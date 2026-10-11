# Decisions

## 2026-10-11 — Start with a portable host core

**Decision:** Use standard C++17, CMake, and a small host simulator. Keep hardware APIs abstract and target-specific code out of the core.

**Reason:** It permits meaningful host validation before the watch MCU, display, RTOS, and electrical interfaces are selected.

**Status:** Implemented on `codex/os-core`; CI result pending.

## 2026-10-11 — Module attach is a logical state machine only

**Decision:** Model descriptor compatibility and attach/detach transitions without probing buses or controlling power.

**Reason:** Connector, pinout, bus, and power protections are not yet verified.

**Status:** Implemented. Hardware handshake remains proposed.

## 2026-10-11 — Keep the initial simulator honest

**Decision:** Label it as a simulator and emit no fake physiological readings.

**Reason:** Sensor outputs are consumer wellness data and no physical sensor has been integrated or validated.

**Status:** Implemented.
