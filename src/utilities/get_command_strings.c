/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_command_strings.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/10 18:55:22 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/10 18:55:22 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "tokenizer.h"
#include "parser_utils.h"

static void	add_word(char **dest, char *src)
{
	char	*temp;
	size_t	size;

	if (*dest == NULL)
		temp = ft_strdup(src);
	else
	{
		size = ft_strlen(*dest) + ft_strlen(src) + 1;
		temp = (char *)ft_memalloc(sizeof(char) * size + 1);
		if (temp != NULL)
		{
			ft_strcpy(temp, *dest);
			temp[ft_strlen(*dest)] = ' ';
			ft_strcpy(&(temp[ft_strlen(*dest) + 1]), src);
		}
	}
	if (temp != NULL)
	{
		free(*dest);
		*dest = temp;
	}
}

char		*get_pipe_seq_str(t_token *token)
{
	t_token	*temp;
	char	*string;

	temp = token;
	string = NULL;
	while (temp != NULL)
	{
		add_word(&string, temp->value);
		if (temp->type == PIPE)
			break ;
		temp = temp->next;
	}
	return (string);
}

char		*get_command_str(t_token *token)
{
	t_token	*temp;
	char	*string;

	temp = token;
	string = NULL;
	while (temp != NULL)
	{
		add_word(&string, temp->value);
		if (is_seperator_op(temp) == 1)
			break ;
		temp = temp->next;
	}
	return (string);
}
