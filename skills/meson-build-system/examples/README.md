# Meson examples

Each directory is a runnable project. Configure it from the repository root with a separate build directory.

```bash
meson setup builddir skills/meson-build-system/examples/basic-build
meson compile -C builddir
meson test -C builddir
```

| Example | Purpose | Checks |
|---|---|---|
| [basic-build](basic-build/) | Named library, executable, and test | Compile and test |
| [cross-compilation](cross-compilation/) | Native generator and cross target | Cross setup and compile, target runtime needs a wrapper |
| [executable-with-tests](executable-with-tests/) | Application with unit tests | Compile, test, staged install |
| [generated-sources](generated-sources/) | `custom_target()` and `generator()` output | Compile and run |
| [github-actions](github-actions/) | GitHub Actions Meson pipeline | Local compile and test, workflow review |
| [mixed-c-cpp](mixed-c-cpp/) | C API with C++ caller | Compile and run |
| [package-installation](package-installation/) | Headers, data, and staged install | Compile, test, staged install |
| [pkg-config-export](pkg-config-export/) | Shared library and pkg-config file | Compile, test, staged install |
| [plugin-system](plugin-system/) | Runtime-loaded module | Compile and run |
| [reusable-library](reusable-library/) | C++ library and dependency object | Compile and test |
| [windows-msvc](windows-msvc/) | MSVC-oriented project | Requires Windows and MSVC |
| [wrap-fallback](wrap-fallback/) | System dependency with nested `tinydep` fallback | Compile, test, and fallback setup |

Each project keeps its own README, source files, licenses, scripts, templates, and machine files. `wrap-fallback/subprojects/tinydep` is part of the fallback example.
