# Software Validation

## Automated checks

The repository provides a CMake build, a dependency-free C++ test executable registered with CTest, and a simulator run. GitHub Actions is configured to run configure, build, CTest, and simulator steps on pushes to `main` or `codex/**`, and on pull requests.

## Evidence

- Test coverage is authored in `tests/core_tests.cpp`; this is not evidence of a passing run.
- A passing GitHub Actions run is required before reporting the milestone as tested.
- No physical hardware validation has been performed.
- No display refresh-rate or power-performance measurement is claimed.

## Scope/limitations

The tests exercise the host core only. They do not validate concurrency, persistence, display rendering, sensor accuracy, bus errors, hot-plug electrical behavior, power switching, or embedded compiler compatibility.
