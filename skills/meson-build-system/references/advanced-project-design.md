# Advanced project design

Inspect target, directory, dependency, and option boundaries. Change the boundary that causes duplication, hidden state, or unnecessary coupling. Keep public headers separate from private code, generated files in the build tree, targets small, and project policy out of leaf targets.

Keep `meson.build` shallow: top-level project metadata and `subdir()` calls, `meson.options` for options, `include/` for installed headers, `src/` for implementation, `tests/` for test-only code, and `subprojects/` for fallbacks. Put `subdir('src')` before tests when tests link project targets.

Use feature options for optional capabilities:

```meson
# meson.options
option('wayland', type: 'feature', value: 'auto', description: 'Enable Wayland support')

# meson.build
wayland_dep = dependency('wayland-client', required: get_option('wayland'))
```

Use one `declare_dependency()` for each public library interface. Add transitive dependencies only when consumers require them.

```meson
mylib = library('mylib', 'src/mylib.cpp', include_directories: inc, install: true)
mylib_dep = declare_dependency(include_directories: inc, link_with: mylib, dependencies: upstream_dep)
```

Use `static_library()` for internal or embedded reuse, `shared_library()` for a stable ABI, `both_libraries()` when downstreams need both, and `shared_module()` for runtime-loaded plugins. `library()` follows `default_library` when either form satisfies the public contract.

Use `custom_target()` for one command and `generator()` for a tool applied to many inputs. Give commands source inputs and `@OUTPUT@`; resolve scripts from the source directory. Pass generated targets as sources and expose their build directory to consumers. Use `configuration_data()` and `configure_file()` for build-time constants. `summary()` should report final choices.

`add_project_arguments()` affects later targets in the project. Put target-only arguments on the target. Put global arguments at the top level, never in subprojects. Prefer explicit, versioned dependencies, deterministic generators, pinned CI tools, and version-controlled machine files. Consider the update cost, ABI duplication, patches, and packaging support before vendoring.

When an option still requires its dependency, pass the feature object to `required`. When a parent cannot retrieve a subproject interface, export a top-level dependency variable. When a library only works in one form, check static transitive links, shared symbols and runtime paths, and module loading.

The check is complete when affected targets configure and compile, affected tests pass, generated files stay in the build tree, and public consumers receive one complete dependency object.
