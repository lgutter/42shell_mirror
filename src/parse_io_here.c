/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_io_here.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/06 17:03:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"

t_io_here		*free_io_here(t_io_here *io_here)
{
	if (io_here == NULL)
		return (NULL);
	free(io_here->here_end);
	io_here->here_end = NULL;
	free(io_here);
	return (NULL);
}

t_io_here		*parse_io_here(t_token **token)
{
	t_io_here	*io_here;

	if ((*token)->type != DLESS ||
		(*token)->next == NULL || (*token)->next->type != WORD)
	{
		handle_error_str(parsing_error, (*token)->value);
		return (NULL);
	}
	*token = (*token)->next;
	io_here = ft_memalloc(sizeof(t_io_here) * 1);
	if (io_here == NULL)
	{
		handle_error(malloc_error);
		return (NULL);
	}
	io_here->here_end = ft_strdup((*token)->value);
	if (io_here->here_end == NULL)
	{
		free(io_here);
		handle_error(malloc_error);
		return (NULL);
	}
	*token = (*token)->next;
	return (io_here);
}
