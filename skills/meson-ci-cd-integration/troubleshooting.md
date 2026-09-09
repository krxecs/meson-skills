# Troubleshoot Meson in CI

## `meson: command not found`

Install Meson before the build step and verify the selected Python version.

## `ninja: command not found`

Install Ninja explicitly or use the platform package manager image that already includes it.

## Restored build directory behaves strangely

This usually means the cached build tree no longer matches the compiler, Meson version, options, or source tree.

Reconfigure first:

```bash
meson setup builddir --reconfigure --clearcache
```

If the configuration itself is invalid, resolve the job's exact build directory and recreate it:

```bash
meson setup builddir --wipe
```

## Tests pass locally but fail in CI

Check for missing runtime dependencies, missing `exe_wrapper` in cross jobs, and environment assumptions that only exist on a developer machine.

## Cache misses are too frequent

Use stable cache keys based on the lock-step inputs that actually affect the build:

- Meson version
- compiler version
- wrap files
- machine files
- build options
