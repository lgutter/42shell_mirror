/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_utils.c                                    :+:    :+:            */
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

static size_t	get_temp_hist_buff(t_buff *buffer, t_history *hist)
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

static char		*get_hist_str(t_hist_list **start, size_t index)
{
	t_hist_list		*temp;
	char			*string;
	size_t			i;

	i = 0;
	if (start == NULL || *start == NULL)
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

size_t			scroll_hist(t_history *hist, t_buff *buffer, t_cursor *cursor
, char dir)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (hist == NULL || buffer == NULL || buffer->buff == NULL
		|| cursor == NULL)
		return (1);
	if (dir == 'U')
		hist->current_index--;
	else if (dir == 'D')
		hist->current_index++;
	if (get_temp_hist_buff(buffer, hist) != 0)
		return (1);
	remove_buff(buffer, cursor);
	if (hist->current_index == hist->max_index + 1)
		temp = ft_strdup(hist->buff_temp);
	else
		temp = get_hist_str(&hist->hist_list, hist->current_index);
	if (temp == NULL)
		return (1);
	if (ft_strlen(temp) != 0 &&
	insert_word(buffer, cursor, &temp[i], ft_strlen(&temp[i])) != 0)
		return (1);
	free(temp);
	return (0);
}

void			free_history(t_history *hist)
{
	if (hist->hist_path != NULL)
		free(hist->hist_path);
	if (hist->buff_temp != NULL)
		free(hist->buff_temp);
	free_hist_list(&hist->hist_list);
	if (hist != NULL)
		free(hist);
}

void			free_hist_list(t_hist_list **start)
{
	t_hist_list	*temp;
	t_hist_list	*temp2;

	temp = *start;
	if (temp == NULL)
		return ;
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
