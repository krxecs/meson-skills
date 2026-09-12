project(
  'shared-library',
  'c',
  'cpp',
  version: '1.2.3',
  meson_version: '>=1.7.0',
  license: '0BSD',
  license_files: ['LICENSE.md'],
  default_options: [
    'c_std=c17',
    'cpp_std=c++20',
    'warning_level=3',
  ],
)

inc = include_directories('include')

shared_lib = shared_library(
  'shared-library',
  'src/shared_api.c',
  include_directories: inc,
  c_args: ['-DSHARED_LIBRARY_BUILD'],
  version: '1.2.3',
  soversion: '1',
  install: true,
)

shared_dep = declare_dependency(
  include_directories: inc,
  link_with: shared_lib,
)

consumer = executable(
  'cpp-consumer',
  'src/consumer.cpp',
  dependencies: shared_dep,
  cpp_args: ['-DSHARED_LIBRARY_USE'],
  install: true,
)

test('cpp-consumer', consumer, args: ['20', '22'])

install_headers('include/shared_library/shared_api.h', subdir: 'shared_library')

pkg = import('pkgconfig')
pkg.generate(
  shared_lib,
  name: 'shared-library',
  description: 'C shared library with a stable ABI',
  filebase: 'shared-library',
)
