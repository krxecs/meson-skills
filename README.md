<!--
SPDX-License-Identifier: 0BSD
-->

# Meson Skills _(meson-skills)_

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

A comprehensive collection of educational resources and guided skills for mastering the Meson build system.

## Table of Contents

- [Background](#background)
- [Skills](#skills)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Background

Meson is a modern, declarative build system designed to be both powerful and user-friendly. This project provides a curated collection of learning materials organized as individual "skills"—focused, guided resources covering different aspects of Meson, from basic setup to advanced project architecture.

Whether you're new to Meson or looking to deepen your expertise with cross-compilation, CI/CD integration, or advanced project design patterns, these skills guide you through practical workflows and best practices.

## Skills

The repository contains the following skills, organized by complexity and topic:

### Core Skills

- **[meson-build-system](skills/meson-build-system/)** — Entry point for Meson fundamentals. Learn standard `meson.build` syntax, project structure, and the basic setup-compile-test-install workflow.

### Configuration & Setup

- **[meson-setup-configuration](skills/meson-setup-configuration/)** — Configure projects with options, dependencies, and initial setup.
- **[meson-version-compatibility](skills/meson-version-compatibility/)** — Handle version requirements, deprecations, and migrations.

### Building & Compilation

- **[meson-compile-targets](skills/meson-compile-targets/)** — Declare, inspect, and build targets effectively.
- **[meson-cross-compilation](skills/meson-cross-compilation/)** — Set up builds for different platforms and architectures.

### Testing & Installation

- **[meson-testing-installation](skills/meson-testing-installation/)** — Write tests, manage test suites, and install artifacts.

### Advanced Features

- **[meson-subprojects-management](skills/meson-subprojects-management/)** — Work with wraps, vendored dependencies, and subproject fallbacks.
- **[meson-advanced-project-design](skills/meson-advanced-project-design/)** — Design complex projects with feature options, generated sources, and reusable interfaces.
- **[meson-patterns-cookbook](skills/meson-patterns-cookbook/)** — Complete examples and project layout patterns.

### Specialized Topics

- **[meson-ci-cd-integration](skills/meson-ci-cd-integration/)** — Integrate Meson with GitHub Actions, GitLab CI, and other CI platforms.
- **[meson-package-export-distribution](skills/meson-package-export-distribution/)** — Package projects for distribution, export installations, and manage releases.
- **[meson-debugging-troubleshooting](skills/meson-debugging-troubleshooting/)** — Diagnose and resolve setup, compile, and test failures.
- **[meson-freestanding-projects](skills/meson-freestanding-projects/)** — Build embedded and freestanding applications.

## Usage

Each skill contains:

1. **SKILL.md** — Overview, learning objectives, and routing to related skills
2. **reference.md** — Detailed reference material and API documentation
3. **troubleshooting.md** — Common issues, solutions, and debugging tips
4. **examples/** — Complete, runnable example projects

### Getting Started

1. Start with [meson-build-system](skills/meson-build-system/) if you're new to Meson
2. Navigate to specialized skills based on your needs using the routing table in SKILL.md files
3. Reference the troubleshooting guides when you encounter issues
4. Study the example projects to understand patterns and best practices

### Choosing Your Path

- **Learning Meson basics?** → [meson-build-system](skills/meson-build-system/)
- **Setting up a new project?** → [meson-setup-configuration](skills/meson-setup-configuration/)
- **Building for multiple platforms?** → [meson-cross-compilation](skills/meson-cross-compilation/)
- **Integrating with CI/CD?** → [meson-ci-cd-integration](skills/meson-ci-cd-integration/)
- **Publishing a project?** → [meson-package-export-distribution](skills/meson-package-export-distribution/)

## Contributing

Contributions are welcome! This project follows a standard contribution workflow:

1. Fork the repository
2. Create a feature branch for your changes
3. Make your improvements or additions
4. Submit a pull request with a clear description of your changes

PRs accepted. Please ensure that any contributed skills or examples follow the same structure and include SKILL.md, reference.md, troubleshooting.md, and example files.

For detailed guidelines, see [CONTRIBUTING.md](CONTRIBUTING.md) if it exists, or create an issue to discuss major changes.

## License

© 2024 krxecs and Contributors

Licensed under the BSD Zero Clause License. See [LICENSE file](LICENSE.md) in the project root, or https://opensource.org/licenses/0BSD for full license information.

The [SPDX](https://spdx.dev) license identifier for this project is `0BSD`.
