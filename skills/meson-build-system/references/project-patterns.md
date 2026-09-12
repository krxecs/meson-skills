# Project patterns

Choose the smallest runnable example that matches the requested build shape. The example directory is the canonical source. Adapt it rather than copying a second full example into a build definition or this reference.

| Need | Runnable example |
|---|---|
| Named target, library, executable, and test | [basic build](../examples/basic-build/) |
| Executable with tests | [executable with tests](../examples/executable-with-tests/) |
| Reusable C++ library | [reusable library](../examples/reusable-library/) |
| C ABI with a C++ consumer | [mixed C and C++](../examples/mixed-c-cpp/) |
| Build-tree generated sources | [generated sources](../examples/generated-sources/) |
| Runtime module | [plugin system](../examples/plugin-system/) |
| System dependency with in-tree fallback | [wrap fallback](../examples/wrap-fallback/) |
| Native generator with a cross target | [cross-compilation](../examples/cross-compilation/) |
| Windows MSVC target | [Windows MSVC](../examples/windows-msvc/) |
| Install staging | [package installation](../examples/package-installation/) |
| pkg-config metadata | [pkg-config export](../examples/pkg-config-export/) |
| GitHub Actions pipeline | [GitHub Actions](../examples/github-actions/) |

Minimal examples show one concept. Production-oriented examples add an install layout, version metadata, pkg-config export, tests, a dependency object, and a README. Omit unused directories. Keep public APIs installed, optional capabilities behind feature options, generated files in the build tree, and subprojects limited to a clear dependency need.

The check is complete when a fresh configuration compiles the chosen example and its declared tests or staged installation succeed.
