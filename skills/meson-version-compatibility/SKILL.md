---
name: meson-version-compatibility
description: Choose and verify Meson version requirements. Use for `meson_version`, deprecated or removed APIs, distribution package constraints, compiler or backend limits, and migration across Meson releases.
---

# Meson version compatibility

Select one distribution baseline for this repository, then use it consistently in every project example.

## Workflow

1. When web access is available, identify the latest Ubuntu LTS, Debian stable, and Fedora stable releases from their official release pages.
2. Read each release's Meson version from its official package index. Compare the upstream version components and select the oldest. This is the repository baseline.
3. Inspect the APIs and options used in each example against the official Meson reference and release notes.
4. Use an equivalent API supported by the baseline when practical. If an example requires a newer API, raise that example's `meson_version` and state why.
5. Set the selected baseline in every other `project()` definition.
6. Configure the examples with the exact baseline. The check is complete when they all configure successfully and every higher-version exception is documented.

If web access is unavailable, ask the user which Meson version to target and suggest the locally installed version as a fallback. Do not silently replace the repository policy with an API-derived minimum.

## Policy

- Set the selected baseline in every `project()` declaration unless a documented feature requires a higher version.
- Write new examples for the current repository baseline first.
- Attach higher-version requirements to the feature that needs them.
- Avoid legacy APIs unless migration is the subject.
- Prefer modern accessors, option syntax, and dependency declarations supported by the baseline.
- Keep deprecation notes concise and actionable.
- Do not add compatibility ladders outside migration guidance.
- Distinguish Meson, compiler, linker, and backend constraints.

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

The repository currently uses Meson 1.7.0 because it is the oldest version selected by the distribution policy above. The `license_files` API needs only Meson 1.1.0, but an API floor does not override the repository baseline. Recompute the distribution baseline before changing it.

## Common mistakes

- mixing old and new API names in the same example
- documenting every historical Meson release instead of the supported range
- making version guidance so broad that it stops being useful
- forgetting that compiler and backend support can differ even when Meson itself is current
