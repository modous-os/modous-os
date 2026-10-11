# Open Questions

## Hardware

- Which exact watch processor and package will be used, and what evidence supports the selection?
- Which display revision, interface, timings, controller initialization, and low-power behavior are verified?
- What are the schematic-backed module connector contacts, electrical ratings, bus, detection method, and safe power path?
- Which wireless architecture is selected, including the external radio companion if ESP32-P4 is chosen?
- Which sensor part/revision and optical/mechanical stack are planned? What are the vendor initialization and calibration requirements?
- How are debug access, boot straps, reset, brownout, and unexpected module removal handled?

## Software/platform

- Which OS/RTOS and exact embedded toolchain should host the first MCU adapter?
- What settings persistence encoding, versioning, and migration rules are required?
- Should EventBus remain synchronous or use a bounded queue on the embedded target?
- What module descriptor wire format, authentication/integrity, timeout, and retry limits will the hardware support?
- Which verified display and sensor evaluation boards can be used for the first integration tests?

## Evidence and ownership

- Where is the active KiCad project and its source documentation?
- Who owns updates to the hardware/software contract, and how will cross-review acceptance be recorded?
