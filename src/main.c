/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/23 16:21:37 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "prompt.h"
#include "handle_input.h"
#include "history.h"
#include "signal_handler.h"

static int		redir_file_argument(char *filename)
{
	int			fd;
	struct stat	statbuff;

	if (access(filename, F_OK) != 0)
		return (handle_error_str(no_such_file_or_dir, filename));
	if (access(filename, R_OK) != 0)
		return (handle_error_str(access_denied, filename));
	stat(filename, &statbuff);
	if (S_ISDIR(statbuff.st_mode) != 0)
		return (handle_error_str(is_dir_error, filename));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (handle_error_str(access_denied, filename));
	dup2(fd, STDIN_FILENO);
	return (0);
}

static void		cetushell(t_shell *shell)
{
	char		*input;
	char		*prompt;
	int			ret;

	ret = 0;
	while (ret != exit_shell_code)
	{
		prompt = ft_getenv(shell->env, "PS1", SHELL_VAR);
		input = prompt_shell(shell, prompt == NULL ? PROMPT_NORMAL : prompt);
		free(prompt);
		if ((g_signal_handler & SIGINT_BUFF) == SIGINT_BUFF)
		{
			free(input);
			input = shell->interactive == 1 ? ft_strdup("") : NULL;
		}
		if (input == NULL)
			break ;
		ret = handle_input(shell, &input);
		update_history(shell->hist, shell->env, input);
		free(input);
		input = NULL;
		g_signal_handler = 0;
	}
}

int				main(int argc, char **argv)
{
	t_shell		*shell;
	int			interactive;
	int			exit_code;

	if (argc > 1 && argv[1] != NULL)
	{
		if (redir_file_argument(argv[1]) != 0)
			return (1);
	}
	interactive = isatty(STDIN_FILENO);
	shell = init_shell(interactive);
	if (shell == NULL)
		return (1);
	cetushell(shell);
	exit_code = get_exit_code(shell);
	free_shell(shell, 1);
	return (exit_code);
}
