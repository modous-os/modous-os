#include "moduos/core.hpp"

#include <iostream>

int main() {
    using namespace moduos;
    std::cout << "ModuOS host simulator (simulated state; no watch hardware connected)\n";

    EventBus events;
    events.subscribe([](const Event& event) {
        if (std::holds_alternative<ApplicationStarted>(event)) std::cout << "event: app started\n";
        if (std::holds_alternative<ApplicationStopped>(event)) std::cout << "event: app stopped\n";
        if (const auto* screen = std::get_if<ScreenSelected>(&event))
            std::cout << "event: screen=" << screen->screen_id << '\n';
        if (const auto* module = std::get_if<ModuleChanged>(&event))
            std::cout << "event: module=" << module->module_id
                      << " state=" << static_cast<int>(module->state) << '\n';
    });

    Application app;
    app.start(events);

    UiState ui;
    ui.widgets = {{"clock", true}, {"steps", false}};
    ui.select_screen("watch");
    events.publish(ScreenSelected{ui.selected_screen});

    Module demo({ "simulated.demo", "demo", {1, 0}, {"example"} });
    if (demo.begin_attach({1, 0}) && demo.finish_attach(true))
        events.publish(ModuleChanged{demo.descriptor().id, demo.state()});

    std::cout << "theme=dark layout=compact widgets=" << ui.widgets.size() << '\n';
    demo.begin_detach();
    demo.finish_detach();
    events.publish(ModuleChanged{demo.descriptor().id, demo.state()});
    app.stop(events);
    return 0;
}
