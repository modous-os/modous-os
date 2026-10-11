# ModuOS

ModuOS is a modular smartwatch platform. This repository is the software foundation for a future watch; it is not a custom computer operating system.

## Current status

The software starter milestone is on branch `codex/os-core`. No watch hardware, display, MCU, sensor, electrical interface, or performance target has been verified here. Treat all parts and interfaces as candidates until backed by design files and manufacturer documentation.

## Build, test, and run

Requires a C++17 compiler, CMake 3.16 or newer, and CTest.

```sh
cmake -S . -B build
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/moduos_simulator
```

On Windows, run the simulator as `build\\moduos_simulator.exe`.

The simulator prints simulated UI and module state only; no watch hardware or physiological readings are connected.

## Software foundation

- Portable C++ application core and typed synchronous event delivery.
- Validated settings, structured log records, module descriptors and logical attach/detach lifecycle.
- UI state for screen, theme, layout, and widget visibility.
- Abstract display, clock, storage, and sensor interfaces.
- CMake/CTest checks and GitHub Actions workflow.

See `docs/` for architecture, proposed hardware contract, decisions, open questions, and validation scope.

## Consumer use

ModuOS is intended for consumer wellness. Sensor outputs must not be represented as medical-grade measurements. No physical hardware validation or display refresh-rate claim has been made.
