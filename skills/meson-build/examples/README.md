# Meson examples

Each directory is a runnable project. Configure it from the repository root with a separate build directory.

```bash
meson setup builddir skills/meson-build/examples/basic-build
meson compile -C builddir
meson test -C builddir
```

| Example                                 | Purpose                                                                 | Checks                                                  |
| --------------------------------------- | ----------------------------------------------------------------------- | ------------------------------------------------------- |
| [basic-build](basic-build/)             | Named targets, a library, an executable, and unit/smoke tests           | Compile and test                                        |
| [cross-compilation](cross-compilation/) | Native build tool, cross-machine configuration, and generated output    | Cross setup and compile, target runtime needs a wrapper |
| [shared-library](shared-library/)       | C ABI shared library, C++ consumer, installation, and pkg-config export | Compile, test, staged install, downstream package check |
| [plugin-system](plugin-system/)         | Runtime-loaded module and exported entry point                          | Compile, load, and run                                  |
| [wrap-fallback](wrap-fallback/)         | System dependency with nested `tinydep` fallback                        | Compile, test, and fallback setup                       |

Each project keeps its own README, source files, licenses, scripts, templates, and machine files. `wrap-fallback/subprojects/tinydep` is part of the fallback example.
