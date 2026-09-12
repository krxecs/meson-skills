# Shared library

Build a C shared library with a stable C ABI and a C++ consumer. The project
installs its public header, exports an in-tree `declare_dependency()`, and
generates pkg-config metadata for installed consumers. The Windows export
macros also let the in-tree consumer build with MSVC when pkg-config is not
available.

```bash
meson setup build
meson compile -C build
meson test -C build

# Stage an install without writing to the real prefix.
meson install -C build --destdir "$PWD/stage"

# On systems with pkg-config, compile a separate downstream consumer.
PKG_CONFIG_PATH="$PWD/stage/usr/local/lib/pkgconfig" \
PKG_CONFIG_SYSROOT_DIR="$PWD/stage" \
  c++ downstream.cpp $(pkg-config --cflags --libs shared-library) -o downstream
```

The staged pkg-config directory may be under `lib64` or another `libdir`; use
the path reported by the staged tree on those systems. Pkg-config is an
installed-package check, not a requirement for the in-tree or MSVC consumer.
