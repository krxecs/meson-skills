---
name: meson-compile-targets
description: Compile selected Meson targets and inspect target names. Use for `meson compile`, parallel jobs, verbose output, clean builds, or backend-specific Ninja, Visual Studio, and Xcode arguments.
---

# Compile Meson targets

Use the configured build directory. Run `meson setup` first when none exists.

## Workflow

1. Find the build directory and configured backend.
2. List targets when the requested selector is uncertain.
3. Compile the smallest target set that proves the change.
4. Use verbose output for a failure, then report the failing compiler or linker command.

The compile step is complete when the requested target succeeds. If it fails, preserve the first useful diagnostic and route broader diagnosis to `meson-debugging-troubleshooting`.

## Common commands

```bash
meson compile -C builddir
meson compile -C builddir app
meson compile -C builddir app tests
meson compile -C builddir -j 4
meson compile -C builddir -v
```

Values below 1 for `-j` let the backend choose its worker count. Omitting `-j` also uses the backend default.

## Find target selectors

```bash
meson introspect builddir --targets
```

A qualified selector ends in `:type`. Add the path and output suffix shown by introspection when duplicate target names make them necessary.

```bash
meson compile -C builddir app:executable
meson compile -C builddir core:static_library
```

Do not infer selectors from source filenames. Use introspection output.

## Clean builds

`--clean` cleans the configured build directory. Run a second command to rebuild it.

```bash
meson compile -C builddir --clean
meson compile -C builddir
```

Use `meson setup builddir --wipe` when the configuration itself must be recreated. Resolve the build directory's exact path and confirm that its artifacts are disposable before wiping it.

## Backend arguments

Pass backend-specific arguments only when Meson's common options cannot express the request.

```bash
meson compile -C builddir --ninja-args='-d explain'
meson compile -C builddir --ninja-args='-k 0'
meson compile -C builddir --vs-args='/v:quiet'
meson compile -C builddir --xcode-args='-quiet'
```

Backend arguments reduce portability. Keep them in local debugging commands or backend-specific CI jobs.

## Common mistakes

- using a source path as a target selector
- assuming `--clean` also rebuilds
- passing Ninja arguments to another backend
- increasing parallelism without checking memory or load limits
- rebuilding every target when one target proves the change

Read [reference.md](reference.md) for target declarations and inspection commands. Read [troubleshooting.md](troubleshooting.md) after a target is resolved but compilation or linking still fails.
