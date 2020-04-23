/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_history_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/23 16:38:00 by devan         #+#    #+#                 */
/*   Updated: 2020/04/23 16:38:00 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "history.h"

static size_t	get_history_size(t_history *hist)
{
	struct stat stats;

	if (stat(hist->hist_path, &stats) == -1)
		return (1);
	hist->file_size = (size_t)(stats.st_size);
	return (0);
}

static int		get_hist_path(t_history *hist)
{
	char	*temp;

	temp = getenv("HOME");
	if (temp == NULL)
		return (1);
	hist->hist_path = ft_strjoin(temp, HISTFILE);
	if (hist->hist_path == NULL)
		return (1);
	return (0);
}

int				get_histfile(t_history *hist)
{
	if (hist == NULL)
		return (1);
	if (get_hist_path(hist) == 1)
		return (2);
	if (access(hist->hist_path, F_OK) == 0)
		if (access(hist->hist_path, R_OK | W_OK) != 0)
			return (3);
	if (get_history_size(hist) == 1)
		return (4);
	return (0);
}

static size_t	offset_i(t_history *hist, char *history, size_t i)
{
	size_t		count;

	count = 0;
	if (i > 2)
		i = i - 2;
	while (HISTSIZE > count)
	{
		if (history[i] == '\n')
			count++;
		hist->max_index = count;
		if (i == 0)
			count = HISTSIZE;
		else
			i--;
	}
	if (i != 0)
		i++;
	hist->current_index = hist->max_index + 1;
	return (i);
}

char			**cut_split_history(t_history *hist, char *history, size_t i)
{
	char		*cut;
	char		**split;

	if (history == NULL || hist == NULL)
		return (NULL);
	i = offset_i(hist, history, i);
	cut = ft_strdup(&history[i]);
	if (cut == NULL)
		return (NULL);
	split = ft_strsplit(cut, '\n');
	free(cut);
	if (split == NULL)
		return (NULL);
	else if (split != NULL && split[0] == NULL)
		split[0] = ft_strdup("");
	if (split[0] == NULL)
		return (NULL);
	return (split);
}
