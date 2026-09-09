# Troubleshoot freestanding builds

## Compiler not found

Confirm every executable named in `[binaries]` exists on `PATH` or use an absolute path. Check the compiler's target before configuring:

```bash
i686-elf-gcc -dumpmachine
```

## Entry point is undefined

Confirm that the linker script's `ENTRY()` name matches a global symbol in the startup object.

```bash
i686-elf-nm builddir/path/to/entry.o | rg ' _start$'
rg 'ENTRY\(' arch/i686/linker.ld
```

Source-list order is not a reliable fix. Define the entry point and placement in the source and linker script.

## Hosted startup symbols conflict

Inspect the verbose link command. A freestanding target normally links with `-nostdlib` or an equivalent toolchain option. Remove hosted CRT objects unless the selected runtime requires them.

## Runtime symbols are undefined

Calls such as `memcpy`, `memset`, division helpers, or C++ ABI routines may come from compiler output even when the source does not call them directly.

```bash
i686-elf-nm -u builddir/kernel.elf
```

Provide ABI-compatible implementations or link the appropriate compiler and C runtime libraries. Do not add a hosted system library from the build machine.

## Linker script changes do not rebuild

Add the script to `link_depends` as well as `link_args`:

```meson
script = files('arch/i686/linker.ld')
executable(
  'kernel',
  sources,
  name_suffix: 'elf',
  link_args: ['-Wl,-T,' + meson.current_source_dir() / 'arch/i686/linker.ld'],
  link_depends: script,
)
```

## A required section disappears

`--gc-sections` removes unreferenced input sections. Retain boot headers, vectors, and constructor tables in the linker script:

```ld
.multiboot : { KEEP(*(.multiboot)) }
.init_array : { KEEP(*(.init_array .init_array.*)) }
```

## GRUB rejects the kernel

Check the completed file instead of inferring validity from section names:

```bash
grub-file --is-x86-multiboot builddir/kernel.elf
```

For Multiboot 1, confirm that the complete header lies within the first 8192 bytes and has the required alignment and checksum.

## The emulator resets or hangs

Separate build validity from runtime diagnosis:

1. Check the ELF machine, entry point, and program headers.
2. Confirm the image or firmware loader accepts the artifact.
3. Start the emulator with serial output and no automatic reboot.
4. Attach a debugger at the reset or entry address.

The Meson task is complete when it produces the expected artifact with the correct dependencies. Boot behavior may require architecture-specific debugging beyond the build definition.
