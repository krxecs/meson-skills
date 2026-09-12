# Version compatibility

The repository baseline is `meson_version: '>=1.7.0'`. It comes from the existing distribution policy: compare current Ubuntu LTS, Debian stable, and Fedora stable releases using their official package indexes and select the oldest Meson version. Do not replace this policy with an API-derived minimum.

Set the baseline in every example unless a documented feature requires a newer release. Inspect used APIs and options against the official reference and release notes. Use a baseline-supported equivalent when practical. Configure examples with Meson 1.7.0 and document every higher-version exception.

Use `meson.project_source_root()` instead of `meson.source_root()`, `meson.project_build_root()` instead of `meson.build_root()`, `meson.get_external_property()` instead of `meson.get_cross_property()`, and `meson.can_run_host_binaries()` instead of `meson.has_exe_wrapper()`.

Keep version notes beside the feature that needs them. Distinguish Meson constraints from compiler, linker, and backend constraints. Avoid historical compatibility ladders unless migration is the topic.

The check is complete when every `project()` keeps the baseline or names its required exception, and the exact baseline configures the examples.
