project('fim', 'c',
  version : '0.4',
  default_options : [
    'buildtype=release',
    'c_std=c99',
    ],
  meson_version : '>=0.56.0')

subdir('src')
#subdir('test')

sdl2_lib = meson.get_compiler('c').find_library('SDL2')
sdl2image_lib  = meson.get_compiler('c').find_library('SDL2_image')

executable('fim',
  [src_game, src_main],
  c_args : [
    '-Wall',
    '-Werror',
    '-Wextra',
    '-Wshadow',
    '-Wundef',
    '-Wconversion',
    '-Wpedantic',
    '-Wformat=2',
    '-Wnull-dereference', 
    '-Wlogical-op'
    ],
  #link_args : ['-lSDL2_image'],
  dependencies : [sdl2_lib, sdl2image_lib],
  include_directories : 'src')
