# Experimental public upstream CPU build

The community branch permits a separately prepared public upstream XACC installation to be selected explicitly. This is an experimental compatibility profile, not a claim that arbitrary XACC versions work.

- `XACC_TAG` selects the expected revision for the dependency version check. The original default remains `01053824`.
- `XACC_REPOSITORY` selects the source repository if an installation needs to be built. Existing installations still undergo the version check.
- `WITH_TNQVM=OFF` skips acquisition and installation of ExaTN/TNQVM. It does not add another implementation of their simulators. The default is ON.
- `N_PROC=2` limits dependency build parallelism. Explicit values must be positive integers; otherwise processor discovery supplies the default.

The first community qualification uses XACC commit `d1edaa7ae53edc7e335f46d33160f93d6020aaa3` with a separately recorded ACZ compatibility patch and a qpp CPU profile. See the qualification scripts in the companion `marqov-dev/qristal` fork for exact sources, compiler, dependency inventory and test evidence.

The clean toolchain is public Ubuntu 22.04 with GCC 11.4 and Python 3.10. This is a Qristal runtime environment, not an environment for installing the current Marqov SDK. Marqov integration will use an isolated execution adapter and requires separate acceptance testing.

No commercial Emulator or internal vQPU is part of this profile. GPU, tensor-network, remote hardware, broad algorithm compatibility and distribution packaging remain separate qualification work. Do not advertise them based on a Core build or import test.
