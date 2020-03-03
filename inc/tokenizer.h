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

typedef struct		s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
}					t_token;

/*
**	converts a string to alist of tokens according to shell language rules.
**	arg: input - the input string to be tokenized.
**
**	return: a linked list of tokens, containing a token type and value.
*/
t_token				*tokenizer(char *input);

#endif
