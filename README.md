<!--
SPDX-License-Identifier: 0BSD
-->

# Meson skills _(meson-skills)_

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

A collection of [agent skills](https://agentskills.io/) for the Meson build system.

## Table of Contents

- [Skills](#skills)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Skills

The repository contains these agent skills, grouped by topic.

### Core Skills

- [meson-build-system](skills/meson-build-system/) covers Meson fundamentals.

### Configuration & Setup

- [meson-setup-configuration](skills/meson-setup-configuration/) covers project options, dependencies, and initial setup.
- [meson-version-compatibility](skills/meson-version-compatibility/) covers version requirements, deprecations, and migrations.

### Building & Compilation

- [meson-compile-targets](skills/meson-compile-targets/) covers declaring, inspecting, and building targets.
- [meson-cross-compilation](skills/meson-cross-compilation/) covers builds for different platforms and architectures.

### Testing & Installation

- [meson-testing-installation](skills/meson-testing-installation/) covers tests, test suites, and artifact installation.

### Advanced Features

- [meson-subprojects-management](skills/meson-subprojects-management/) covers wraps, vendored dependencies, and subproject fallbacks.
- [meson-advanced-project-design](skills/meson-advanced-project-design/) covers feature options, generated sources, and reusable interfaces for complex projects.
- [meson-patterns-cookbook](skills/meson-patterns-cookbook/) contains examples and project layout patterns.

### Specialized Topics

- [meson-ci-cd-integration](skills/meson-ci-cd-integration/) covers GitHub Actions, GitLab CI, and other CI platforms.
- [meson-package-export-distribution](skills/meson-package-export-distribution/) covers packaging, installation exports, and releases.
- [meson-debugging-troubleshooting](skills/meson-debugging-troubleshooting/) covers setup, compile, and test failures.
- [meson-freestanding-projects](skills/meson-freestanding-projects/) covers embedded and freestanding applications.

## Usage

```sh
npx skills add krxecs/meson-skills
```

## Contributing

Unless you explicitly state otherwise, any contribution intentionally submitted
for inclusion in the work by you, shall be licensed as below, without any
additional terms or conditions.

## License

Licensed under the BSD Zero Clause License. See [LICENSE file](LICENSE.md) in
the project root, or https://opensource.org/licenses/0BSD for full license
information.

The [SPDX](https://spdx.dev) license identifier for this project is `0BSD`.
