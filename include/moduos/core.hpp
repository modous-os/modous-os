#pragma once

#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace moduos {

enum class ApplicationState { created, running, stopped };

struct ApplicationStarted {};
struct ApplicationStopped {};
struct ScreenSelected { std::string screen_id; };
enum class ModuleState { detached, attaching, attached, detaching, faulted };
struct ModuleChanged { std::string module_id; ModuleState state; };
using Event = std::variant<ApplicationStarted, ApplicationStopped, ScreenSelected, ModuleChanged>;

class EventBus {
public:
    using Handler = std::function<void(const Event&)>;
    void subscribe(Handler handler);
    void publish(const Event& event) const;
private:
    std::vector<Handler> handlers_;
};

class Application {
public:
    bool start(EventBus& events);
    bool stop(EventBus& events);
    ApplicationState state() const noexcept;
private:
    ApplicationState state_{ApplicationState::created};
};

enum class Theme { dark, light };
enum class Layout { compact, spacious };
struct Settings {
    std::uint8_t brightness_percent{50};
    Theme theme{Theme::dark};
    Layout layout{Layout::compact};
    std::string selected_screen{"watch"};
    std::vector<std::string> enabled_widgets;
};
std::optional<std::string> validate(const Settings& settings);

enum class LogLevel { debug, info, warning, error };
struct LogRecord {
    LogLevel level;
    std::string component;
    std::string message;
};
class Logger {
public:
    using Sink = std::function<void(const LogRecord&)>;
    explicit Logger(Sink sink);
    void write(LogLevel level, std::string component, std::string message) const;
private:
    Sink sink_;
};

struct ProtocolVersion {
    std::uint16_t major{1};
    std::uint16_t minor{0};
};
struct ModuleDescriptor {
    std::string id;
    std::string type;
    ProtocolVersion protocol;
    std::vector<std::string> capabilities;
};
class Module {
public:
    explicit Module(ModuleDescriptor descriptor);
    const ModuleDescriptor& descriptor() const noexcept;
    ModuleState state() const noexcept;
    bool begin_attach(ProtocolVersion host_protocol);
    bool finish_attach(bool initialized);
    bool begin_detach();
    bool finish_detach();
private:
    ModuleDescriptor descriptor_;
    ModuleState state_{ModuleState::detached};
};

struct WidgetState {
    std::string id;
    bool visible{true};
};
struct UiState {
    std::string selected_screen{"watch"};
    Theme theme{Theme::dark};
    Layout layout{Layout::compact};
    std::vector<WidgetState> widgets;
    bool select_screen(std::string screen_id);
    bool set_widget_visible(const std::string& id, bool visible);
};

class Display {
public:
    virtual ~Display() = default;
    virtual bool initialize() = 0;
    virtual bool present(const UiState& state) = 0;
    virtual void set_low_power(bool enabled) = 0;
};
class Clock {
public:
    virtual ~Clock() = default;
    virtual std::uint64_t now_ms() const = 0;
};
class Storage {
public:
    virtual ~Storage() = default;
    virtual bool read(const std::string& key, std::string& value) = 0;
    virtual bool write(const std::string& key, const std::string& value) = 0;
};
struct SensorReading {
    double value{0.0};
    std::uint64_t timestamp_ms{0};
    bool simulated{false};
};
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual std::optional<SensorReading> read() = 0;
};

} // namespace moduos
