# Freestanding reference

## Machine file roles

`[binaries]` names target tools. `[host_machine]` describes the machine that will run the output. `[built-in options]` holds compiler and linker settings. `[properties]` holds project-specific metadata read with `meson.get_external_property()`.

Prefer compiler drivers for linking. They know which target runtime objects and libraries accompany the selected language. Override linker selection only when the toolchain and Meson version support the requested linker.

## RISC-V 64-bit preset

```ini
[binaries]
c = 'riscv64-unknown-elf-gcc'
cpp = 'riscv64-unknown-elf-g++'
ar = 'riscv64-unknown-elf-ar'
strip = 'riscv64-unknown-elf-strip'
objcopy = 'riscv64-unknown-elf-objcopy'

[host_machine]
system = 'none'
cpu_family = 'riscv64'
cpu = 'riscv64'
endian = 'little'

[built-in options]
c_args = ['-ffreestanding', '-march=rv64imac', '-mabi=lp64']
c_link_args = ['-nostdlib', '-march=rv64imac', '-mabi=lp64', '-Wl,--gc-sections']
```

Match `-march` and `-mabi` to the processor and firmware ABI. Do not copy these values into a target with different extensions or floating-point support.

## ARM Cortex-M4 preset

```ini
[binaries]
c = 'arm-none-eabi-gcc'
cpp = 'arm-none-eabi-g++'
ar = 'arm-none-eabi-ar'
strip = 'arm-none-eabi-strip'
objcopy = 'arm-none-eabi-objcopy'

[host_machine]
system = 'none'
cpu_family = 'arm'
cpu = 'cortex-m4'
endian = 'little'

[built-in options]
c_args = ['-ffreestanding', '-mcpu=cortex-m4', '-mthumb']
c_link_args = ['-nostdlib', '-mcpu=cortex-m4', '-mthumb', '-Wl,--gc-sections']
```

Add `-mfpu` and `-mfloat-abi` only when the processor, ABI, and runtime libraries agree on the floating-point ABI.

## AArch64 preset

```ini
[binaries]
c = 'aarch64-none-elf-gcc'
cpp = 'aarch64-none-elf-g++'
ar = 'aarch64-none-elf-ar'
strip = 'aarch64-none-elf-strip'
objcopy = 'aarch64-none-elf-objcopy'

[host_machine]
system = 'none'
cpu_family = 'aarch64'
cpu = 'aarch64'
endian = 'little'

[built-in options]
c_args = ['-ffreestanding', '-mgeneral-regs-only']
c_link_args = ['-nostdlib', '-Wl,--gc-sections']
```

`-mgeneral-regs-only` is an AArch64 option. Keep it out of x86 machine files.

## Linker script

The exact script depends on the architecture and boot protocol. A freestanding script commonly needs:

- `ENTRY()` for the startup symbol
- `MEMORY` regions for firmware targets
- fixed virtual or physical addresses for kernels
- `KEEP()` for boot headers, interrupt vectors, and constructor tables
- exported boundary symbols used by startup code
- explicit alignment for pages, vectors, and stacks

Pass the script to the compiler driver and make it a build dependency:

```meson
script = files('arch/linker.ld')
firmware = executable(
  'firmware',
  sources,
  name_suffix: 'elf',
  link_args: ['-Wl,-T,' + meson.current_source_dir() / 'arch/linker.ld'],
  link_depends: script,
)
```

## Boot images

Model each transformation as a build target. Put multi-step filesystem work in a checked script rather than shell operators inside `custom_target()`.

```meson
image_tool = find_program('scripts/make-image.py')

image = custom_target(
  'boot-image',
  input: firmware,
  output: 'firmware.bin',
  command: [image_tool, '@INPUT@', '@OUTPUT@'],
  build_by_default: true,
)
```

The script should create parent directories, fail on the first error, and write only inside the build tree.

## Runtime libraries

A freestanding compiler may still emit calls to compiler runtime helpers. Inspect undefined symbols before choosing support code:

```bash
target-nm -u builddir/firmware.elf
```

Provide the smallest ABI-compatible runtime that resolves required symbols. Pin third-party sources and export their include paths, compile arguments, and link inputs through a dependency object.

## Validation by artifact type

| Artifact | Checks |
|---|---|
| ELF kernel | ELF class, machine, entry point, program headers, required boot header |
| Raw firmware | size, load address, vector table, checksum if required |
| GRUB image | `grub-file`, ISO contents, emulator boot |
| UEFI image | PE/COFF machine type, firmware load, expected entry point |

Use target-prefixed binutils when host tools do not support the target format.
