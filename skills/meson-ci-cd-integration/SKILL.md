---
name: meson-ci-cd-integration
description: Run Meson in continuous integration. Use for CI matrices, caches, artifacts, coverage, sanitizers, staged installs, and release jobs on GitHub Actions, GitLab CI, Jenkins, or Azure Pipelines.
---

# Meson CI and release automation

## Workflow

1. Inspect the project's supported platforms, machine files, dependency sources, and existing local commands.
2. Reuse those commands in CI before adding matrices, caches, or release jobs.
3. Give each cache a key derived from every input that can invalidate it.
4. Run configure, compile, test, and the requested install or package check.
5. Preserve logs or artifacts needed to diagnose a failed job.

## What CI should verify

- configure cleanly
- compile cleanly
- test cleanly
- install into a staging directory cleanly
- export the expected metadata cleanly
- catch regression in cross-platform behavior early

## Default pipeline

```bash
meson setup builddir -Dwarning_level=3
meson compile -C builddir
meson test -C builddir --print-errorlogs
meson install -C builddir --destdir "$PWD/stage"
```

## Why cache policy matters

A CI cache should speed up repeated work without making stale configuration invisible.

The safe default cache strategy is:

- compiler cache (`ccache` or `sccache`)
- wrap download cache (`subprojects/packagecache`)
- artifacts that are clearly reusable and not build-directory state

Do not treat `build/` as a universal portable cache. Restoring a build directory can help only when the exact same toolchain, source tree, and configure state are still valid. That is why the build-directory caching pattern from Meson issue #9234 should not be the default general-case strategy. For the general case, compiler caches are the safer win.

## GitHub Actions example

```yaml
name: ci
on:
  push:
  pull_request:

jobs:
  build:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        buildtype: [debugoptimized, release]
    steps:
      - uses: actions/checkout@v4
      - uses: actions/setup-python@v5
        with:
          python-version: '3.12'
      - run: |
          sudo apt-get update
          sudo apt-get install -y ccache
          python -m pip install meson ninja
      - uses: actions/cache@v4
        with:
          path: |
            ~/.cache/ccache
            subprojects/packagecache
          key: ${{ runner.os }}-meson-${{ matrix.buildtype }}-${{ hashFiles('meson.build', 'meson.options', '**/*.wrap') }}
      - run: meson setup builddir --buildtype=${{ matrix.buildtype }} -Dwarning_level=3
      - run: meson compile -C builddir
      - run: meson test -C builddir --print-errorlogs
```

## When to cache a build directory

Only do it when:

- the toolchain is pinned
- the source tree is stable
- the build options are stable
- the job is narrow and intentionally optimized for one exact shape

Even then, use a narrow restore policy instead of caching every build directory indefinitely.

## Introspection in CI

Use `meson introspect` to report the build shape and catch unexpected option drift.

```bash
meson introspect builddir --targets
meson introspect builddir --tests
meson introspect builddir --dependencies
meson introspect builddir --buildoptions
```

## CI checks

- pin Meson, Ninja, and compiler versions in the job environment when possible
- use a matrix for operating systems and build types
- run tests with `--print-errorlogs`
- upload logs and test reports as artifacts
- include sanitizer jobs in the matrix
- run packaging jobs separately from normal test jobs
- prefer cache keys that invalidate when source or options change

## Common mistakes

- caching the whole build tree as if it were compiler cache
- forgetting to invalidate caches when toolchains change
- testing only the default buildtype
- not running install or staging checks
- hiding the build shape from the logs

Read [reference.md](reference.md) for cache invalidation and job ordering. Read [troubleshooting.md](troubleshooting.md) when tools are missing, restored state behaves differently, or local and CI results disagree.
