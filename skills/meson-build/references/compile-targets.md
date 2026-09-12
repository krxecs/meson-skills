# Compile targets

Use a configured build directory. List targets before guessing a selector.

```bash
meson introspect builddir --targets
meson compile -C builddir app
meson compile -C builddir app:executable
meson compile -C builddir -j 4
meson compile -C builddir -v
```

`meson compile` forwards to the configured backend. Omit `-j`, or pass a value below 1, to let the backend choose its worker count. Qualified selectors use the path and output suffix from introspection when names collide. Do not use source paths as selectors.

`meson compile -C builddir --clean` only cleans. Run compile again to rebuild. Recreate configuration with `meson setup builddir --wipe` only after resolving the exact disposable directory. Keep Ninja, Visual Studio, and Xcode arguments in local diagnostics or backend-specific CI jobs:

```bash
meson compile -C builddir --ninja-args='-d explain' target-name
meson compile -C builddir --vs-args='/v:quiet'
meson compile -C builddir --xcode-args='-quiet'
```

Declare targets with explicit names. Pass libraries through `link_with` and external interfaces through `dependencies`.

```meson
app = executable('myapp', 'src/main.cpp', include_directories: include_directories('include'), install: true)
```

For a compile failure, rerun the narrow target with `-v`, then read the first compiler or linker diagnostic. Check sources, includes, generated inputs, dependencies, and language arguments. Model generated inputs through `input`, `output`, target sources, or `link_depends`. If a change does not rebuild, reconfigure, clean, then compile. Inspect `meson introspect builddir --compilers` and the built file when output architecture is wrong. A changed cross file needs a fresh configuration.

The check is complete when the requested target compiles, or the recorded first diagnostic identifies the blocking compiler, linker, source, or dependency issue.
