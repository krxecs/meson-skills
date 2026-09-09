# Wrap fallback

This example prefers a system dependency and falls back to a source subproject. It has no `.wrap` file because the subproject lives under `subprojects/`.

```bash
meson setup builddir
meson compile -C builddir
meson test -C builddir
```
