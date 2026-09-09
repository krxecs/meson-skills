project(
  'generated-sources',
  'c',
  'cpp',
  version: '0.1.0',
  meson_version: '>=1.1.0',
  license: '0BSD',
  license_files: ['LICENSE.md'],
  default_options: [
    'c_std=c17',
    'cpp_std=c++20',
    'warning_level=3',
  ],
)


python = find_program('python3', required: true)
version_script = files('scripts/gen_version.py')
message_script = meson.current_source_dir() / 'scripts/gen_message.py'
inc = include_directories('include')

version_h = custom_target(
  'version-header',
  input: 'templates/version.in',
  output: 'version.hpp',
  command: [python, version_script, '@INPUT@', '@OUTPUT@'],
)

header_gen = generator(
  python,
  output: '@BASENAME@.hpp',
  arguments: [message_script, '@INPUT@', '@OUTPUT@'],
)

message_headers = header_gen.process(files('templates/hello.txt', 'templates/farewell.txt'))

app = executable(
  'generated-app',
  'src/main.cpp',
  include_directories: inc,
  sources: [version_h] + message_headers,
  install: true,
)

test('generated-app', app, args: ['--version'])
