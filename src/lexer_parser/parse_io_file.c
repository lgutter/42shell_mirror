/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_io_file.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/06 17:03:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"

t_io_file		*free_io_file(t_io_file *io_file)
{
	if (io_file == NULL)
		return (NULL);
	free(io_file->filename);
	io_file->filename = NULL;
	io_file->redirect_op = no_redirect_op;
	free(io_file);
	return (NULL);
}

t_io_file		*parse_io_file(t_token **token)
{
	t_io_file	*io_file;

	if (token == NULL || *token == NULL)
		return (handle_error_p(invalid_token, NULL));
	if (is_redirect_op(*token) != 1 ||
		(*token)->next == NULL || (*token)->next->type != WORD)
	{
		handle_error_str(parsing_error, (*token)->value);
		return (NULL);
	}
	io_file = (t_io_file *)ft_memalloc(sizeof(t_io_file) * 1);
	if (io_file == NULL)
		return (handle_error_p(malloc_error, NULL));
	io_file->redirect_op = (t_redirect_op)(*token)->type;
	*token = (*token)->next;
	io_file->filename = ft_strdup((*token)->value);
	if (io_file->filename == NULL)
	{
		free_io_file(io_file);
		handle_error(malloc_error);
		return (NULL);
	}
	*token = (*token)->next;
	return (io_file);
}
