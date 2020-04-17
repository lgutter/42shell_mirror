project(
  '21shell',
  'c',
  default_options: [
    'warning_level=3',
    'werror=true',
  ]
)

cc = meson.get_compiler('c')

add_project_arguments(cc.get_supported_arguments([
  '-Woverflow',
  '-Wassign-enum',
  '-Wno-missing-braces',
  '-Wno-missing-field-initializers',
  '-Wno-unused-parameter',
  '-Wno-unused-result',
]), language: 'c')

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
  'src/escape_controls_1.c',
  'src/escape_controls_2.c',
  'src/cut_copy.c',
  'src/tokenizer.c',
  'src/token_list_util.c',
  'src/handle_error.c',
  'src/parse_complete_command.c',
  'src/parse_pipe_sequence.c',
  'src/parse_simple_command.c',
  'src/parse_arguments.c',
  'src/parse_io_redirect.c',
  'src/parse_io_file.c',
  'src/parse_io_here.c',
  'src/parser_utils.c',
  'src/handle_error.c',
  'src/utils.c',
  'src/str_utils.c',
  'src/quote_utils_1.c',
  'src/quote_utils_2.c',
  'src/handle_input.c',
  'src/convert_env_to_envp.c',
  'src/dup_sys_env.c',
  'src/expand_variable.c',
  'src/ft_getenv.c',
  'src/ft_setenv.c',
  'src/ft_unsetenv.c',
  'src/free_env_list.c',
  'src/word_processing.c',
  'src/temp_print_token_parse.c',
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
    'src/token_list_util.spec.c',
    'src/parse_complete_command.spec.c',
    'src/parse_pipe_sequence.spec.c',
    'src/parse_simple_command.spec.c',
    'src/parse_arguments.spec.c',
    'src/parse_io_redirect.spec.c',
    'src/parse_io_here.spec.c',
    'src/parse_io_file.spec.c',
    'src/parser_utils.spec.c',
    'src/cut_copy.spec.c',
    'src/convert_env_to_envp.spec.c',
    'src/dup_sys_env.spec.c',
    'src/expand_variable.spec.c',
    'src/ft_getenv.spec.c',
    'src/ft_setenv.spec.c',
    'src/ft_unsetenv.spec.c',
    'src/quote_utils.spec.c',
    'src/word_processing.spec.c',
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
