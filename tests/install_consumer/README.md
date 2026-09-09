# Installed SDK consumer

This small standalone consumer checks that `find_package(qristal_core)` and `qristal::core` work without the Core source or build trees. It initializes XACC and constructs one Hadamard gate through the installed Core C++ API.

Copy this fixture into a clean consumer directory. Make the installed Core/XACC prefixes and required system development libraries available, but do not expose the Core source/build directories or dependency cache. Run:

```sh
cmake -S . -B build -Dqristal_core_DIR=/path/to/installed/core
cmake --build build --parallel 2
./build/core-consumer
```

The recorded Linux amd64 Ubuntu 22.04 test used fixed install prefixes `/work/install-core` and `/work/install-xacc`, with no LD_LIBRARY_PATH override. Runtime and compiler dependencies came from the pinned public Ubuntu toolchain used in marqov-dev/qristal qualification. This does not claim prefix relocation, a standalone wheel, or validation on other platforms.

Before the fix, configuration failed: exported dependencies referenced `/work/qristal-core/deps/eigen3`, which was absent, and the system Eigen 3.4.0 was below the required 3.4.1. After installing Core's bundled Eigen and exporting its install path, configuration, compilation and execution passed. The fix also covers cached reconfiguration, where Eigen3_ADDED is no longer true but the selected Eigen is still Core's local copy. External/system Eigen selections retain their existing behavior; that alternative was not separately rebuilt here.
