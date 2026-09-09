# Troubleshoot `meson setup`

## `meson setup: command not found`

Install Meson first and make sure it is on `PATH`.

## Build directory already configured

The source tree already has a build directory attached. Choose the approach that matches your intent:

Reconfigure in place to preserve build artifacts:
```bash
meson setup builddir --reconfigure
```

Resolve the build directory and use Meson's wipe operation to remove its artifacts:
```bash
meson setup builddir --wipe
```

## Wrong compiler is used

The compiler was probably chosen during the first setup. Change the environment before setup, or wipe the build directory and configure again.

## Option changes are ignored

Run `meson setup builddir --reconfigure` or `meson configure builddir` after changing options.

## Stale cache after a toolchain change

Clear cached dependency results during reconfiguration:

```bash
meson setup builddir --reconfigure --clearcache
```

## Cross/native file confusion

If the wrong machine file is used, Meson may configure the build successfully but produce the wrong target shape. Recheck `--cross-file` and `--native-file` separately.

## Build type does not match expectations

Confirm the build type explicitly:

```bash
meson introspect builddir --buildoptions
```

Then reconfigure with the desired build type.

## Common mistakes

- changing environment variables after `meson setup` and expecting Meson to rediscover the compiler
- editing `meson.build` and forgetting to reconfigure when options changed
- assuming `--reconfigure` fixes a bad machine file
- treating `--clearcache` as a substitute for a bad toolchain selection

Use `meson-setup-configuration` when the problem is choosing a language standard rather than diagnosing setup state.
