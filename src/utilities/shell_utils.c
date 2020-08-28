/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 13:17:06 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/08 17:37:34 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "handle_error.h"
#include "history.h"
#include "environment.h"
#include "utils.h"
#include "prompt.h"
#include "signal_handler.h"
#include "job_control.h"
#include "hashtable.h"
#include "input_handling.h"

static t_shell	*alloc_shell(bool interactive)
{
	t_shell		*shell;

	shell = (t_shell *)ft_memalloc(sizeof(t_shell));
	if (shell == NULL)
		return (NULL);
	shell->hist = NULL;
	shell->job_control = NULL;
	if (interactive == true)
	{
		shell->hist = (t_history *)ft_memalloc(sizeof(t_history) * 1);
		if (shell->hist == NULL)
			handle_error_str(malloc_error, "when creating history");
	}
	shell->job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont) * 1);
	if (shell->job_control == NULL)
		handle_error_str(malloc_error, "when creating job control");
	shell->buffer = (t_buff *)ft_memalloc(sizeof(t_buff) * 1);
	if (shell->buffer == NULL)
	{
		free_shell(shell, 0);
		handle_error(malloc_error);
		shell = NULL;
	}
	return (shell);
}

static char		*check_passwd_entry(char *entry, uid_t user, bool interactive)
{
	char	**fields;
	char	*ret;

	ret = NULL;
	fields = ft_strsplit(entry, ':');
	if (fields != NULL && ft_str_arr_len(fields) == 7 &&
		user == (unsigned int)ft_atoi(fields[2]))
	{
		ret = ft_strdup(fields[5]);
		if (interactive == true)
		{
			ft_dprintf(STDERR_FILENO, "Cetushell: HOME not found, so assumed ");
			ft_dprintf(STDERR_FILENO, "\"%s\" from \"/etc/passwd\".\n", ret);
		}
	}
	ft_free_str_array(fields);
	return (ret);
}

/*
**	check if we inherited a HOME, and if not, fetch the user's home from
**	/etc/passwd. this could be done easier with getpwuid(3), but since that is
**	a section 3 function, we are not allowed to use it. if the shell is
**	interactive, we also print a warning that we assumed the user's home.
*/

static void		init_home_var(t_shell *shell)
{
	char	*temp;
	char	*line;
	int		fd;
	uid_t	user;

	temp = ft_getenv(shell->env, "HOME", ENV_VAR);
	if (temp == NULL)
	{
		fd = open("/etc/passwd", O_RDONLY);
		if (fd >= 0)
		{
			user = getuid();
			while (temp == NULL && ft_getline(fd, &line) > 0)
			{
				temp = check_passwd_entry(line, user, shell->interactive);
				free(line);
			}
			close(fd);
		}
		ft_setenv(shell->env, "HOME", temp, ENV_VAR);
	}
	free(temp);
}

t_shell			*init_shell(bool interactive)
{
	t_shell		*shell;

	if (interactive == true)
		setup_signals();
	shell = alloc_shell(interactive);
	if (shell == NULL)
		return (handle_error_p(malloc_error, NULL));
	shell->env = dup_sys_env();
	if (shell->env == NULL)
	{
		free_shell(shell, 0);
		return (handle_error_p(malloc_error, NULL));
	}
	shell->interactive = interactive;
	init_home_var(shell);
	if (interactive == true)
		configure_terminal(shell, 2);
	if (shell->hist != NULL)
		initialize_history(shell);
	if (init_hashtable(shell) != 0)
		free_hashtable(shell);
	return (shell);
}

int				free_shell(t_shell *shell, int ret)
{
	if (shell != NULL)
	{
		free_history(shell->hist);
		free_hashtable(shell);
		shell->hist = NULL;
		free_read_buff(shell->buffer);
		free_buffer_buffs(shell, 1);
		if (shell->buffer != NULL)
			free(shell->buffer);
		shell->buffer = NULL;
		free_job_control(shell->job_control);
		shell->job_control = NULL;
		if (shell->interactive == true)
			configure_terminal(NULL, 0);
		free_env_list(shell->env);
		free(shell);
	}
	return (ret);
}
