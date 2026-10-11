# Hardware/Software Contract

Status: proposed software boundary; no electrical interface has been verified.

## Software interfaces present

The portable core defines abstract interfaces for display initialization/presentation/low-power requests, monotonic milliseconds, key/value storage, and optional timestamped sensor readings. `SensorReading::simulated` distinguishes demo data from physical measurements.

## Not specified yet

No connector pin count or pinout, contact arrangement, voltage/current rating, bus allocation, power-enable GPIO, hot-plug detection circuit, reset/boot strap, debug interface, display timing, or sensor initialization sequence is approved by this document.

Candidate parts named in planning are not design selections. Confirm exact manufacturer part/revision and datasheet before implementing drivers.

## Required module handshake (proposed)

1. Hardware detects attachment and reports a bounded, stable module identity.
2. Platform adapter performs electrical checks and only enables module power through hardware-protected circuitry.
3. Software reads descriptor (ID, type, protocol version, capabilities) with a timeout.
4. Host rejects malformed descriptors and unsupported protocol majors.
5. Driver initialization is bounded; failure leaves the module unavailable and reports a fault.
6. Detach or communication loss disables further transactions, requests safe power-down through the adapter, and reports logical detach.
7. Hardware protection remains responsible for current limiting, reverse/short protection, and safe defaults; software is not the sole safety mechanism.

Transport, framing, checksums, timeouts, retries, detach sensing, and power sequencing remain undecided pending the schematic and component evidence.
