# Troubleshoot Meson target builds

## Target not found

List configured targets before changing `meson.build`:

```bash
meson introspect builddir --targets
```

Use the exact short name or fully qualified selector from the result. A missing dependency during `meson setup` is a configuration failure, not a missing compile target.

## Compilation fails

Rerun the narrow target with verbose output:

```bash
meson compile -C builddir target-name -v
```

Read the first compiler diagnostic and its command line. Check the target's sources, include directories, generated inputs, dependencies, and language-specific arguments.

## Linking fails

Use the verbose link command to identify the missing or duplicate symbol and the libraries passed to the linker.

```bash
meson compile -C builddir target-name -v
meson introspect builddir --targets
nm builddir/path/from/introspection | grep 'symbol_name'
```

Pass libraries with `link_with` or dependency objects with `dependencies`. Do not copy a dependency object's raw flags into consumers.

## A change does not rebuild

Ask the backend why it considers the target current:

```bash
meson compile -C builddir --ninja-args='-d explain' target-name
```

Check that generated inputs are modeled through `input`, `output`, target sources, or `link_depends`. Then try the supported recovery sequence:

```bash
meson setup builddir --reconfigure
meson compile -C builddir --clean
meson compile -C builddir target-name
```

Use `meson setup builddir --wipe` only after resolving the exact build directory and accepting the loss of its artifacts. Do not delete Ninja state files by hand.

## The optimization level is wrong

Inspect the effective option before changing it:

```bash
meson introspect builddir --buildoptions
meson configure builddir -Dbuildtype=release
meson compile -C builddir target-name
```

Machine files and explicit `optimization` or language arguments may override what a build type suggests. Confirm the compiler command with `-v`.

## A subproject output is unavailable

Export a dependency object from the subproject and retrieve that variable in the parent:

```meson
# subprojects/mylib/meson.build
mylib_lib = library('mylib', sources)
mylib_dep = declare_dependency(link_with: mylib_lib)

# parent meson.build
mylib_project = subproject('mylib')
mylib_dep = mylib_project.get_variable('mylib_dep')
```

## The output architecture is wrong

Inspect the configured compilers and built file:

```bash
meson introspect builddir --compilers
file builddir/path/to/target
```

Changing a cross file requires a fresh configuration. Use a new build directory or `meson setup builddir --wipe --cross-file path/to/cross.ini`.
