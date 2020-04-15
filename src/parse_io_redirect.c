/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_io_redirect.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/06 17:03:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"

t_io_redirect	*free_io_redirect(t_io_redirect *io_redirect)
{
	if (io_redirect == NULL)
		return (NULL);
	free(io_redirect->io_number);
	io_redirect->io_number = NULL;
	free_io_file(io_redirect->io_file);
	io_redirect->io_file = NULL;
	free_io_here(io_redirect->io_here);
	io_redirect->io_here = NULL;
	io_redirect->next = free_io_redirect(io_redirect->next);
	free(io_redirect);
	return (NULL);
}

static int		init_io_number(t_io_redirect *io_redirect, t_token **token)
{
	if ((*token)->type == IO_NUMBER)
	{
		io_redirect->io_number = ft_strdup((*token)->value);
		if (io_redirect->io_number == NULL)
		{
			handle_error(malloc_error);
			return (-1);
		}
		*token = (*token)->next;
	}
	return (0);
}

static int		init_io_redirect(t_io_redirect *io_redirect, t_token **token)
{
	if (token == NULL || *token == NULL)
	{
		handle_error(invalid_token);
		return (-1);
	}
	if ((*token)->next != NULL)
	{
		if (is_redirect_op(*token) == 1)
		{
			io_redirect->io_file = parse_io_file(token);
			if (io_redirect->io_file == NULL)
				return (-1);
			return (0);
		}
		else if ((*token)->type == DLESS)
		{
			io_redirect->io_here = parse_io_here(token);
			if (io_redirect->io_here == NULL)
				return (-1);
			return (0);
		}
	}
	handle_error_str(parsing_error, (*token)->value);
	return (-1);
}

t_io_redirect	*parse_io_redirect(t_token **token)
{
	t_io_redirect	*io_redirect;

	if (token == NULL || *token == NULL)
		return (handle_error_p(invalid_token, NULL));
	io_redirect = (t_io_redirect *)ft_memalloc(sizeof(t_io_redirect) * 1);
	if (io_redirect == NULL)
		return (handle_error_p(malloc_error, NULL));
	if (init_io_number(io_redirect, token) == -1)
		return (free_io_redirect(io_redirect));
	if (init_io_redirect(io_redirect, token) == -1)
		return (free_io_redirect(io_redirect));
	if (*token != NULL && is_start_of_redirect(*token) == 1)
	{
		io_redirect->next = parse_io_redirect(token);
		if (io_redirect->next == NULL)
			return (free_io_redirect(io_redirect));
	}
	return (io_redirect);
}
