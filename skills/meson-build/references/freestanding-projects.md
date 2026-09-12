# Freestanding projects

Use this reference when the host machine has `system = 'none'`. Inspect the architecture, ABI, compiler driver, linker script, entry point, image format, and boot protocol. Keep arguments required by every freestanding project in the project definition. In GNU or GNU-style toolchains, this includes `-ffreestanding`, PIE and stack-protector settings, `-nostdlib`, linker options, and the C++ exception and RTTI policy. Pair `--gc-sections` with `-ffunction-sections` and `-fdata-sections`. Put an argument in the cross file only when it depends on the selected toolchain or target machine; put target-only arguments on the target.

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

```

```meson
project('kernel', 'c', 'cpp',
  default_options: ['c_std=c17', 'cpp_std=c++20'])

add_project_arguments(
  '-ffreestanding',
  '-fno-pie',
  '-fno-stack-protector',
  '-ffunction-sections',
  '-fdata-sections',
  language: ['c', 'cpp'],
)
add_project_arguments('-fno-exceptions', '-fno-rtti', language: 'cpp')
add_project_link_arguments(
  '-nostdlib',
  '-no-pie',
  '-Wl,--gc-sections',
  language: ['c', 'cpp'],
)

script = files('arch/i686/linker.ld')
kernel = executable('kernel', 'arch/i686/entry.S', 'src/main.c',
  name_suffix: 'elf',
  link_args: ['-Wl,-T,' + meson.current_source_dir() / 'arch/i686/linker.ld'],
  link_depends: script)
```

GCC and Clang compile `.S` through the C driver, so declare C unless the assembler needs its own language. Do not name the target `kernel.elf` when `name_suffix: 'elf'` adds the suffix. The linker script must define `ENTRY()`, placement, and required sections. Use `KEEP()` for boot headers, vectors, and constructor tables when garbage collection is enabled. Multiboot 1 headers must meet its first-8192-byte, alignment, and checksum rules.

`-nostdlib` removes hosted startup files and libraries. Provide the entry point and compiler-emitted routines such as memory or division helpers through the smallest ABI-compatible runtime. Keep runtime inputs in a dependency object and pin third-party sources. Model image transformations with a `custom_target()` or checked script that writes only into the build tree.

```bash
meson compile -C builddir kernel
i686-elf-readelf -h -S builddir/kernel.elf
i686-elf-nm -n builddir/kernel.elf
i686-elf-nm -u builddir/kernel.elf
grub-file --is-x86-multiboot builddir/kernel.elf
qemu-system-i386 -kernel builddir/kernel.elf
```

Use target-prefixed binutils where host tools cannot inspect the format. Check ELF class, machine, entry point, headers, symbols, and required protocol fields before an emulator. Match RISC-V `-march` and `-mabi`, use Cortex-M `-mcpu` and `-mthumb`, and add floating-point options only when processor, ABI, and runtime agree. `-mgeneral-regs-only` applies to AArch64 only.

When the linker cannot find the entry point, match `ENTRY()` to a global startup symbol. Add linker scripts to `link_depends`. Inspect undefined symbols before adding runtime libraries. Separate valid build artifacts from emulator failures and report unavailable toolchains, boot validators, and emulators.

The check is complete when target inspection accepts the expected artifact. Emulator boot is a separate runtime check.
