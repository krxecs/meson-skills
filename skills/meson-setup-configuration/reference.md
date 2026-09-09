# `meson setup` option reference

Check `meson setup --help` for the installed Meson version. Options added after the project's minimum version need a version note or another spelling.

## Installation directories

| Option | Purpose |
|---|---|
| `--prefix PATH` | Final installation prefix |
| `--bindir PATH` | Executable directory under the prefix |
| `--includedir PATH` | Header directory under the prefix |
| `--libdir PATH` | Library directory under the prefix |
| `--datadir PATH` | Architecture-independent data directory |
| `--libexecdir PATH` | Helper executable directory |

## Build configuration

| Option | Purpose |
|---|---|
| `--buildtype VALUE` | Sets `plain`, `debug`, `debugoptimized`, `release`, or `minsize` defaults |
| `--optimization VALUE` | Sets the optimization level directly |
| `--debug` | Enables debug information |
| `--strip` | Strips installed targets |
| `--backend VALUE` | Selects Ninja, Visual Studio, Xcode, or no backend |
| `--warnlevel VALUE` | Sets the compiler warning level |
| `--werror` | Treats compiler warnings as errors |

Use `-Ddebug=false` or `-Dstrip=false` when a boolean option must be disabled explicitly.

## Feature and dependency control

| Option | Purpose |
|---|---|
| `-Dname=value` | Sets a built-in or project option |
| `--auto-features=VALUE` | Overrides project feature options whose value is `auto` |
| `--wrap-mode=VALUE` | Controls subproject fallback and download behavior |
| `--force-fallback-for=NAMES` | Forces selected dependencies to their fallback |
| `--pkg-config-path=PATHS` | Adds host-machine pkg-config search paths |
| `--cmake-prefix-path=PATHS` | Adds host-machine CMake search prefixes |

Thin link-time optimization uses both options:

```bash
meson setup builddir -Db_lto=true -Db_lto_mode=thin
```

## Machine files

```bash
meson setup builddir --native-file native.ini
meson setup builddir --cross-file cross.ini
```

A native file configures build-machine tools and native builds. A cross file describes the host machine and its toolchain.

## Existing build directories

| Command | Effect |
|---|---|
| `meson configure builddir -Dname=value` | Changes options in place |
| `meson setup builddir --reconfigure` | Regenerates an existing build |
| `meson setup builddir --reconfigure --clearcache` | Also clears cached dependency results; `--clearcache` requires Meson 1.3.0 |
| `meson setup builddir --wipe` | Recreates the build using its recorded command-line options |

Resolve the directory before `--wipe`. It removes build artifacts.

## Examples

```bash
CC=clang CXX=clang++ meson setup builddir -Db_lto=true
meson setup builddir -Db_sanitize=address
meson setup builddir --prefix=/usr
meson configure builddir -Dbuildtype=release
```
