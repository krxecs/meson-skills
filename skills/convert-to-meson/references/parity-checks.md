# Parity checks

Create a parity matrix before conversion. Each row names a supported configuration or contract, its source-build command and result, its Meson command and result, and any intentional difference. Limit the matrix to supported behavior, but account for every supported branch relevant to the request.

## Build configuration

- Languages and language standards
- Debug, optimized, sanitizer, static, shared, and optional-feature variants
- Compiler definitions, include order, compile arguments, link arguments, and symbol visibility
- Native, cross, and platform-specific toolchains

Use verbose source-build and Meson builds when command-level differences matter. Prefer artifact behavior over byte-for-byte output unless reproducibility is an explicit contract.

## Graph and artifacts

- Target names, types, source sets, output names, and output directories
- Generated headers, sources, resources, and configuration files
- Required build order expressed through explicit inputs and outputs
- External dependencies, version constraints, fallback behavior, and static or shared selection

Inspect binaries with the platform's object, symbol, and dependency tools when ABI, exports, runtime search paths, or architecture matter.

## Tests

- Test names, suites, arguments, environment, working directories, fixtures, timeouts, expected failures, and skipped conditions
- Unit, integration, smoke, benchmark, and generated-artifact checks
- Cross-build execution through the required wrapper or an explicit non-runnable result

Compare clean test runs. A matching test count is insufficient when selection or setup differs.

## Install and package contracts

- Installed programs, libraries, headers, data, documentation, and directory layout under the same prefix
- Shared-library versions, ABI names, runtime paths, and exported symbols
- pkg-config or CMake package metadata used by downstream consumers
- Distribution archives and package-manager inputs when supported

Stage both installs under separate temporary roots and compare their file lists, metadata, and a downstream consumer build. Exclude known build-system bookkeeping from the comparison.

## Cutover

Run the Meson setup, compile, test, staged install, consumer, and package commands from a clean checkout or equivalent clean source tree. Update CI and build documentation only after those checks pass. Keep an unresolved difference in the matrix with its impact and owner rather than treating the conversion as complete.
