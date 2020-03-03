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
  'src/set_terminal.c',
  'src/tokenizer.c',
])

main_file = files('src/main.c')

executable(
  'cetushell',
  sources: src_files + main_file,
  include_directories: inc_dir,
  dependencies: [libft_deb, libftprintf_deb, libcurses_deb],
)

libcriterion_deb = dependency('criterion', required: false)

if libcriterion_deb.found()
  test_files = src_files + files([
    'src/tokenizer.spec.c',
  ])

  tester = executable('test-cetushell',
    sources: test_files,
    include_directories: inc_dir,
    dependencies: [libft_deb, libftprintf_deb, libcurses_deb, libcriterion_deb])

  test('cetushell', tester)
endif

norminette = find_program('norminette', required: false)

if norminette.found()
  test('norm',
    find_program('scripts/meson-norm.sh'),
    args: src_files + main_file)
endif
