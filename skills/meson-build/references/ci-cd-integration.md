# CI and CD integration

Inspect supported platforms, machine files, dependency sources, and existing local commands. Reuse those commands in CI. Run setup, compile, tests, and the requested staging or package checks. Preserve logs and reports that explain failures.

```bash
meson setup builddir -Dwarning_level=3
meson compile -C builddir
meson test -C builddir --print-errorlogs
meson install -C builddir --destdir "$PWD/stage"
```

Cache compiler results such as `~/.cache/ccache` or `~/.cache/sccache`, wrap downloads in `subprojects/packagecache`, and CI artifacts. Derive cache keys from Meson, compiler, source tree, machine and native files, wraps, and options. A build directory is reusable only when that entire configuration is the same. Use narrow build-directory caching only for a pinned, stable, intentionally optimized job.

```yaml
name: ci
on: [push, pull_request]
jobs:
  build:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        buildtype: [debugoptimized, release]
    steps:
      - uses: actions/checkout@v4
      - uses: actions/setup-python@v5
        with: {python-version: '3.12'}
      - run: python -m pip install meson ninja
      # Template: point the source directory at the project under test.
      - run: meson setup builddir skills/meson-build/examples/basic-build --buildtype=${{ matrix.buildtype }} -Dwarning_level=3
      - run: meson compile -C builddir
      - run: meson test -C builddir --print-errorlogs
```

Pin Meson, Ninja, and compiler versions when possible. Use matrices for operating systems and build types, include sanitizers, upload logs and test reports, and separate clean release or packaging jobs. `meson introspect builddir --targets --tests --dependencies --buildoptions` can record the configured shape.

Install Meson and Ninja explicitly when jobs lack them. Reconfigure a mismatched restored build with `--clearcache`, then wipe only the exact invalid build directory. Check runtime dependencies, `exe_wrapper`, and local-only environment assumptions when CI tests differ. Adjust cache keys to the actual invalidating inputs.

The check is complete when each required CI job configures, compiles, tests, and stages or packages its declared outputs.
