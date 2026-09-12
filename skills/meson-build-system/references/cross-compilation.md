# Cross-compilation

Identify build, host, and target machines. Most cross builds need build and host only. Inspect the toolchain and sysroot before writing a machine file, then configure a fresh directory.

```ini
[host_machine]
system = 'linux'
cpu_family = 'arm'
cpu = 'armv7l'
endian = 'little'

[binaries]
c = '/usr/bin/arm-linux-gnueabihf-gcc'
cpp = '/usr/bin/arm-linux-gnueabihf-g++'
ar = '/usr/bin/arm-linux-gnueabihf-gcc-ar'
strip = '/usr/bin/arm-linux-gnueabihf-strip'
exe_wrapper = '/usr/bin/qemu-arm'

[properties]
sys_root = '/opt/arm-sysroot'
pkg_config_libdir = '/opt/arm-sysroot/usr/lib/pkgconfig'
toolchain_prefix = 'arm-linux-gnueabihf'

[built-in options]
c_std = 'c17'
cpp_std = 'c++20'
warning_level = '3'
```

`[binaries]` names target tools. `[properties]` holds metadata read with `meson.get_external_property()`. `[built-in options]` holds compiler and linker flags, standards, and warning levels. Use `pkg_config_libdir` to isolate target pkg-config metadata. Put build-machine generators and formatters in a native file, not the cross file.

```bash
meson setup builddir --cross-file cross.ini
meson setup builddir --native-file native.ini
```

Use an `exe_wrapper` for runnable target binaries. Otherwise skip target tests or use host-side helpers. Keep machine files in version control. Check `meson-logs/meson-log.txt` and introspection for selected tools and dependencies.

When the wrong compiler or linker runs, check `[binaries]` and its installed prefix. When pkg-config finds build-machine libraries, isolate the sysroot and its environment. Replace `meson.get_cross_property()` with `meson.get_external_property()`. A changed machine file requires a fresh configuration.

The check is complete when the intended toolchain and target dependencies configure and the requested outputs compile. Report unavailable cross compilers, wrappers, and target runtime checks.
