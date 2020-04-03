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
  'src/prompt.c',
  'src/read_input.c',
  'src/configure_terminal.c',
  'src/cursor.c',
  'src/buffer.c',
  'src/controls.c',
  'src/escape_controls.c',
  'src/cut_copy.c',
  'src/tokenizer.c',
  'src/free_token_list.c',
  'src/handle_error.c',
  'src/utils.c',
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
    'src/buffer.spec.c',
    'src/tokenizer.spec.c',
    'src/handle_error.spec.c',
    'src/free_token_list.spec.c',
    'src/cut_copy.spec.c',
  ])

  tester = executable('test-cetushell',
    sources: test_files,
    include_directories: inc_dir,
    dependencies: [libft_deb, libftprintf_deb, libcurses_deb, libcriterion_deb])

  test('cetushell',
  tester,
  args: '--verbose')
endif

norminette = find_program('norminette', required: false)

if norminette.found()
  test('norm',
    find_program('scripts/meson-norm.sh'),
    args: src_files + main_file)
endif
