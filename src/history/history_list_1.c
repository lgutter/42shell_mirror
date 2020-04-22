/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_list_1.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/19 12:00:22 by devan         #+#    #+#                 */
/*   Updated: 2020/04/19 12:00:22 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "history.h"

void			remove_first_element(t_hist_list **start)
{
	t_hist_list		*temp;
	size_t			i;

	i = 0;
	temp = *start;
	if ((*start)->next != NULL)
	{
		*start = (*start)->next;
		(*start)->prev = NULL;
		free(temp->hist_buff);
		free(temp);
	}
	temp = *start;
	while (temp->next != NULL)
	{
		temp->index = i;
		i++;
		temp = temp->next;
	}
	temp->index = i;
}

static int		change_values(t_hist_list *current, t_hist_list *prev,
	size_t i, char *buff)
{
	current->prev = prev;
	current->next = NULL;
	current->index = i;
	current->hist_buff = ft_strdup(buff);
	if (current->hist_buff == NULL)
		return (1);
	return (0);
}

t_hist_list		*add_history_element(t_hist_list **start, char *buff, size_t i)
{
	t_hist_list *current;
	t_hist_list *prev;

	if (*start == NULL)
	{
		*start = (t_hist_list *)ft_memalloc(sizeof(t_hist_list));
		current = *start;
		prev = NULL;
	}
	else
	{
		current = *start;
		while (current->next != NULL)
			current = current->next;
		current->next = (t_hist_list *)ft_memalloc(sizeof(t_hist_list));
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return (NULL);
	if (change_values(current, prev, i, buff) != 0)
		return (NULL);
	return (*start);
}

int				create_history_list(t_hist_list **start, char **buff)
{
	int i;

	i = 0;
	while (buff[i] != NULL)
	{
		*start = add_history_element(start, buff[i], i);
		if (*start == NULL)
			return (0);
		i++;
	}
	return (i);
}

char			*get_hist_str(t_hist_list **start, size_t index)
{
	t_hist_list		*temp;
	char			*string;
	size_t			i;

	i = 0;
	if (start == NULL)
		return (NULL);
	temp = *start;
	while (temp != NULL && index != temp->index)
		temp = temp->next;
	if (temp != NULL && temp->hist_buff != NULL)
	{
		while (ft_isdigit(temp->hist_buff[i + 1]))
			i++;
		i = i + 2;
		string = ft_strdup(&temp->hist_buff[i]);
		return (string);
	}
	return (NULL);
}
