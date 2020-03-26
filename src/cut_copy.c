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

#include "cetushell.h"
#include "input_control.h"

<<<<<<< HEAD
char		*copy_cut_right_to_left(t_buff *buffer, int cut)
=======
char		*cut_copy_right_to_left(t_buff *buffer, int cut)
>>>>>>> 461c721e986a64e022db25670cf2f321f0f72195
{
	char	*copy;
	size_t	len;

<<<<<<< HEAD
	len = buffer->rv_start - buffer->rv_end + 1;
	if (len == 0)
		return (NULL);
=======
	len = buffer->rv_start - buffer->rv_end;
	if (len == 1)
	{
		buffer->rv_end--;
		len = 2;
	}
>>>>>>> 461c721e986a64e022db25670cf2f321f0f72195
	copy = ft_memalloc(sizeof(char) * len + 1);
	if (copy == NULL)
		return (NULL);
	copy[len + 1] = '\0';
	ft_strncpy(copy, &buffer->buff[buffer->rv_end], len);
<<<<<<< HEAD
	if (cut == 1)
	{
		buffer->rv_start++;
		buffer->index = buffer->rv_start;
=======
	buffer->index = buffer->rv_start;
	if (cut == 1)
	{
>>>>>>> 461c721e986a64e022db25670cf2f321f0f72195
		while (buffer->rv_start > buffer->rv_end)
		{
			remove_char(buffer);
			buffer->rv_start--;
		}
	}
	return (copy);
}

<<<<<<< HEAD
char		*copy_cut_left_to_right(t_buff *buffer, int cut)
=======
char		*cut_copy_left_to_right(t_buff *buffer, t_cursor *cursor, int cut)
>>>>>>> 461c721e986a64e022db25670cf2f321f0f72195
{
	char	*copy;
	size_t	len;

	len = buffer->rv_end + 1 - buffer->rv_start;
<<<<<<< HEAD
	if (len == 0)
		return (NULL);
=======
>>>>>>> 461c721e986a64e022db25670cf2f321f0f72195
	copy = ft_memalloc(sizeof(char) * len + 1);
	if (copy == NULL)
		return (NULL);
	copy[len + 1] = '\0';
<<<<<<< HEAD
	buffer->rv_end++;
	buffer->index = buffer->rv_end;
=======
	buffer->index = buffer->rv_end + 1;
>>>>>>> 461c721e986a64e022db25670cf2f321f0f72195
	ft_strncpy(copy, &buffer->buff[buffer->rv_start], len);
	while (buffer->rv_start < buffer->rv_end)
	{
		if (cut == 1)
<<<<<<< HEAD
			remove_char(buffer);
		buffer->rv_end--;
	}
	return (copy);
}

void	copy(t_buff *buffer)
{
	if (buffer->rv_start < buffer->rv_end)
			buffer->copy = copy_cut_left_to_right(buffer, 0);
	else if (buffer->rv_start > buffer->rv_end)
			buffer->copy = copy_cut_right_to_left(buffer, 0);
}

void	cut(t_buff *buffer)
{
	if (buffer->rv_end != buffer->rv_start)
=======
		{
			remove_char(buffer);
			cursor->current.x--;
		}
		buffer->rv_end--;
	}
	if (cut == 1)
		remove_char(buffer);
	return (copy);
}

void	cut_cntrl_left(t_buff *buffer,t_cursor *cursor, char *seq)
{
	if (ft_strncmp(CNTRL_LEFT, seq, sizeof(CNTRL_LEFT)) == 0 && \
		buffer->rv_end != buffer->rv_start)
>>>>>>> 461c721e986a64e022db25670cf2f321f0f72195
	{
		if (buffer->copy != NULL && ft_strlen(buffer->copy) > 0)
			ft_memset(buffer->copy, '\0', ft_strlen(buffer->copy));
		if (buffer->rv_start < buffer->rv_end)
<<<<<<< HEAD
			buffer->copy = copy_cut_left_to_right(buffer, 1);
		else if (buffer->rv_start > buffer->rv_end)
			buffer->copy = copy_cut_right_to_left(buffer, 1);
		buffer->rv_start = buffer->index;
		buffer->rv_end = buffer->rv_start;
	}
	else if (buffer->index != buffer->len && buffer->rv_end != buffer->rv_start)
=======
			buffer->copy = cut_copy_left_to_right(buffer, cursor, 1);
		else if (buffer->rv_start > buffer->rv_end)
			buffer->copy = cut_copy_right_to_left(buffer, 1);
		buffer->rv_start = buffer->index;
		buffer->rv_end = buffer->rv_start;
	}
	else if (ft_strncmp(CNTRL_LEFT, seq, sizeof(CNTRL_LEFT)) == 0 \
	&& buffer->index != buffer->len)
>>>>>>> 461c721e986a64e022db25670cf2f321f0f72195
	{
		buffer->copy = ft_memalloc(2);
		buffer->copy[1] = '\0';
		buffer->copy[0] = buffer->buff[buffer->index];
		buffer->index++;
		remove_char(buffer);
	}
<<<<<<< HEAD
}

void	paste(t_buff *buffer, t_cursor *cursor)
{
	size_t len;
	size_t i;

	i = 0;
	len = ft_strlen(buffer->copy);
	while (len > i)
	{
		insert_char(buffer, buffer->copy[i]);
		cursor->current.x++;
		set_cursor_pos(cursor, buffer->len);
		i++;
	}
}

void	cut_copy_paste(t_buff *buffer, t_cursor *cursor, char *seq, char c)
{
	if (c == CNTRL_X)
		copy(buffer);
	if (c == CNTRL_V || (seq != NULL 
	&& ft_strncmp(seq, CNTRL_RIGHT, sizeof(CNTRL_RIGHT)) == 0))
		paste(buffer, cursor);
	if (seq != NULL && ft_strncmp(seq, CNTRL_LEFT, sizeof(CNTRL_LEFT)) == 0)
	{
		if (buffer->rv_start < buffer->rv_end)
			cursor->current.x = cursor->current.x - (buffer->rv_end \
			- buffer->rv_start);
		cut(buffer);
	}
=======
>>>>>>> 461c721e986a64e022db25670cf2f321f0f72195
}