/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/14 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "ft_printf.h"
# include "libft.h"
# include "token_trans_table.h"
# include "handle_error.h"
# include "cetushell.h"
# include <stdlib.h>

/*
**	buffer size of the buffer used in the tokenizer/lexer.
**	the part of the input string that will become a token is kept in this buffer
*/
# define BUFFER_SIZE	128

/*
**	the linked list node containing a token.
**	fields:
**	type:	contains an enum specifying the type of the token.
**			enums are defined in token_trans_table.h
**	value:	a string with the characters from the input that the token contains.
**	next:	pointer to the next token in the list.
**	prev:	pointer to the previous token in the list.
*/
typedef struct			s_token
{
	t_type				type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

/*
**	converts a string to a list of tokens according to shell language rules.
**	arg: input - the input string to be tokenized.
**
**	return: a linked list of tokens, containing a token type and value.
*/
t_token					*tokenizer(t_shell *shell, char *input);

/*
**	The add_token function creates a new node in the list of tokens,
**	and sets the type and transfers the buffer into the value field.
**	It also calls ft_memset to empty the buffer after it is done.
**	arg: start - a pointer to the first element in the token list.
**	arg: type - the type of the token.
**	arg: buff - a pointer to the buffer.
**	returns: 0 on success, error code on error.
*/
int						add_token(t_token **start, t_type type, char **buff);

/*
**	frees all nodes and their content in a token linked list.
**	arg: start: a pointer to a pointer to the first element in the list.
*/
t_token					*free_token_list(t_token **start);

#endif
