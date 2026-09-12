# Plugin system

Build a host executable and a shared module plugin. The test passes the built
module path to the host, which loads the module and calls both exported entry
points.

```bash
meson setup build
meson compile -C build
meson test -C build
```

On Unix-like systems the host uses `dlopen()` and `dlsym()`. On Windows it uses
`LoadLibrary()` and `GetProcAddress()`.
