project(
  '21shell',
  'c',
  default_options: [
    'warning_level=3',
    'werror=true',
  ]
)

cc = meson.get_compiler('c')

libft_proj = subproject('libft')
libft_deb = libft_proj.get_variable('libft_deb')

libftprintf_proj = subproject('ft_printf')
libftprintf_deb = libftprintf_proj.get_variable('libftprintf_deb')

libcurses_deb = cc.find_library('curses', required: false)
if not libcurses_deb.found()
	libcurses_deb = dependency('ncurses')
endif

inc_dir = include_directories('inc')
src_files = files([
  'src/main.c',
  'src/set_terminal.c',
])

executable(
  'cetushell',
  sources: src_files,
  include_directories: inc_dir,
  dependencies: [libft_deb, libftprintf_deb, libcurses_deb],
)

libcriterion_deb = dependency('criterion', required: false)

if libcriterion_deb.found()
  test_files = files([
    'src/foo_test.spec.c',
    'src/foo_test.c',
  ])

  tester = executable('test-cetushell',
    sources: test_files,
    include_directories: inc_dir,
    dependencies: [libft_deb, libftprintf_deb, libcurses_deb, libcriterion_deb])

  test('cetushell', tester)
endif
