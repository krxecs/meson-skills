---
name: meson-freestanding-projects
description: Build freestanding targets with Meson. Use for kernels, bootloaders, bare-metal firmware, `system = 'none'` machine files, linker scripts, boot images, custom ELF sections, or freestanding C library support.
---

# Meson freestanding projects

Use `meson-cross-compilation` for targets that run under Linux, Windows, macOS, or another operating system. Use this skill when the host machine has `system = 'none'`.

## Workflow

1. Inspect the target architecture, ABI, compiler driver, linker script, entry point, and image format.
2. Put toolchain-wide compile and link arguments in the cross file. Keep target-only arguments on the target.
3. Pass the linker script through `link_args` and `link_depends`.
4. Build the named target through Meson.
5. Inspect the resulting ELF headers, sections, symbols, and boot protocol before running an emulator.

The build is complete only when the expected artifact exists and architecture-specific inspection tools accept it. An emulator boot is a separate runtime check.

## Minimal i686 cross file

```ini
[binaries]
c = 'i686-elf-gcc'
cpp = 'i686-elf-g++'
ar = 'i686-elf-ar'
strip = 'i686-elf-strip'
objcopy = 'i686-elf-objcopy'

[host_machine]
system = 'none'
cpu_family = 'x86'
cpu = 'i686'
endian = 'little'

[built-in options]
c_std = 'c17'
cpp_std = 'c++20'
c_args = ['-ffreestanding', '-fno-pie', '-fno-stack-protector']
cpp_args = ['-ffreestanding', '-fno-pie', '-fno-stack-protector', '-fno-exceptions', '-fno-rtti']
c_link_args = ['-nostdlib', '-no-pie', '-Wl,--gc-sections']
cpp_link_args = ['-nostdlib', '-no-pie', '-Wl,--gc-sections']
```

Configure it with a fresh build directory:

```bash
meson setup builddir --cross-file cross/i686.ini
```

## Kernel target

```meson
project('kernel', 'c', meson_version: '>=1.7.0')

linker_script = files('arch/i686/linker.ld')

kernel = executable(
  'kernel',
  'arch/i686/entry.S',
  'src/main.c',
  name_suffix: 'elf',
  link_args: ['-Wl,-T,' + meson.current_source_dir() / 'arch/i686/linker.ld'],
  link_depends: linker_script,
  install: false,
)
```

The target name is `kernel`, and `name_suffix: 'elf'` produces `kernel.elf`. `link_depends` makes linker-script changes rebuild the target. Meson and the backend determine object order, so the linker script and entry symbol must encode placement requirements.

GCC and Clang compile `.S` sources through the C compiler driver, so this project declares only C. Declare `nasm` or another assembler language only when the source and toolchain use it.

## Linker script requirements

The script must define the entry symbol, memory layout, and sections the boot protocol requires. Retain headers and constructor tables with `KEEP()` when section garbage collection is enabled.

```ld
ENTRY(_start)

SECTIONS {
  . = 1M;
  .multiboot : { KEEP(*(.multiboot)) }
  .text : { *(.text .text.*) }
  .rodata : { *(.rodata .rodata.*) }
  .data : { *(.data .data.*) }
  .bss : { *(COMMON) *(.bss .bss.*) }
}
```

For Multiboot 1, keep the header fully inside the first 8192 bytes of the image and aligned as the specification requires. Use `grub-file --is-x86-multiboot` to check the finished image when GRUB provides that tool.

## Freestanding runtime support

`-nostdlib` removes the hosted startup files and libraries. The program must provide its entry point and any compiler-emitted routines such as `memcpy`, `memset`, or architecture-specific division helpers. Add picolibc, newlib, compiler runtime libraries, or local implementations only after checking the target ABI and license requirements.

Keep the selected runtime in a dependency object. Pin any wrap revision to a reviewed commit or release instead of a moving branch.

## Artifact checks

Use tools from the same target toolchain where possible.

```bash
meson compile -C builddir kernel
i686-elf-readelf -h -S builddir/kernel.elf
i686-elf-nm -n builddir/kernel.elf | head
grub-file --is-x86-multiboot builddir/kernel.elf
qemu-system-i386 -kernel builddir/kernel.elf
```

## Common mistakes

- naming the target `kernel.elf` and also setting `name_suffix: 'elf'`
- relying on source-list order to place the entry object or boot header
- changing compile flags without matching link flags
- omitting the linker script from `link_depends`
- using host `readelf`, `objcopy`, or libraries without checking target support
- assuming a successful link proves that the image satisfies its boot protocol

Read [reference.md](reference.md) for other architecture machine files and linker-script details. Read [troubleshooting.md](troubleshooting.md) for entry-point, runtime-symbol, section-retention, and boot-image failures.
