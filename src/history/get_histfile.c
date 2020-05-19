/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_histfile.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/23 16:38:00 by devan         #+#    #+#                 */
/*   Updated: 2020/04/23 16:38:00 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "history.h"
#include "handle_error.h"
#include "environment.h"

static size_t	get_history_size(t_shell *shell)
{
	struct stat	stats;
	char		*temp;
	int			histsize;

	histsize = HISTSIZE;
	temp = ft_getenv(shell->env, "HISTSIZE", ENV_VAR);
	if (temp != NULL)
		histsize = ft_atoi(temp);
	if (histsize < 0)
		histsize = 1;
	free(temp);
	temp = ft_itoa(histsize);
	ft_setenv(shell->env, "HISTSIZE", temp, SHELL_VAR | RO_VAR);
	if (stat(shell->hist->hist_path, &stats) == -1)
		return (1);
	shell->hist->file_size = (size_t)(stats.st_size);
	return (0);
}

static int		get_hist_path(t_shell *shell)
{
	char	*home;

	if (shell->hist->hist_path != NULL)
		return (0);
	shell->hist->hist_path = ft_getenv(shell->env, "HISTFILE", SHELL_VAR);
	if (shell->hist->hist_path == NULL)
	{
		home = ft_getenv(shell->env, "HOME", SHELL_VAR);
		if (home == NULL)
			return (1);
		shell->hist->hist_path = ft_strjoin(home, HISTFILE);
		free(home);
		if (shell->hist->hist_path == NULL)
			return (1);
		ft_setenv(shell->env, "HISTFILE", shell->hist->hist_path,
														SHELL_VAR | RO_VAR);
	}
	return (0);
}

int				get_histfile(t_shell *shell)
{
	if (shell == NULL || shell->hist == NULL)
		return (malloc_error);
	if (get_hist_path(shell) == 1)
		return (error_histpath);
	if (access(shell->hist->hist_path, F_OK) != 0)
		return (0);
	if (access(shell->hist->hist_path, R_OK) != 0)
		return (no_read_permission_hist);
	if (access(shell->hist->hist_path, W_OK) != 0)
		return (no_write_permission_hist);
	if (get_history_size(shell) == 1)
		return (history_filesize_error);
	return (0);
}

int				get_histsize(t_env *env)
{
	char	*tmp;
	int		histsize;

	histsize = HISTSIZE;
	tmp = ft_getenv(env, "HISTSIZE", SHELL_VAR);
	if (tmp != NULL)
	{
		histsize = ft_atoi(tmp);
		if (histsize < 1)
			histsize = 1;
	}
	free(tmp);
	return (histsize);
}
