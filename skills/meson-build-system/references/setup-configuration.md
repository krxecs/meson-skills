# Setup and configuration

`meson setup` creates the build directory and selects compilers, toolchain, and options. Inspect `project()`, `meson.options`, existing build directories, and machine files before choosing a command.

```bash
meson setup builddir -Dwarning_level=3
meson configure builddir -Dbuildtype=release
meson setup builddir --reconfigure --clearcache
meson setup builddir --wipe
meson introspect builddir --buildoptions
```

Set compiler variables before first setup. Use `meson configure` for option changes, `--reconfigure` to refresh build state, and `--wipe` only after confirming the directory's artifacts can go. `--clearcache` clears cached dependency results and requires Meson 1.3.0.

Use `debug` for development, `debugoptimized` for an optimized developer build, `release` for shipping, `minsize` when size matters, and `plain` to avoid Meson-imposed defaults. Keep project defaults in `project(default_options: ...)` and project options in `meson.options`. Use built-in options for standards and warnings instead of raw `-std=` flags. Setup also accepts `--prefix`, `--bindir`, `--includedir`, `--libdir`, `--datadir`, `--libexecdir`, `--backend`, `--optimization`, `--debug`, `--strip`, `--warnlevel`, `--werror`, `--auto-features`, `--wrap-mode`, `--force-fallback-for`, `--pkg-config-path`, and `--cmake-prefix-path`.

```bash
CC=clang CXX=clang++ meson setup builddir -Db_lto=true
meson setup builddir -Db_lto=true -Db_lto_mode=thin
meson setup builddir -Db_sanitize=address
meson setup builddir --native-file native.ini
meson setup builddir --cross-file cross.ini
```

During a migration, read CMake, Autotools, Makefiles, CI, and compiler scripts for existing language standard choices. Ask when they do not establish one. Do not change standards silently. New projects must record the chosen compiler-supported standards in `default_options`.

If Meson is missing, install it and put it on `PATH`. A compiler picked at first setup requires a new or wiped build when it changes. Reconfigure ignored options. Check `--cross-file` and `--native-file` separately when output shape is wrong. Use introspection to confirm an unexpected build type.

The check is complete when Meson reports the requested compilers and options through `meson configure` or introspection.
