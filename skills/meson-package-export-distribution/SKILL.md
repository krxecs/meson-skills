---
name: meson-package-export-distribution
description: Package and export Meson projects. Use for install layout, pkg-config metadata, shared-library versions, staged installs, `meson dist`, release archives, or downstream package consumers.
---

# Meson package export and distribution

## Workflow

1. Identify the public headers, libraries, programs, data, and metadata.
2. Inspect the configured prefix and every install declaration.
3. Stage the install under `DESTDIR` and inspect the resulting tree.
4. Test one downstream consumer against the staged metadata when the package exports a library.
5. Run `meson dist` only from a clean, configured source checkout.

## Install the right things

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

```meson
inc = include_directories('include')
lib = library(
  'mylib',
  'src/mylib.cpp',
  include_directories: inc,
  version: '1.2.0',
  soversion: '1',
  install: true,
)

install_headers('include/mylib/mylib.hpp', subdir: 'mylib')
```

This installs the public API and keeps private implementation details out of the package.

## Export a pkg-config file

```meson
pkg = import('pkgconfig')
pkg.generate(
  lib,
  description: 'My reusable library',
  filebase: 'mylib',
  subdirs: 'mylib',
)
```

That makes the library easy to consume from other Meson projects and from non-Meson consumers that use pkg-config.

## ABI and shared library versioning

If the library has a stable ABI, version it intentionally:

- `version` tracks the project release
- `soversion` tracks the ABI family

Use both when the library is intended for downstream reuse.

## Relocatable installs

Prefer install layouts that do not bake build-tree paths into installed files. Keep generated `.pc` files and config files portable when possible.

If a package needs a prefix-relative install, structure it deliberately and document the assumption.

## Support staging installs

Use `DESTDIR` during packaging and keep prefixes relocatable.

```bash
meson install -C builddir --destdir "$pkgdir"
```

## Release tarballs

Use `meson dist` for source distributions when the project is set up to build from a clean tree.

```bash
meson dist -C builddir
```

## Downstream packaging targets

A good packaging story should cover:

- Linux distro packaging
- local binary package staging
- reproducible release tarballs
- developer installs under a custom prefix
- SDK and sysroot exports when relevant

## Interoperability options

### pkg-config

Use for projects that expose libraries to many consumers.

### CMake package exports

Use when downstream users primarily consume via CMake and need package config files.

### vcpkg and Conan

Document how the project fits those ecosystems instead of assuming every consumer is a Meson user.

## Packaging checklist

- install headers intentionally, not accidentally
- version shared libraries with `version` and `soversion`
- export a dependency object for in-tree reuse
- generate pkg-config metadata for downstream use
- keep runtime data and developer-only files separate
- avoid hardcoded install paths
- document whether the install layout is relocatable
- ensure the installed package can be consumed from another build tree

## Common mistakes

- installing private headers as public API
- shipping unversioned shared libraries for a stable ABI
- forgetting pkg-config metadata
- embedding build-tree paths in installed files
- exporting a build-helper target instead of the actual public library interface

## What belongs elsewhere

- tests and install commands: `meson-testing-installation`
- build-tree structure and dependencies: `meson-advanced-project-design`
- complete examples: `meson-patterns-cookbook`
