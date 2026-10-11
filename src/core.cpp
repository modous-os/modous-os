#include "moduos/core.hpp"

#include <utility>

namespace moduos {

void EventBus::subscribe(Handler handler) {
    handlers_.push_back(std::move(handler));
}

void EventBus::publish(const Event& event) const {
    for (const auto& handler : handlers_) {
        handler(event);
    }
}

bool Application::start(EventBus& events) {
    if (state_ != ApplicationState::created) return false;
    state_ = ApplicationState::running;
    events.publish(ApplicationStarted{});
    return true;
}

bool Application::stop(EventBus& events) {
    if (state_ != ApplicationState::running) return false;
    state_ = ApplicationState::stopped;
    events.publish(ApplicationStopped{});
    return true;
}

ApplicationState Application::state() const noexcept {
    return state_;
}

std::optional<std::string> validate(const Settings& settings) {
    if (settings.brightness_percent > 100) return "brightness must be 0..100";
    if (settings.selected_screen.empty()) return "selected_screen must not be empty";
    if (settings.enabled_widgets.size() > 8) return "at most 8 widgets may be enabled";
    for (const auto& id : settings.enabled_widgets) {
        if (id.empty()) return "widget IDs must not be empty";
    }
    return std::nullopt;
}

Logger::Logger(Sink sink) : sink_(std::move(sink)) {}

void Logger::write(LogLevel level, std::string component, std::string message) const {
    if (sink_) sink_(LogRecord{level, std::move(component), std::move(message)});
}

Module::Module(ModuleDescriptor descriptor) : descriptor_(std::move(descriptor)) {}

const ModuleDescriptor& Module::descriptor() const noexcept { return descriptor_; }
ModuleState Module::state() const noexcept { return state_; }

bool Module::begin_attach(ProtocolVersion host_protocol) {
    if (state_ != ModuleState::detached || descriptor_.id.empty() ||
        descriptor_.type.empty() || descriptor_.protocol.major != host_protocol.major) {
        return false;
    }
    state_ = ModuleState::attaching;
    return true;
}

bool Module::finish_attach(bool initialized) {
    if (state_ != ModuleState::attaching) return false;
    state_ = initialized ? ModuleState::attached : ModuleState::faulted;
    return true;
}

bool Module::begin_detach() {
    if (state_ != ModuleState::attached && state_ != ModuleState::faulted) return false;
    state_ = ModuleState::detaching;
    return true;
}

bool Module::finish_detach() {
    if (state_ != ModuleState::detaching) return false;
    state_ = ModuleState::detached;
    return true;
}

bool UiState::select_screen(std::string screen_id) {
    if (screen_id.empty()) return false;
    selected_screen = std::move(screen_id);
    return true;
}

bool UiState::set_widget_visible(const std::string& id, bool visible) {
    for (auto& widget : widgets) {
        if (widget.id == id) {
            widget.visible = visible;
            return true;
        }
    }
    return false;
}

} // namespace moduos
