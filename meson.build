project('fim', 'c',
  version : '0.4',
  default_options : [
    'buildtype=release',
    'c_std=c17',
    'b_coverage=true',
  ],
  meson_version : '>=0.56.0'
)

c_flags = [
  '-Wall',
  '-Wextra',
  '-Wpedantic',
  '-Wshadow',
  '-Wformat=2',
  '-Wconversion',
  '-Wmissing-include-dirs',
  '-Werror',
]

subdir('src')
subdir('test')

sdl2_dep = [dependency('sdl2'), dependency('sdl2_image'), dependency('sdl2_ttf')] 
cmocka_dep = [dependency('cmocka')]

# This only runs at configuration.
run_command('bash', '-c', 'cp -r $MESON_SOURCE_ROOT/assets $MESON_BUILD_ROOT/assets')

executable('fim',
  [src_game, src_main],
  c_args : [c_flags],
  dependencies : [sdl2_dep],
  include_directories : 'src'
)

test_exe = executable('fim_test',
  [src_test, src_game],
  c_args : [c_flags,
    '-Wno-unused-parameter',
    '-DUNIT_TESTING',
  ],
  dependencies : [sdl2_dep, cmocka_dep],
  include_directories : 'src'
)

test('unit tests', test_exe)
