---
name: meson-setup-configuration
description: Configure Meson build directories and options. Use for initial setup, compiler selection, build types, sanitizers, optimization, installation prefixes, `-D` options, reconfiguration, or wipes.
---

# Meson setup and configuration

`meson setup` creates the build directory and locks in the compiler, toolchain, and option set. Use `meson configure` for later edits and `meson setup --reconfigure` when the build state should be refreshed.

## Useful defaults

```bash
meson setup builddir -Dwarning_level=3
```

## Workflow

1. Inspect `project()`, `meson.options`, existing build directories, and machine files.
2. Decide whether the request needs a new setup, `meson configure`, `--reconfigure`, or `--wipe`.
3. Apply options on the command line or in their owning project file.
4. Confirm the result with `meson configure builddir` or `meson introspect builddir --buildoptions`.

## Common configuration goals

- switch between debug and release
- turn warnings into errors
- enable or disable optional features
- set the install prefix and directories
- choose sanitizers or LTO
- adjust the language standard
- choose native or cross machine files

## Build-type guidance

Use build types as workflow choices, not as hidden policy inside every project example.

- `debug` for day-to-day development
- `debugoptimized` for a practical developer build
- `release` for shipping binaries
- `minsize` when footprint matters
- `plain` when the build should avoid Meson-imposed defaults

## Practical rules

- set compiler selection before the first `meson setup`
- edit options with `meson configure` instead of rewriting the build tree by hand
- wipe or reconfigure when the toolchain changes
- keep project options in `meson.options` and defaults in `project(default_options: ...)`
- use built-in options for standards and warning levels rather than manual `-std=` flags

## Project header

Use the repository baseline selected by `meson-version-compatibility`. Raise it only when a required API needs a newer Meson release:

```meson
project(
  'my-project',
  'c',
  'cpp',
  version: '0.1.0',
  meson_version: '>=1.7.0',
  license: 'MIT',
  license_files: ['LICENSE'],
  default_options: [
    'c_std=c17',
    'cpp_std=c++20',
    'warning_level=3',
  ],
)
```

## Common mistakes

- changing compiler variables after setup and expecting them to take effect automatically
- editing the build tree by hand instead of reconfiguring
- putting language standards in random target arguments instead of built-in options
- forcing production-only settings into beginner examples
- confusing project defaults with per-build workflow decisions

## Language standard selection

When migrating a project to Meson:

1. Inspect `CMakeLists.txt` for `CMAKE_C_STANDARD` and `CMAKE_CXX_STANDARD`.
2. Inspect Autotools files such as `configure.ac` and `Makefile.am`, plus any compiler flags like `-std=c17` or `-std=c++20`.
3. Inspect plain Makefiles for `-std=` flags.
4. Inspect CI configurations and compiler invocation scripts.
5. If the standards still cannot be deduced, ask the user directly which C and C++ standards they want.
6. For a new project with no stated constraint, choose standards supported by its compiler baseline and record the choice in `default_options`.

Do not silently change language standards during Meson migration.

Read [reference.md](reference.md) when exact setup flags or built-in option values matter. Read [troubleshooting.md](troubleshooting.md) when setup state, compiler selection, or cached dependencies do not match the request.
