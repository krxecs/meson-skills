# Meson subproject reference

## Wrap sources

- `wrap-file` downloads an archive.
- `wrap-git` checks out a Git repository.
- A source subproject can live directly under `subprojects/` without a wrap.
- Patch files belong beside the wrap that applies them.

Pin downloaded content to a reviewed release, commit, and hash where the wrap format supports them.

## Dependency fallback

```meson
foo_dep = dependency('foo', fallback: ['foo', 'foo_dep'])
```

The first value names the subproject. The second names the dependency variable that it exports.

Use an explicit branch when the project needs custom fallback behavior:

```meson
foo_dep = dependency('foo', required: false)
if not foo_dep.found()
  foo_project = subproject('foo')
  foo_dep = foo_project.get_variable('foo_dep')
endif
```

## Boundaries

- Keep subprojects under the top-level `subprojects/` directory.
- Let the parent choose whether system or fallback dependencies win.
- Let each subproject define its own targets and local arguments.
- Export one `declare_dependency()` object to consumers.
- Preserve an upstream subproject's language standards unless an override is tested and documented.

## Cache cleanup

```bash
meson subprojects purge --confirm --include-cache
```

This command deletes downloaded source trees and cached packages. Confirm the selected source directory and whether downloads are recoverable before running it.
