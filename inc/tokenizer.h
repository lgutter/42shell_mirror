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

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "ft_printf.h"
# include "libft.h"
# include "token_trans_table.h"
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
*/
typedef struct			s_token
{
	t_type				type;
	char				*value;
	struct s_token		*next;
}						t_token;

/*
**	converts a string to a list of tokens according to shell language rules.
**	arg: input - the input string to be tokenized.
**
**	return: a linked list of tokens, containing a token type and value.
*/
t_token					*tokenizer(char *input);

#endif
