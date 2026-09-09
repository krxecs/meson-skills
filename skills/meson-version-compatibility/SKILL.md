---
name: meson-version-compatibility
description: Choose and verify Meson version requirements. Use for `meson_version`, deprecated or removed APIs, distribution package constraints, compiler or backend limits, and migration across Meson releases.
---

# Meson version compatibility

Choose the minimum version from evidence, not from one universal baseline.

## Workflow

1. Inspect the project's current `meson_version`, APIs, options, and CI or packaging targets.
2. Find the earliest Meson release that supports every required feature in the official reference and release notes.
3. Check the Meson versions available in each environment the project promises to support. Use current package data when distribution compatibility matters.
4. Set the lowest version that satisfies both the required APIs and the support policy.
5. Configure with that exact minimum version when practical. The check is complete when setup succeeds or the unsupported feature reports the expected version error.

## Policy

- set `meson_version` in each top-level `project()` declaration
- attach version notes to the feature that needs them
- avoid legacy APIs unless a migration note is the point of the section
- preserve an older API when the supported Meson range requires it
- distinguish Meson, compiler, linker, and backend constraints

## Replace older APIs

Use these modern forms instead of the older ones:

- Replace `meson.source_root()` with `meson.project_source_root()`.
- Replace `meson.build_root()` with `meson.project_build_root()`.
- Replace `meson.get_cross_property()` with `meson.get_external_property()`.
- Replace `meson.has_exe_wrapper()` with `meson.can_run_host_binaries()`.

## What to document

- the minimum Meson version required by the repo
- APIs that should no longer appear in examples
- backend-specific limitations that still matter
- compiler-specific behavior that changes the recommended pattern
- whether a skill is about modern use or legacy migration

## Version notes

Keep version notes attached to the actual feature, not scattered across unrelated files.

Example:

```meson
project(
  'example',
  'c',
  'cpp',
  version: '0.1.0',
  meson_version: '>=1.1.0',
  license: 'MIT',
  license_files: ['LICENSE'],
  default_options: [
    'c_std=c17',
    'cpp_std=c++20',
    'warning_level=3',
  ],
)
```

Name the feature that sets the bound. In this example, `license_files` requires Meson 1.1.0. Raise the bound if another API requires a newer release.

## Common mistakes

- mixing old and new API names in the same example
- documenting every historical Meson release instead of the supported range
- making version guidance so broad that it stops being useful
- forgetting that compiler and backend support can differ even when Meson itself is current
