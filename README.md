# ModuOS

ModuOS is a modular smartwatch platform. This repository is the software foundation for a future watch; it is not a custom computer operating system.

## Current status

The repository is being initialized. No watch hardware, display, MCU, sensor, electrical interface, or performance target has been verified in this repository yet. Treat all part numbers and interfaces in planning documents as candidates until backed by design files and manufacturer documentation.

## Planned software foundation

- Portable C++ application core with a host simulator.
- Hardware interfaces kept separate from platform-specific drivers.
- Typed events, validated settings, module lifecycle, and UI state.
- Automated tests and reproducible CMake build instructions.
- Hardware/software contract documented without inventing pinouts or electrical ratings.

## Consumer use

ModuOS is intended for consumer wellness. Sensor outputs must not be represented as medical-grade measurements.

## Getting started

Build and test instructions will be added with the first working software milestone. No build or test result is claimed yet.