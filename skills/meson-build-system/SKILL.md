---
name: meson-build-system
description: Build, configure, test, install, package, debug, and maintain Meson projects. Use for Meson setup and options, targets, tests, installs, cross or freestanding builds, subprojects, CI, project design, version compatibility, distribution, troubleshooting, or runnable Meson examples.
---

# Meson build system

Inspect the relevant `meson.build`, `meson.options`, machine files, wraps, and CI files before editing. Inspect the configured build directory before recommending a command. Keep changes local to the requested behavior.

## Shared workflow

1. Identify the build shape and load the reference that matches the request.
2. Change the source definition or command that owns the behavior.
3. Configure a fresh or reconfigured build directory as needed.
4. Compile the affected targets, then run affected tests and install checks.
5. Report every command run and every unavailable platform, toolchain, emulator, or runtime check.

Build directories are disposable. Keep project metadata in `project()`, project options in `meson.options`, and workflow choices in setup options. Prefer built-in options and dependency objects over copied flags. Keep generated output in the build tree. Use target-local arguments unless an argument applies to the whole project.

## References

- [Setup and configuration](references/setup-configuration.md): setup, compilers, options, build types, reconfiguration, and migration standards.
- [Compile targets](references/compile-targets.md): target selection, backend arguments, and compile failures.
- [Testing and installation](references/testing-installation.md): tests, suites, staging, and install rules.
- [Cross-compilation](references/cross-compilation.md): native and cross files, sysroots, wrappers, and target tools.
- [Freestanding projects](references/freestanding-projects.md): bare-metal toolchains, linker scripts, boot images, and artifact checks.
- [Subprojects](references/subprojects-management.md): wraps, fallbacks, vendoring, and dependency boundaries.
- [CI and CD](references/ci-cd-integration.md): pipelines, caches, artifacts, and release jobs.
- [Debugging](references/debugging-troubleshooting.md): setup, compile, dependency, test, and install diagnosis.
- [Version compatibility](references/version-compatibility.md): the repository policy, modern APIs, and portability constraints.
- [Project design](references/advanced-project-design.md): options, interfaces, generated sources, library boundaries, and layout.
- [Package export and distribution](references/package-export-distribution.md): install layout, pkg-config, ABI versions, staged consumers, and `meson dist`.
- [Project patterns](references/project-patterns.md): choose a runnable pattern from [examples](examples/README.md).

## Completion criteria

- The changed definition expresses the requested behavior without duplicate flags or hidden build-tree state.
- Every affected target configures and compiles.
- Tests, staged installs, package checks, and artifact inspection run when the request makes them relevant.
- The project keeps its established `meson_version: '>=1.7.0'` baseline unless a documented repository policy change asks for another value.
