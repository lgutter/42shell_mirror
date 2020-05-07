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
  'src/terminal_input/prompt.c',
  'src/terminal_input/read_input.c',
  'src/terminal_input/configure_terminal.c',
  'src/terminal_input/cursor.c',
  'src/terminal_input/buffer.c',
  'src/terminal_input/buffer_utils.c',
  'src/terminal_input/controls.c',
  'src/terminal_input/escape_controls_1.c',
  'src/terminal_input/escape_controls_2.c',
  'src/terminal_input/cut_copy.c',
  'src/lexer_parser/tokenizer.c',
  'src/lexer_parser/token_list_util.c',
  'src/lexer_parser/parse_complete_command.c',
  'src/lexer_parser/parse_pipe_sequence.c',
  'src/lexer_parser/parse_simple_command.c',
  'src/lexer_parser/parse_arguments.c',
  'src/lexer_parser/parse_io_redirect.c',
  'src/lexer_parser/parse_io_file.c',
  'src/lexer_parser/parse_io_here.c',
  'src/lexer_parser/parser_utils.c',
  'src/utilities/handle_error.c',
  'src/utilities/d_handle_error.c',
  'src/utilities/utils.c',
  'src/utilities/str_utils.c',
  'src/utilities/quote_utils_1.c',
  'src/utilities/quote_utils_2.c',
  'src/utilities/executor_utils.c',
  'src/utilities/process_word.c',
  'src/utilities/process_redirects.c',
  'src/utilities/word_processing.c',
  'src/environment/convert_env_to_envp.c',
  'src/environment/dup_sys_env.c',
  'src/environment/expand_variable.c',
  'src/environment/ft_getenv.c',
  'src/environment/ft_setenv.c',
  'src/environment/ft_unsetenv.c',
  'src/environment/free_env_list.c',
  'src/handle_input.c',
  'src/history/history_list.c',
  'src/history/init_history.c',
  'src/history/init_history_utils.c',
  'src/history/history_utils.c',
  'src/executor/find_executable.c',
  'src/executor/exec_complete_command.c',
  'src/executor/exec_pipe_sequence.c',
  'src/executor/exec_simple_command.c',
  'src/executor/set_up_redirections.c',
  'src/executor/set_up_io_file.c',
  'src/executor/add_fd_to_list.c',
  'temp/temp_print_token_parse.c',
  'src/builtins/builtin_cd.c',
  'src/builtins/builtins_1.c',
  'src/builtins/builtins_2.c',
  'src/builtins/builtin_env_1.c',
  'src/builtins/builtin_env_2.c',
])

main_file = files('src/main.c')

executable(
  'cetushell',
  sources: src_files + main_file,
  include_directories: inc_dir,
  dependencies: [libft_deb, libftprintf_deb, libcurses_deb],
)

libcriterion_deb = dependency('criterion', required: false)

default_test_timeout = 360

if libcriterion_deb.found()
  test_files = src_files + files([
    'src/terminal_input/buffer.spec.c',
    'src/terminal_input/cut_copy.spec.c',
    'src/lexer_parser/tokenizer.spec.c',
    'src/lexer_parser/token_list_util.spec.c',
    'src/lexer_parser/parse_complete_command.spec.c',
    'src/lexer_parser/parse_pipe_sequence.spec.c',
    'src/lexer_parser/parse_simple_command.spec.c',
    'src/lexer_parser/parse_arguments.spec.c',
    'src/lexer_parser/parse_io_redirect.spec.c',
    'src/lexer_parser/parse_io_here.spec.c',
    'src/lexer_parser/parse_io_file.spec.c',
    'src/lexer_parser/parser_utils.spec.c',
    'src/utilities/handle_error.spec.c',
    'src/environment/convert_env_to_envp.spec.c',
    'src/environment/dup_sys_env.spec.c',
    'src/environment/expand_variable.spec.c',
    'src/environment/ft_getenv.spec.c',
    'src/environment/ft_setenv.spec.c',
    'src/environment/ft_unsetenv.spec.c',
    'src/utilities/quote_utils.spec.c',
    'src/utilities/process_word.spec.c',
    'src/utilities/process_redirects.spec.c',
    'src/utilities/word_processing.spec.c',
    'src/history/history_utils.spec.c',
    'src/executor/add_fd_to_list.spec.c',
    'src/executor/find_executable.spec.c',
    'src/executor/set_up_io_file.spec.c',
    'src/executor/set_up_redirections.spec.c',
    'src/executor/exec_complete_command.spec.c',
    'src/executor/exec_pipe_sequence.spec.c',
    'src/executor/exec_simple_command.spec.c',
    'src/builtins/builtins.spec.c',
  ])

  tester = executable('test-cetushell',
    sources: test_files,
    include_directories: inc_dir,
    dependencies: [libft_deb, libftprintf_deb, libcurses_deb, libcriterion_deb])

  test('cetushell',
  tester,
  args: '--verbose',
  timeout: default_test_timeout,)
endif

norminette = find_program('norminette', required: false)

if norminette.found()
  test('norm',
    find_program('scripts/meson-norm.sh'),
    args: src_files + main_file)
endif
