---
name: meson-build-system
description: Route Meson work to the skill that owns it. Use for general Meson syntax, basic project files, build directories, or requests that span several Meson topics.
---

# Meson build system

Inspect the project before recommending a command or changing a build definition. Read `meson.build`, `meson.options`, machine files, wrap files, and CI configuration when they bear on the request.

## Fast path

1. Identify the owning skill below.
2. Inspect the source and configured build directory before editing.
3. Apply the smallest change that fits the existing project.
4. Run the relevant setup, compile, test, or install command. Report any check that could not run.

## Route to the right skill

- New projects, build options, compilers, or build types: `meson-setup-configuration`
- Target selection, parallel builds, or backend arguments: `meson-compile-targets`
- Test execution or installation commands: `meson-testing-installation`
- Cross or native machine files: `meson-cross-compilation`
- Freestanding, kernel, or bare-metal targets: `meson-freestanding-projects`
- Wraps, subprojects, or dependency fallbacks: `meson-subprojects-management`
- CI jobs, matrices, artifacts, or caches: `meson-ci-cd-integration`
- Unexplained setup, compile, test, or install failures: `meson-debugging-troubleshooting`
- Minimum Meson versions, removed APIs, or portability: `meson-version-compatibility`
- Feature options, dependency objects, generated sources, or large project structure: `meson-advanced-project-design`
- Full reusable examples: `meson-patterns-cookbook`
- Install layout, pkg-config metadata, releases, or packages: `meson-package-export-distribution`

## Core rules

- Keep `meson.build` declarative and small.
- Prefer target-local configuration over global argument sprawl.
- Use feature options for optional capabilities.
- Export reusable interfaces with `declare_dependency()` instead of duplicating flags.
- Treat build directories as disposable; do not store source of truth there.
- Prefer built-in standards and options over manual compiler flags.
- Use the repository baseline selected by `meson-version-compatibility`. Raise it only when a required API needs a newer Meson release. Use the repository's actual license file name in `license_files`.

```meson
project(
  'example',
  'c',
  'cpp',
  version: '0.1.0',
  meson_version: '>=1.7.0',
  license: 'MIT',
  license_files: ['LICENSE.md'],
  default_options: [
    'c_std=c17',
    'cpp_std=c++20',
    'warning_level=3',
  ],
)
```

## Project checks

- A small top-level `meson.build` that wires together subdirectories.
- Public headers installed separately from private implementation details.
- Dependencies represented as dependency objects, not copied compiler flags.
- Optional features controlled by `feature` options, not hardcoded booleans.
- Generated code created in the build tree, not committed to the source tree.
- Versioned install metadata and pkg-config exports for downstream users.

## Naming and placement

- Use explicit names for targets and dependency objects.
- Prefer `foo_dep` for dependency objects, `foo_lib` for libraries, and `foo_test` for test helpers.
- Keep `subdir()` boundaries shallow and predictable.
- Put reusable helper functions in `meson.build` only when they truly reduce duplication.
- Keep project metadata in `project()`, option defaults in `default_options`, and project options in `meson.options`.

For requests that cross several branches, load each relevant skill and reconcile their checks before editing. The task is complete when the requested behavior works and every relevant check has a recorded result.
