# Package export and distribution

Identify public headers, libraries, programs, data, and metadata. Inspect every install declaration and prefix. Stage the install, inspect it, and test a downstream consumer when exporting a library.

```meson
inc = include_directories('include')
lib = library('mylib', 'src/mylib.cpp', include_directories: inc,
  version: '1.2.0', soversion: '1', install: true)
install_headers('include/mylib/mylib.hpp', subdir: 'mylib')

pkg = import('pkgconfig')
pkg.generate(lib, description: 'My reusable library', filebase: 'mylib', subdirs: 'mylib')
```

`version` tracks the release. `soversion` tracks the ABI family. Use both for a downstream shared-library ABI. Install public headers and data intentionally; do not install private headers or build helpers. Keep build-tree paths out of installed files. Document a prefix-relative layout when the package needs one.

```bash
meson install -C builddir --destdir "$pkgdir"
meson dist -C builddir
```

Use `DESTDIR` for package staging. Run `meson dist` from a clean, configured checkout that can build from its archive. Document CMake, vcpkg, or Conan integration when downstream users depend on those systems. For in-tree reuse, export a `declare_dependency()` object; for external consumers, provide pkg-config metadata where appropriate.

The check is complete when the staged tree has the intended public files, metadata resolves from a separate consumer build, and the requested distribution archive succeeds.
