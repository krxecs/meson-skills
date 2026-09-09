# Advanced Meson project design reference

## `declare_dependency()` quick reference

Export a library interface as a single dependency object so consumers never copy flags manually.

```meson
mylib_dep = declare_dependency(
  include_directories: inc,        # public headers
  link_with: mylib,                # library to link against
  dependencies: upstream_dep,      # transitive deps forwarded to consumers
  compile_args: ['-DMYLIB_STATIC'], # only when the interface requires it
)
```

Consumers then use one object:

```meson
executable('myapp', 'main.cpp', dependencies: mylib_dep)
```

## Feature option declaration (`meson.options`)

```ini
option('wayland',  type: 'feature', value: 'auto',    description: 'Enable Wayland support')
option('docs',     type: 'feature', value: 'disabled', description: 'Build documentation')
option('max_conns',type: 'integer', value: 16,         description: 'Maximum connections')
option('backend',  type: 'combo',   choices: ['epoll','kqueue','select'], value: 'epoll')
```

Gate a dependency with the option:

```meson
wayland_opt = get_option('wayland')
wayland_dep = dependency('wayland-client', required: wayland_opt)
if wayland_dep.found()
  add_project_arguments('-DHAVE_WAYLAND', language: 'cpp')
endif
```

## Library type selection

| Type | Declaration | When to use |
|------|-------------|-------------|
| Static | `static_library()` | Internal reuse; embedded targets; no ABI contract |
| Shared | `shared_library()` | Stable ABI; runtime reuse; distro packaging |
| Both | `both_libraries()` | Downstream needs either form |
| Module | `shared_module()` | Loadable plugin; never linked directly |

`library()` respects the `default_library` option. Use it for public libraries when either static or shared output is acceptable.

## `custom_target()` and `generator()`

| | `custom_target()` | `generator()` |
|-|-------------------|---------------|
| Use when | One-off generation (single schema, version header) | Same tool applied to many inputs |
| Output naming | Explicit | Template-based (`@BASENAME@.hpp`) |
| Parallelism | One invocation | One invocation per input |

```meson
# custom_target uses one invocation
version_script = files('scripts/gen_version.py')
version_h = custom_target('version-header',
  input:   'templates/version.in',
  output:  'version.hpp',
  command: [python, version_script, '@INPUT@', '@OUTPUT@'],
)

# generator uses one invocation per input file
message_script = meson.current_source_dir() / 'scripts/gen_message.py'
header_gen = generator(python,
  output:    '@BASENAME@.hpp',
  arguments: [message_script, '@INPUT@', '@OUTPUT@'],
)
message_headers = header_gen.process(files('hello.txt', 'farewell.txt'))
```

Both produce files in the build tree. Never write generated output into the source tree.

## `summary()` usage

Call at the end of the top-level `meson.build` to print the final configuration:

```meson
summary({
  'prefix':   get_option('prefix'),
  'wayland':  wayland_dep.found(),
  'docs':     get_option('docs').enabled(),
}, section: 'Configuration')
```

Meson prints this after `meson setup` so users can confirm what was enabled.

## Subdirectory layout conventions

```text
project/
├── meson.build          # project() + subdir() calls only
├── meson.options        # all option declarations
├── include/             # public headers (installed)
│   └── mylib/
├── src/                 # implementation + private headers
├── tests/               # test-only code
├── subprojects/         # vendored fallbacks (wrap files or in-tree)
└── docs/                # documentation (optional)
```

- `subdir('src')` before `subdir('tests')` so test targets can link against src targets.
- Keep `subdir()` chains shallow enough to inspect without tracing many files.

## `configure_file()` for build-time constants

```meson
conf = configuration_data()
conf.set('VERSION',     meson.project_version())
conf.set('HAVE_WAYLAND', wayland_dep.found())
conf.set_quoted('DATADIR', get_option('prefix') / get_option('datadir'))

configure_file(input: 'config.h.in', output: 'config.h', configuration: conf)
```

Access in code with `#include "config.h"`. The output lives in the build tree.

## Common design rules

- One `declare_dependency()` per public library interface.
- Feature options go in `meson.options`.
- Global arguments (`add_project_arguments`) belong in the top-level `meson.build`, never in subprojects.
- Generated files always go to the build tree (`@OUTPUT@`, not a source path).
- Keep `subdir()` boundaries aligned with ownership: one directory = one team or one public interface.
