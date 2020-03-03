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

#include "tokenizer.h"
#include <stdlib.h>

static void	expand_buff(char **buff, char new)
{
	static size_t	size = 1024;
	size_t			i;

	i = 0;
	if (*buff == NULL)
		*buff = (char *)ft_memalloc(size);
	while (i < size && (*buff)[i] != '\0')
		i++;
	if (i == size)
		exit(42); // expand buffer!!
	(*buff)[i] = new;
}

static void	add_token(t_token **start, t_type type, char **buff)
{
	t_token *temp;

	if (*start == NULL)
	{
		(*start) = (t_token *)ft_memalloc(sizeof(t_token));
		temp = *start;
	}
	else
	{
		temp = *start;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = (t_token *)ft_memalloc(sizeof(t_token));
		temp = temp->next;
	}
	temp->next = NULL;
	temp->type = type;
	temp->value = ft_strdup(*buff);
	free(*buff);
	*buff = NULL;
}

t_token		*tokenizer(char *input)
{
	t_rules	state_rules;
	t_token	*start;
	t_state	cur_state;
	char	*buff;

	buff = NULL;
	start = NULL;
	cur_state = blank;
	while (1)
	{
		state_rules = g_token_trans[cur_state].rules[(int)*input];
		if (state_rules.next_state == invalid)
			state_rules = g_token_trans[cur_state].catch_state;
		if (state_rules.delimit_type != undetermined)
			add_token(&start, state_rules.delimit_type, &buff);
		if (state_rules.add_char == ADD_CHAR)
			expand_buff(&buff, *input);
		if (state_rules.next_state == eof)
			return (start);
		cur_state = state_rules.next_state;
		input++;
	}
	return (start);
}
