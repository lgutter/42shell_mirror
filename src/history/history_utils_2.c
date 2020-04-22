/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_utils_2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 21:36:16 by devan         #+#    #+#                 */
/*   Updated: 2020/04/21 21:36:16 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"
#include "history.h"

size_t	get_temp_hist_buff(t_buff *buffer, t_history *hist)
{
	if (buffer->state == INPUT_STATE)
	{
		if (hist->buff_temp != NULL)
		{
			free(hist->buff_temp);
			hist->buff_temp = NULL;
		}
		hist->buff_temp = ft_strdup(buffer->buff);
		if (hist->buff_temp == NULL)
			return (1);
		buffer->state = HISTORY_STATE;
	}
	return (0);
}

size_t	get_history_size(t_history *hist)
{
	struct stat stats;

	if (stat(hist->hist_path, &stats) == -1)
		return (1);
	hist->file_size = (size_t)(stats.st_size);
	return (0);
}

int		get_hist_path(t_history *hist)
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

size_t	get_last_index(char **split)
{
	size_t		i;
	size_t		index;
	char		numb[32];

	ft_bzero(numb, 32);
	index = 0;
	while (split[index] != NULL)
		index++;
	index--;
	i = ft_atoi(&split[index][1]);
	return (i);
}

void	free_history(t_history *hist)
{
	free(hist->hist_path);
	free(hist->buff_temp);
	free_hist_list(&hist->hist_list);
	free(hist);
}
