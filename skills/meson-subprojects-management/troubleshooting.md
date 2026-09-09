# Troubleshoot Meson subprojects

## A subproject is not found

Confirm that a matching directory or wrap exists under the top-level `subprojects/` directory. Inspect `--wrap-mode` before assuming fallback is enabled.

## The wrong source wins

Read `meson-logs/meson-log.txt` to see whether Meson resolved a system package, CMake package, cached wrap, or source subproject. Reconfigure with the intended policy:

```bash
meson setup builddir --reconfigure --force-fallback-for=foo
```

Use `--wrap-mode=nofallback` when the build must use system dependencies.

## A fallback exports the wrong variable

Match the second item in `fallback: ['foo', 'foo_dep']` to a top-level variable in `subprojects/foo/meson.build`. That variable should usually hold a `declare_dependency()` result.

## Cached sources are stale

Inspect the wrap revision and cached directory first. If the cache may be discarded and downloaded again, run:

```bash
meson subprojects purge --confirm --include-cache
meson subprojects download
```

The purge is destructive. Record local patches or offline requirements before running it.

## Downstream packaging forbids vendoring

Keep the fallback for development only if policy permits it. Configure the packaging job with `--wrap-mode=nofallback` and verify that all required system dependencies resolve.
