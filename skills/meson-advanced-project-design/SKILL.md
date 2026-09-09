---
name: meson-advanced-project-design
description: Design larger Meson projects. Use for feature options, dependency objects, generated sources, library boundaries, reproducibility, or project layout beyond initial setup.
---

# Advanced Meson project design

## Workflow

1. Inspect the existing target, directory, dependency, and option boundaries.
2. Identify the one boundary causing duplication, hidden state, or unnecessary coupling.
3. Change that boundary without changing unrelated build behavior.
4. Configure and compile every affected target. Run affected tests when available.

## Design goals

- keep configuration readable
- keep dependencies explicit
- keep targets small and composable
- keep generated files in the build tree
- keep the public API separate from private implementation details
- keep the project reproducible across machines and CI
- keep policy out of target declarations unless it is genuinely local

## Canonical project skeleton

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

```meson
inc = include_directories('include')

subdir('src')
subdir('tests')
```

A clean split usually looks like this:

- `include/` for public headers
- `src/` for implementation and private helpers
- `tests/` for test-only code
- `subprojects/` for vendored dependencies, if needed
- `docs/` and `scripts/` only when they add value

## Feature options

Use `feature` options for optional dependencies and optional capabilities.

```meson
option('wayland', type: 'feature', value: 'auto', description: 'Enable Wayland support')
```

Then gate the dependency explicitly:

```meson
wayland_opt = get_option('wayland')
wayland_dep = dependency('wayland-client', required: wayland_opt)
```

Prefer this over ad hoc booleans because the option expresses intent better and composes more cleanly in large projects.

## `declare_dependency()`

Use `declare_dependency()` to publish a library interface once and reuse it everywhere.

```meson
mylib = library('mylib', 'src/mylib.cpp', include_directories: inc, install: true)

mylib_dep = declare_dependency(
  include_directories: inc,
  link_with: mylib,
)
```

That pattern gives consumers one dependency object instead of a pile of copied flags.

## Static and shared libraries

Choose the library type deliberately.

- `static_library()` is good for internal reuse and some embedded or plugin-free cases
- `shared_library()` is good when ABI stability and runtime reuse matter
- `both_libraries()` is useful when downstreams need either form
- `shared_module()` is for loadable modules that are not linked as normal libraries

Do not pick a library type just because a snippet happened to use it.

## Generated sources

Generated code should be created from the build tree, not committed to source control.

```meson
protoc = find_program('protoc', required: true)

proto = custom_target(
  'generated-proto',
  input: 'schema.proto',
  output: ['schema.pb.h', 'schema.pb.cc'],
  command: [protoc, '--cpp_out=@OUTDIR@', '@INPUT@'],
)
```

Use `custom_target()` when you need one-off commands and `generator()` when the same tool is applied repeatedly to many inputs.

## Reproducibility and cleanup

- prefer explicit versioned dependencies
- avoid environment-sensitive command discovery where possible
- keep machine files under version control for cross builds
- keep generated output out of the source tree
- use `summary()` to print final configuration choices clearly
- prefer deterministic generation scripts and pinned tool versions in CI

## Vendoring costs

Vendoring is convenient, but it is not free.

Costs include:

- duplicated security updates
- larger source trees
- multiple ABI copies
- inconsistent patching across downstreams
- maintenance burden when the vendored project changes its own build rules

Prefer a system dependency when packaging rules and platform support allow it. Vendor only when the project genuinely needs a fallback.

## What belongs elsewhere

- complete examples: `meson-patterns-cookbook`
- install layout and releases: `meson-package-export-distribution`
- CI recipes: `meson-ci-cd-integration`
- dependency fallbacks and vendoring policy: `meson-subprojects-management`
- version and deprecation details: `meson-version-compatibility`

## Common mistakes

- keeping optional features as hardcoded booleans
- copying compiler flags into every consumer manually
- generating files into the source tree
- building the same dependency both as a system package and as a vendored copy without a policy
- letting target-local behavior leak into global build state

Read [reference.md](reference.md) when exact feature-option, dependency-object, library-type, generator, or layout syntax matters. Read [troubleshooting.md](troubleshooting.md) when arguments leak, generated files are misplaced, or consumers cannot use an exported target.
