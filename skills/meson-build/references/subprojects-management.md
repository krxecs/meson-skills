# Subprojects and dependency fallbacks

Inspect `dependency()`, wrap files, and exported variables. Let the parent choose a system dependency, fallback, or forced fallback, then pass one dependency object to consumers.

```meson
foo_dep = dependency('foo', fallback: ['foo', 'foo_dep'])
```

The first fallback item is the subproject name. The second is its top-level exported variable.

```meson
# subprojects/foo/meson.build
foo_dep = declare_dependency(include_directories: inc, link_with: foo_lib)

# Parent with custom fallback policy
foo_dep = dependency('foo', required: false)
if not foo_dep.found()
  foo_project = subproject('foo')
  foo_dep = foo_project.get_variable('foo_dep')
endif
```

Prefer system packages. Vendor when a reviewed version is unavailable, builds are inconsistent across supported targets, an offline build is required, upstream recommends bundling, or packaging policy makes a fallback safer. Keep source subprojects and wraps under top-level `subprojects/`; version-control wraps and patches. `wrap-file` downloads an archive, `wrap-git` checks out a repository, and source subprojects can be in-tree. Pin downloaded content to reviewed versions, commits, and hashes.

Use `meson wrap install`, `meson subprojects download`, and `meson subprojects update` as needed. Cache compiler results and `subprojects/packagecache`, not arbitrary build directories. `meson subprojects purge --confirm --include-cache` deletes downloaded sources and cached packages. Confirm recoverability and local patches first.

Use `--wrap-mode=nofallback` for system-only packaging and `--force-fallback-for=foo` to select a fallback. Inspect `meson-logs/meson-log.txt` when the wrong source wins. Preserve an upstream subproject's standard unless a tested, documented override exists. Keep subproject arguments local and do not duplicate a dependency through system and vendored paths.

The check is complete when normal and required fallback configurations resolve the intended dependency object.
