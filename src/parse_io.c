/* ************************************************************************** */
/*                                                                            */
/*   cetushell - 21 Shell                                 ::::::::            */
/*                                                      :+:    :+:            */
/*   By: dkroeke <dkroeke@student.codam.nl>            +:+                    */
/*       lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   License: GPLv3                                ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"

t_token	*parse_io_file(t_token *token)
{
	t_io_file	*io_file;

	if (is_redirect_op(token) != 1 ||
		token->next == NULL || token->next->type != WORD)
		return (handle_error_str_p(parsing_error, token->value, NULL));
	io_file = ft_memalloc(sizeof(t_io_file) * 1);
	if (io_file == NULL)
		return (handle_error_p(malloc_error, NULL));
	io_file->redirect_op = token->type;
	token = token->next;
	io_file->filename = token->value;
	return (token);
}

t_token	*parse_io_here(t_token *token)
{
	t_io_here	*io_here;

	if (token->type != DLESS ||
		token->next == NULL || token->next->type != WORD)
		return (handle_error_str_p(parsing_error, token->value, NULL));
	token = token->next;
	io_here = ft_memalloc(sizeof(t_io_here) * 1);
	if (io_here == NULL)
	{
		handle_error(malloc_error);
		return (NULL);
	}
	io_here->here_end = ft_strdup(token->value);
	if (io_here->here_end == NULL)
	{
		free(io_here);
		io_here = (t_io_here *)handle_error_p(malloc_error, NULL);
	}
	return (token);
}
