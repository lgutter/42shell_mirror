/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_list.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/19 12:00:22 by devan         #+#    #+#                 */
/*   Updated: 2020/04/19 12:00:22 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "history.h"
#include "handle_error.h"

static void		remove_first_element(t_hist_list **start)
{
	t_hist_list		*temp;
	size_t			i;

	i = 0;
	if (start != NULL && *start != NULL && (*start)->next != NULL)
	{
		temp = *start;
		*start = (*start)->next;
		(*start)->prev = NULL;
		free(temp->hist_buff);
		free(temp);
		temp = *start;
		while (temp->next != NULL)
		{
			temp->index = i;
			i++;
			temp = temp->next;
		}
	}
	temp->index = i;
}

static void		print_new_history_line(char *path, int oflag, char *buff)
{
	int			fd_open;

	if (path == NULL || buff == NULL)
		return ;
	fd_open = open(path, oflag, 0644);
	if (fd_open == -1)
		return ;
	ft_dprintf(fd_open, "%s\n", buff);
	close(fd_open);
}

int				add_remove_update_history(t_history *hist, char *buff)
{
	char	*tmp;
	size_t	len;

	tmp = NULL;
	if (buff == NULL || ft_strlen(buff) == 0 || hist == NULL)
		return (0);
	if (hist->hist_list != NULL)
		hist->real_num_index++;
	len = ft_intlen(hist->real_num_index) + ft_strlen(buff) + 3;
	tmp = (char *)ft_memalloc(sizeof(char) * len + 1);
	if (tmp == NULL)
		return (1);
	ft_snprintf(tmp, len, ":%d:%s", hist->real_num_index, buff);
	if (hist->max_index < HISTSIZE && hist->hist_list != NULL)
		hist->max_index++;
	add_history_element(&hist->hist_list, tmp, hist->max_index);
	if (hist->max_index >= HISTSIZE)
		remove_first_element(&hist->hist_list);
	print_new_history_line(hist->hist_path, O_WRONLY | O_CREAT | O_APPEND, tmp);
	hist->current_index = hist->max_index + 1;
	free(hist->buff_temp);
	hist->buff_temp = NULL;
	free(tmp);
	return (0);
}

static int		change_values(t_hist_list *current, t_hist_list *prev,
size_t i, char *buff)
{
	current->prev = prev;
	current->next = NULL;
	current->index = i;
	current->hist_buff = ft_strdup(buff);
	if (current->hist_buff == NULL)
		return (handle_error(malloc_error));
	return (0);
}

t_hist_list		*add_history_element(t_hist_list **start, char *buff
, size_t i)
{
	t_hist_list *current;
	t_hist_list *prev;

	if (start == NULL || buff == NULL)
		return (NULL);
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
		return (handle_error_p(malloc_error, NULL));
	if (change_values(current, prev, i, buff) != 0)
		return (NULL);
	return (*start);
}
