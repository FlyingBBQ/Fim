project('fim', 'c',
  version : '0.4',
  default_options : [
    'buildtype=release',
    'c_std=c17',
  ],
  meson_version : '>=0.56.0')

subdir('src')
#subdir('test')

sdl2_dep = [dependency('sdl2'), dependency('sdl2_image')] 

# This only runs at configuration.
run_command('bash', '-c', 'cp -r $MESON_SOURCE_ROOT/gfx $MESON_BUILD_ROOT/gfx')

executable('fim',
  [src_game, src_main],
  c_args : [
    '-Wall',
    '-Wextra',
    '-Wpedantic',
    '-Wshadow',
    '-Wformat=2',
    '-Wconversion',
    '-Wmissing-include-dirs',
    '-Werror',
    ],
  dependencies : [sdl2_dep],
  include_directories : 'src')
