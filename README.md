<!--
SPDX-License-Identifier: 0BSD
-->

# Meson skills _(meson-skills)_

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

A [model-invoked agent skill](https://agentskills.io/) for the Meson build system.

## Table of Contents

- [Skill](#skill)
- [Usage](#usage)
- [References](#references)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Skill

[`meson-build-system`](skills/meson-build-system/) covers general Meson work and routes detailed guidance through local references. It covers setup and configuration, targets, tests, installation, cross-compilation, freestanding projects, subprojects, CI, debugging, version compatibility, project design, packaging, distribution, and runnable examples.

## Usage

```sh
npx skills add krxecs/meson-skills
```

## References

The skill's [references](skills/meson-build-system/references/) hold topic-specific procedures, syntax, troubleshooting, and completion criteria. The repository baseline remains Meson 1.7.0.

## Examples

The [example index](skills/meson-build-system/examples/README.md) lists five runnable projects. It covers ordinary builds, cross-machine constraints, a shared-library distribution boundary, runtime modules, and fallback dependencies.

## Contributing

Unless you explicitly state otherwise, any contribution intentionally submitted
for inclusion in the work by you, shall be licensed as below, without any
additional terms or conditions.

## License

Licensed under the BSD Zero Clause License. See [LICENSE file](LICENSE.md) in
the project root, or https://opensource.org/licenses/0BSD for full license
information.

The [SPDX](https://spdx.dev) license identifier for this project is `0BSD`.
