# Software Architecture

Status: implemented at host-core level; not yet validated on watch hardware.

## Layers

- **Portable core** (`include/moduos`, `src`): lifecycle, event delivery, settings validation, logging records, module descriptors/lifecycle, and UI state.
- **Hardware contracts**: abstract display, clock, storage, and sensor interfaces. They contain no Linux, ESP-IDF, or MCU APIs.
- **Host simulator** (`app/simulator.cpp`): prints explicitly simulated state transitions; no sensor values are fabricated.
- **Tests** (`tests`): dependency-free executable registered with CTest.

## Lifecycle and event flow

`Application` accepts one transition from created to running and one from running to stopped. `EventBus` delivers typed value events synchronously to registered handlers. The initial implementation is single-threaded; it does not promise thread safety or queued delivery.

## Modules

A `ModuleDescriptor` carries stable ID, type, protocol major/minor, and capabilities. `Module` models logical attach and detach, checks protocol major compatibility, and enters a faulted state if initialization fails. This is not a physical hot-plug driver. Power switching, electrical isolation, bus probing, timeouts, and disconnect recovery require a verified hardware contract and platform adapter.

## Settings and UI

Settings validation rejects brightness above 100, empty screen/widget IDs, and more than eight enabled widgets. UI state stores selected screen, theme, layout, and widget visibility. Persistence format and migration policy remain open.

## Portability

The core is standard C++17 and deliberately avoids platform headers. Platform adapters and MCU-specific builds are deferred until the exact hardware and RTOS/toolchain are agreed. The simulator makes no refresh-rate or hardware-performance claim.
