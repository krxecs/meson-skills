# Troubleshoot advanced Meson project design

## A generator writes into the source tree

Pass source files as `input` and write to `@OUTPUT@`. Resolve helper scripts from the source directory because build-time commands run from the build tree.

```meson
gen_script = files('scripts/generate.py')
generated = custom_target(
  'generated-header',
  input: 'schema.txt',
  output: 'generated.hpp',
  command: [python, gen_script, '@INPUT@', '@OUTPUT@'],
)
```

Correct the command before changing ignore rules. If a generated file is already tracked, removing it from version control is a separate repository change.

## Arguments affect unrelated targets

`add_project_arguments()` affects every later target in the current project. Use target arguments for target-local behavior:

```meson
mylib = library(
  'mylib',
  'src/mylib.cpp',
  cpp_args: ['-DINTERNAL_BUILD'],
)
```

## A feature option still requires its dependency

Pass the feature option object to `required`:

```meson
wayland_option = get_option('wayland')
wayland_dep = dependency('wayland-client', required: wayland_option)
```

When the option is disabled, `dependency()` returns a not-found object. When it is enabled, a missing dependency stops setup.

## A parent cannot retrieve a subproject dependency

Assign the dependency object to a top-level variable in the subproject:

```meson
mylib_dep = declare_dependency(
  include_directories: inc,
  link_with: mylib,
)
```

The parent can then call `subproject_object.get_variable('mylib_dep')`.

## A generated header is unavailable to a target

Pass the custom target as a source and add the build directory that contains its output:

```meson
generated = custom_target('generated-header', output: 'generated.hpp', command: command)
generated_inc = include_directories('.')

app = executable(
  'app',
  'src/main.cpp',
  generated,
  include_directories: generated_inc,
)
```

Keep the target and its consumer in the same Meson subdirectory when using `include_directories('.')`. Otherwise, expose the exact build-relative include directory.

## A library works in one form only

Check what the consumer needs:

- Static consumers need all transitive link dependencies.
- Shared libraries need exported symbols and a discoverable runtime file.
- Modules built with `shared_module()` are loaded at runtime and are not ordinary link dependencies.

Use `library()` only when both static and shared outputs follow the same public contract.
