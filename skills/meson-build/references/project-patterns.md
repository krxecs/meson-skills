# Project patterns

Choose the smallest runnable example that matches the requested build shape. The example directory is the canonical source. Adapt it rather than copying a second full example into a build definition or this reference.

| Need | Runnable example |
|---|---|
| Named targets, executables, and tests | [basic build](../examples/basic-build/) |
| Reusable libraries, C/C++ interoperability, installation, and pkg-config | [shared library](../examples/shared-library/) |
| Build-tree generated output in a cross build | [cross-compilation](../examples/cross-compilation/) |
| Runtime module | [plugin system](../examples/plugin-system/) |
| System dependency with in-tree fallback | [wrap fallback](../examples/wrap-fallback/) |
| Native generator with a cross target | [cross-compilation](../examples/cross-compilation/) |

Minimal examples show one concept. Production-oriented examples add an install layout, version metadata, pkg-config export, tests, a dependency object, and a README. Omit unused directories. Keep public APIs installed, optional capabilities behind feature options, generated files in the build tree, and subprojects limited to a clear dependency need.

The check is complete when a fresh configuration compiles the chosen example and its declared tests or staged installation succeed.
