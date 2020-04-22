/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_list_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 23:32:23 by devan         #+#    #+#                 */
/*   Updated: 2020/04/21 23:32:23 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "history.h"

void	free_hist_list(t_hist_list **start)
{
	t_hist_list	*temp;
	t_hist_list	*temp2;

	temp = *start;
	while (temp->next != NULL)
	{
		temp2 = temp;
		temp = temp->next;
		free(temp2->hist_buff);
		free(temp2);
	}
	free(temp->hist_buff);
	free(temp);
}
