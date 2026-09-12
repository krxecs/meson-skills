# Source-system mapping

Identify where the current build system owns each behavior. Read the files and included fragments that contribute to the selected configuration. Dynamic build definitions may require dry-run or verbose commands to reveal the final compiler and linker invocations.

## CMake

Inspect `CMakeLists.txt`, included `.cmake` modules, presets, toolchain files, and package configuration templates.

| CMake concept | Meson destination |
|---|---|
| `project()` and cache defaults | `project()` and `meson.options` |
| `add_executable()` and `add_library()` | matching Meson target functions |
| `target_sources()` | target source arguments and `files()` |
| `target_include_directories()` | `include_directories()` and dependency objects |
| `target_compile_definitions()` and `target_compile_options()` | target arguments or Meson built-in options |
| `target_link_libraries()` | `link_with`, `link_whole`, or `dependencies` according to ownership |
| `find_package()` | `dependency()`, including `method: 'cmake'` only when needed |
| `option()` and cache variables | typed options in `meson.options` |
| `configure_file()` | `configuration_data()` with `configure_file()` |
| custom commands and generated sources | `custom_target()` or `generator()` with outputs passed to consumers |
| CTest declarations | `test()` and `benchmark()` |
| `install()` and package exports | target install settings, install helpers, and package metadata |

Read generator expressions and target property propagation before mapping them. A CMake target may carry transitive includes, definitions, link inputs, and platform conditions that are not visible at the call site.

## Autotools

Inspect `configure.ac`, every `Makefile.am`, included M4 macros, generated configuration headers, and bootstrap scripts. Use generated `configure` and `Makefile.in` files only to understand behavior absent from the maintained inputs.

Map `AC_INIT` metadata to `project()`, language and compiler checks to declared project languages and compiler feature checks, `AC_ARG_ENABLE` and `AC_ARG_WITH` to typed Meson options, and `PKG_CHECK_MODULES` to `dependency()`. Translate Automake target variables such as `_SOURCES`, `_CPPFLAGS`, `_LDADD`, `_LDFLAGS`, `BUILT_SOURCES`, `TESTS`, and install classes into target, generated-source, test, and install declarations.

Distinguish feature detection from obsolete portability probes. Preserve checks that select real source paths or public configuration macros. Drop probes only after supported compilers and platforms make them unnecessary and the resulting behavior has been tested.

## Hand-written Makefiles

Inspect included makefiles, recursive invocations, variable defaults, pattern and suffix rules, generated dependency files, phony targets, install recipes, and packaging scripts. Record the expanded commands for representative configurations because variable indirection may hide the actual target graph.

Map real artifacts rather than every phony target. Separate compilation inputs, generated inputs, link dependencies, test commands, install destinations, and developer-only helpers. Preserve user-overridable build choices as Meson options or machine-file settings. Do not carry command-order dependencies into Meson when an explicit input-output relationship expresses them.

## Other build systems

For SCons, Bazel, xmake, Premake, IDE projects, and custom scripts, derive the same inventory from declared targets and observed commands. Identify configuration selection, transitive usage requirements, generated outputs, test registration, installation, and platform branches before choosing Meson APIs. Keep source-system-specific helpers until their replacement has an observable parity check.
