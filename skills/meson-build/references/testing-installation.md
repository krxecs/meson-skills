# Testing and installation

Tests run from the build tree. Installation copies only targets and files declared for installation.

```bash
meson test -C builddir --list
meson test -C builddir --suite unit
meson test -C builddir test_name --print-errorlogs
meson install -C builddir --dry-run
meson install -C builddir --destdir "$PWD/stage"
```

Use `test()` to register a test. Use `suite:` for stable groups, `timeout:` for long-running tests, and `should_fail: true` for expected failures. `--no-rebuild` only suits a known-fresh build. `--gdb` and `--wrapper COMMAND` help investigate crashes. `--benchmark` runs benchmarks instead of ordinary tests.

Set the final prefix at setup. `--destdir` prepends a temporary package root and must not write into the live prefix. Inspect the staged tree, including `stage/usr` when the prefix is `/usr`. Declare public targets with `install: true`; use `install_headers()`, `install_man()`, `install_data()`, `install_subdir()`, `install_symlink()`, or `install_emptydir()` for files and directories. Keep private headers and build helpers out of the install tree.

When a test is absent, declare `test('name', test_exe)`. When output is missing, use `--print-errorlogs`. Make tests use absolute or Meson-provided paths instead of a presumed working directory. For install failures, check `install: true`, the helper, `install_dir`, prefix options, and staging permissions. A staged tree that runs incorrectly often lacks a runtime dependency or search path.

The check is complete when affected tests pass and the requested dry-run or staged install has the expected files. A compile alone does not satisfy either check.
