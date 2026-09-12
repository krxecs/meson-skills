<!--
SPDX-License-Identifier: 0BSD
-->

# Meson skills _(meson-skills)_

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

Two [model-invoked agent skills](https://agentskills.io/) for the Meson build system.

## Table of Contents

- [Skills](#skills)
- [Usage](#usage)
- [References](#references)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Skills

- [`meson-build`](skills/meson-build/) covers creating and working on Meson projects. It routes setup, targets, tests, installation, cross-compilation, subprojects, CI, debugging, project design, packaging, and distribution through focused references.
- [`convert-to-meson`](skills/convert-to-meson/) converts an existing C or C++ project from CMake, Autotools, Make, or another build system while preserving its observable build behavior.

## Usage

```sh
npx skills add krxecs/meson-skills
```

## References

The skills' references hold topic-specific procedures, source-build mappings, troubleshooting guidance, and completion criteria. The repository baseline remains Meson 1.7.0.

## Examples

The [`meson-build` example index](skills/meson-build/examples/README.md) lists five runnable projects. It covers ordinary builds, cross-machine constraints, a shared-library distribution boundary, runtime modules, and fallback dependencies.

## Contributing

Unless you explicitly state otherwise, any contribution intentionally submitted
for inclusion in the work by you, shall be licensed as below, without any
additional terms or conditions.

## License

Licensed under the BSD Zero Clause License. See [LICENSE file](LICENSE.md) in
the project root, or https://opensource.org/licenses/0BSD for full license
information.

The [SPDX](https://spdx.dev) license identifier for this project is `0BSD`.
