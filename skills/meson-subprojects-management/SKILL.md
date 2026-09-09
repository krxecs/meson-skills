---
name: meson-subprojects-management
description: Manage Meson subprojects and dependency fallbacks. Use for `.wrap` files, WrapDB, vendored sources, package caches, `subproject()`, or choosing between system and bundled dependencies.
---

# Meson subprojects and dependencies

## Workflow

1. Inspect the existing `dependency()`, wrap file, and exported subproject variable.
2. Decide whether the system package, fallback, or forced fallback should win.
3. Keep that decision at the highest practical project level and pass one dependency object to consumers.
4. Configure once with the normal policy and once with the required fallback policy when both paths are supported.

## Core policy

Prefer a system dependency when possible.

Vendor only when one of these is true:

- a strict version is not widely available yet
- a dependency is difficult to build consistently on all target platforms
- an offline or self-contained build is required
- the upstream project explicitly recommends bundling
- downstream packaging rules make the fallback path the least risky choice

## Quick start

```meson
zlib_dep = dependency('zlib', fallback: ['zlib', 'zlib_dep'])
```

That is the standard pattern: prefer the system dependency first, then fall back to the subproject if needed.

## How subprojects should look

A subproject should export a dependency object, not just a built library.

```meson
# inside the subproject
mylib_dep = declare_dependency(
  include_directories: inc,
  link_with: mylib,
)
```

Then the parent project consumes one object instead of rebuilding its dependency graph by hand.

## Wrap workflow

- `meson wrap install <name>` to fetch a wrap definition
- `meson subprojects download` to fetch sources
- `meson subprojects update` to refresh them
- `meson subprojects purge --confirm --include-cache` to clean stale wrap artifacts

## Wrap-cache and CI policy

Cache wrap downloads, not the whole build tree, unless you have a narrow and well-tested reason to restore the build tree itself. The safe general cache targets are:

- the compiler cache
- `subprojects/packagecache`
- downloaded wraps and archives

## Dependency decision tree

1. Try the system dependency.
2. If the dependency is optional, leave it disabled when not present.
3. If the dependency is required and not present, try the fallback path.
4. If the fallback path is enabled, use the dependency object exported by the subproject.
5. Avoid mixing multiple dependency resolution strategies in the same leaf target unless there is a documented reason.

## Rules that matter in real projects

- keep `subprojects/` at the top level
- do not set global compiler arguments from subprojects
- avoid duplicating the same dependency through multiple paths
- prefer one dependency decision at the top level
- keep wrap files and patch files version-controlled if the project depends on them
- do not let subprojects silently rewrite parent policy

## Good fallback pattern

```meson
auto_dep = dependency('foo', required: false)
if not auto_dep.found()
  foo_proj = subproject('foo')
  auto_dep = foo_proj.get_variable('foo_dep')
endif
```

## When not to vendor

Do not vendor a dependency just because it is convenient today.

Avoid vendoring when:

- the system package is already reliable
- the dependency is large and slow to patch
- the dependency ABI matters more than the specific source snapshot
- the dependency is already well-supported by packaging ecosystems

## Common mistakes

- calling `subproject()` from deep inside nested build logic
- propagating build flags from the subproject into global state
- vendoring two different copies of the same dependency
- mixing system and vendored copies without a clear policy
- treating subprojects as a dumping ground for anything that is hard to build

## What belongs elsewhere

- build-system basics: `meson-build-system`
- CI cache strategy for wraps: `meson-ci-cd-integration`
- dependency design and interfaces: `meson-advanced-project-design`
- install and export packaging: `meson-package-export-distribution`

## Language standards in subprojects

Preserve an upstream subproject's standard choice unless the project has tested a local override:

```meson
# Vendored upstream subproject
project('mylib', 'c', default_options: ['c_std=c11'])
```

For a new subproject that you control, align its standards with the parent unless a target requires another value.

Read [reference.md](reference.md) for wrap types and dependency boundaries. Read [troubleshooting.md](troubleshooting.md) when resolution selects the wrong version, cache, or source.
