/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_utils_1.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/19 14:24:24 by devan         #+#    #+#                 */
/*   Updated: 2020/04/19 14:24:24 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"

size_t	offset_i(t_history *hist, char *history, size_t i)
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

void	print_new_history_line(char *path, int oflag, char *buff, size_t size)
{
	size_t		i;
	int			fd_open;

	i = 0;
	fd_open = open(path, oflag, 0644);
	if (buff == NULL)
	{
		while (i < size)
		{
			ft_dprintf(fd_open, ":%d:TESTTINGHISTORY%d\n", i, i);
			i++;
		}
	}
	else
		ft_dprintf(fd_open, "%s\n", buff);
}

void	print_hist_list(t_hist_list **start)
{
	t_hist_list		*temp;
	static int		i = 0;

	temp = *start;
	ft_printf("\n TEST STARTING(%d):\n", i);
	while (temp->next != NULL)
	{
		ft_printf("\n TEST(%d) : (%s)\n", temp->index, temp->hist_buff);
		temp = temp->next;
	}
	ft_printf("\n TEST(%d) : (%s)\n", temp->index, temp->hist_buff);
	ft_printf("\n-----------------------------------\n");
	i++;
}

int		check_history(char **buff)
{
	int		i;
	int		j;

	i = 0;
	if (ft_strlen(buff[0]) == 0)
		return (0);
	while (buff[i] != NULL)
	{
		j = 0;
		if (buff[i][j] != ':')
		{
			return (1);
		}
		while (ft_isdigit(buff[i][0]))
			j++;
		if (buff[i][j] != ':')
			return (1);
		i++;
	}
	return (0);
}

char	**cut_split_history(t_history *hist, char *history, size_t i)
{
	char		*cut;
	char		**split;

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
