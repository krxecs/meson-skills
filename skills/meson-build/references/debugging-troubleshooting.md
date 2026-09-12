# Debugging and troubleshooting

Start with the exact error and stage: setup, compile, test, or install. Inspect what Meson configured before changing code.

```bash
meson introspect builddir --buildoptions
meson introspect builddir --targets
meson introspect builddir --dependencies
meson introspect builddir --tests
meson compile -C builddir -v
meson test -C builddir --print-errorlogs
meson install -C builddir --dry-run
```

Reproduce one command at a time. Compare source, build directory, machine file, and options with a known-good configuration. A setup failure usually names a toolchain, machine-file, option, or dependency issue. A compile failure usually names a source, include, generated input, or link dependency. A test failure often depends on runtime paths, fixtures, or an absent cross wrapper. An install failure usually lacks install metadata or uses an unexpected path.

For a missing dependency, decide whether it should be a system, pkg-config, CMake, wrap, or subproject dependency. For a stale build, run `meson setup builddir --reconfigure --clearcache`, then wipe only a resolved disposable directory. Use target introspection for an incorrect selector. Wire generated files into target sources through `custom_target()` or `generator()`. Confirm that a cross target can run locally before blaming its test.

Stop when one cause explains the failure and a focused rerun confirms it. Otherwise record the failing command, stage, and first useful diagnostic.
