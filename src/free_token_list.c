/* ************************************************************************** */
/*                                                                            */
/*   cetushell - 21 Shell                                 ::::::::            */
/*                                                      :+:    :+:            */
/*   By: dkroeke <dkroeke@student.codam.nl>            +:+                    */
/*       lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*                                                 #+#    #+#                 */
/*   License: GPLv3                                ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	free_token_list(t_token **start)
{
	t_token	*temp;
	t_token	*current;

	if (start == NULL || *start == NULL)
		return ;
	current = *start;
	while (current != NULL)
	{
		temp = current->next;
		free(current->value);
		current->type = 0;
		current->value = NULL;
		free(current);
		current = temp;
	}
	*start = NULL;
}
