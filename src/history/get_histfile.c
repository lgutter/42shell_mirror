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

static size_t	get_history_size(t_history *hist)
{
	struct stat stats;

	if (stat(hist->hist_path, &stats) == -1)
		return (1);
	hist->file_size = (size_t)(stats.st_size);
	return (0);
}

static int		get_hist_path(t_shell *shell)
{
	char	*dir;

	if (shell->hist->hist_path != NULL)
		return (0);
	shell->hist->hist_path = ft_getenv(shell->env, "HISTFILE", SHELL_VAR);
	if (shell->hist->hist_path == NULL)
	{
		dir = ft_getenv(shell->env, "HOME", SHELL_VAR);
		if (dir == NULL)
			return (1);
		shell->hist->hist_path = ft_strjoin(dir, HISTFILE);
		free(dir);
		if (shell->hist->hist_path == NULL)
			return (1);
		ft_setenv(shell->env, "HISTFILE", shell->hist->hist_path, SHELL_VAR);
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
	if (get_history_size(shell->hist) == 1)
		return (history_filesize_error);
	return (0);
}
