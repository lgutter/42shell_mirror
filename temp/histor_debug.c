/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   histor_debug.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/23 14:54:31 by devan         #+#    #+#                 */
/*   Updated: 2020/04/23 14:54:31 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "cetushell.h"

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

void	print_history_file(char *path, int oflag, size_t size)
{
	size_t		i;
	int			fd_open;

	i = 0;
	fd_open = open(path, oflag, 0644);
	while (i < size)
	{
		ft_dprintf(fd_open, ":%d:TESTTINGHISTORY%d\n", i, i);
		i++;
	}
	close(fd_open);
}
