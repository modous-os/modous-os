# Software Validation

## Reproducible local checks

Requires a C++17 compiler, CMake 3.16 or newer, and CTest.

```sh
cmake -S . -B build
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/moduos_simulator
```

GitHub Actions runs configure, build, CTest, and the simulator on pushes to `main` or `codex/**`, and on pull requests.

## CI evidence

- GitHub Actions run [38159699119](https://github.com/saif12377/modous-os/actions/runs/38159699119) completed successfully on commit `e65dc2bff5a1d13276ae2593816c6e8685c3bd24`: Configure, Build, Test, and Run simulator all succeeded.
- The initial CI run failed during Build because the typed event header did not include `<variant>`. That include was added; the later run above validates the correction.
- Tests in `tests/core_tests.cpp` cover application transitions, event delivery, settings bounds, module protocol/state transitions, and UI mutations.

## Scope and limits

The CI checks exercise the host core only. No physical hardware validation has been performed. The checks do not validate concurrency, persistence, display rendering, sensor accuracy, bus errors, hot-plug electrical behavior, power switching, or embedded compiler compatibility. No display refresh-rate or power-performance measurement is claimed.
