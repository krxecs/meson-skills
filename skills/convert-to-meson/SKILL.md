---
name: convert-to-meson
description: Convert an existing C or C++ project from CMake, Autotools, hand-written Makefiles, or another build system to native Meson definitions. Use when the work requires inventorying the old build, mapping targets and options, preserving generated files, dependencies, tests, installs, and validating side-by-side parity. Use meson-build for projects that already use Meson without a build-system conversion.
---

# Convert to Meson

Treat the existing build as the behavioral specification. Inspect its build files, helper scripts, CI, package metadata, and user-facing build documentation before writing Meson files. Preserve supported configurations and output contracts unless the user asks to change them.

## Conversion workflow

1. Inventory the source build system. Record targets, source sets, language standards, compile definitions, include paths, link inputs, dependencies, options, generated files, tests, install rules, packages, supported platforms, and cross-build behavior. Read [source-system mapping](references/source-system-mapping.md) for the detected build system.
2. Establish a baseline with a clean source-system build. Capture the commands and observable results for each supported configuration relevant to the request. Use [parity checks](references/parity-checks.md) to define the comparison before editing.
3. Add native Meson definitions in small vertical slices. Start with `project()` and one target, then add its dependencies, generation, tests, and install rules. Keep the old build usable during the conversion.
4. Validate each slice from a fresh Meson build directory. Compare it with the source build before translating the next slice.
5. Convert CI, packaging, and developer documentation after local parity. Remove the old build system only when the request includes cutover and every required parity check passes.

## Translation rules

- Translate behavior and ownership, not the source build system's syntax or accumulated flags.
- Put project metadata and language standards in `project()`, user choices in `meson.options`, and platform or toolchain choices in native and cross files.
- Use `executable()`, `library()`, `static_library()`, `shared_library()`, or `shared_module()` according to the existing artifact contract.
- Represent external requirements with `dependency()` and reusable in-tree interfaces with `declare_dependency()`.
- Use `configuration_data()` and `configure_file()` for configuration headers. Use `custom_target()` or `generator()` for generated build outputs, and pass those outputs directly to their consumers.
- Register tests with `test()` while preserving arguments, environment, working directory, timeout, expected failure, and fixtures.
- Reproduce the public install tree with target install settings and `install_headers()`, `install_data()`, or the matching install helper. Preserve package metadata and ABI versioning.
- Keep generated files in the build tree. Keep target-only arguments on their targets and use Meson built-in options for compiler standards, warnings, optimization, sanitizers, and link behavior when they express the same contract.

Meson's `cmake2meson.py` converter can create a CMake-derived skeleton when it is available in a Meson source checkout. Treat generated definitions as an inventory aid. Review and simplify every target, option, dependency, generated rule, test, and install declaration before accepting it.

## Completion criteria

- Fresh source-system and Meson builds succeed for every required configuration.
- The parity matrix accounts for targets, artifacts, options, generated files, dependencies, tests, install layout, package metadata, and supported toolchains.
- Differences are requested, documented, or fixed.
- CI and developer commands use Meson when cutover is in scope.
- Legacy build files remain unless their removal is explicitly in scope and the replacement has passed the required checks.
