---
name: meson-testing-installation
description: Run Meson tests and installation checks. Use for test names or suites, failure logs, test wrappers, install prefixes, staging with `DESTDIR`, dry runs, and install tags.
---

# Meson testing and installation

Tests run from the build tree. Installation copies only artifacts declared for installation.

## Workflow

1. Inspect the configured build directory and list tests or the install plan when scope is unclear.
2. Run the narrow test or staging install requested.
3. Capture failure logs or inspect the staged tree.
4. Report the command and result. A successful compile does not prove tests or installation.

## Test commands

```bash
meson test -C builddir
meson test -C builddir --list
meson test -C builddir core
meson test -C builddir --suite unit
meson test -C builddir --print-errorlogs
```

Useful options include:

| Option | Effect |
|---|---|
| `--no-rebuild` | Runs tests without rebuilding first |
| `--gdb` | Runs the selected test under GDB |
| `--wrapper COMMAND` | Runs tests through a tool such as Valgrind |
| `--benchmark` | Runs benchmarks instead of ordinary tests |
| `-j N` | Sets the number of concurrent test processes |

Define suites in `meson.build` when users need stable groups:

```meson
test('core', core_test, suite: 'unit')
```

## Install commands

Set the final prefix during setup. Use `--destdir` to prepend a temporary package root.

```bash
meson setup builddir --prefix=/usr
meson install -C builddir --dry-run
meson install -C builddir --destdir "$PWD/stage"
```

Inspect the staged tree under `stage/usr` for this example. A staging install must not write into the live prefix.

## Install checks

- Every public target has `install: true` where required.
- Public headers and data use the matching install helper.
- Private headers and build helpers stay out of the install tree.
- Shared libraries carry the intended ABI version.
- Downstream metadata points to installed paths, not build-tree paths.

## Common mistakes

- assuming compilation runs the tests
- using `--no-rebuild` with stale artifacts
- treating `DESTDIR` as the final installation prefix
- testing paths that only exist in the source checkout
- checking a dry run without checking the staged files

Read [reference.md](reference.md) for test metadata and install helpers. Read [troubleshooting.md](troubleshooting.md) when tests are missing, logs are hidden, or installed files land in the wrong path. Use `meson-package-export-distribution` for pkg-config metadata and releases.
