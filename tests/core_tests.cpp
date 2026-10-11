#include "moduos/core.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <variant>

namespace {
void check(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        std::exit(1);
    }
}
}

int main() {
    using namespace moduos;

    EventBus events;
    int delivered = 0;
    events.subscribe([&](const Event&) { ++delivered; });
    Application app;
    check(app.start(events), "application starts once");
    check(!app.start(events), "application cannot start twice");
    check(app.stop(events), "running application stops");
    check(delivered == 2, "start and stop events delivered");

    Settings settings;
    check(!validate(settings), "default settings are valid");
    settings.brightness_percent = 101;
    check(validate(settings).has_value(), "brightness above 100 rejected");
    settings = Settings{};
    settings.enabled_widgets.resize(9, "widget");
    check(validate(settings).has_value(), "more than eight widgets rejected");

    Module module({"sensor.demo", "sensor", {1, 2}, {"sample"}});
    check(module.begin_attach({1, 0}), "same major protocol can begin attach");
    check(module.finish_attach(true), "initialized module attaches");
    check(module.state() == ModuleState::attached, "attached state recorded");
    check(module.begin_detach(), "attached module begins detach");
    check(module.finish_detach(), "module returns to detached state");

    Module incompatible({"sensor.v2", "sensor", {2, 0}, {}});
    check(!incompatible.begin_attach({1, 0}), "incompatible major protocol rejected");
    Module failed({"sensor.fail", "sensor", {1, 0}, {}});
    check(failed.begin_attach({1, 0}), "failed module begins initialization");
    check(failed.finish_attach(false), "failed initialization recorded");
    check(failed.state() == ModuleState::faulted, "failed module is faulted");
    check(failed.begin_detach() && failed.finish_detach(), "faulted module can detach safely");

    UiState ui;
    check(ui.select_screen("settings"), "screen selection succeeds");
    check(!ui.select_screen(""), "empty screen rejected");
    ui.widgets.push_back({"steps", true});
    check(ui.set_widget_visible("steps", false), "known widget visibility changes");
    check(!ui.set_widget_visible("missing", true), "unknown widget is not created implicitly");

    std::cout << "All ModuOS core tests passed.\n";
    return 0;
}
