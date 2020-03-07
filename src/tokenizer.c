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

/*
**	expand_buff will expand the buffer where the value to be stored in a token
**	is kept until the token is delimited.
**	normally this just means adding a character, but if the length of
**	the token value exceeds the BUFFER_SIZE, the size of the buffer is doubled.
**	if there was no buffer yet, it is allocated.
**	the size of the buffer is stored in a static variable so we can always
**	know its exact size.
**	arg: buff - a pointer to the actual buffer.
**	arg: new - the character to be added.
*/

static void	expand_buff(char **buff, char new, size_t *size)
{
	size_t			i;
	char			*temp;

	i = 0;
	if (*buff == NULL)
	{
		*buff = (char *)ft_memalloc(*size);
		if (buff == NULL)
			exit(1);
	}
	i = ft_strlen(*buff);
	if (i >= (*size - 1))
	{
		temp = ft_memalloc(*size * 2);
		if (temp == NULL)
			exit(1);
		temp = ft_strcpy(temp, *buff);
		free(*buff);
		*buff = temp;
		*size = *size * 2;
	}
	(*buff)[i] = new;
}

/*
**	this function is a simple wrapper for buffer management.
**	if the char is a terminating zero (it will never receive this from
**	the tokenizer), it will empty the buffer.
**	otherwise, it will pass its arguments to expand_buffer.
*/

static void	handle_buff(char **buff, char new)
{
	static size_t	size = BUFFER_SIZE;

	if (new == '\0')
	{
		ft_memset((void *)*buff, '\0', size);
	}
	else
	{
		expand_buff(buff, new, &size);
	}
}

/*
**	The add_token function creates a new node in the list of tokens,
**	and sets the type and transfers the buffer into the value field.
**	It also calls handle_buff to empty the buffer.
**	arg: start - a pointer to the first element in the token list.
**	arg: type - the type of the token.
**	arg: buff - a pointer to the buffer.
*/

static void	add_token(t_token **start, t_type type, char **buff)
{
	t_token *temp;

	if (*start == NULL)
	{
		*start = (t_token *)ft_memalloc(sizeof(t_token));
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
	if (temp == NULL)
		exit(1);
	temp->next = NULL;
	temp->type = type;
	temp->value = ft_strdup(*buff);
	handle_buff(buff, '\0');
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
		state_rules = g_token_trans[cur_state].rules[(size_t)*input];
		if (state_rules.next_state == invalid)
			state_rules = g_token_trans[cur_state].catch_state;
		if (state_rules.add_char == ADD_CHAR_PRE)
			handle_buff(&buff, *input);
		if (state_rules.delimit_type != undetermined)
			add_token(&start, state_rules.delimit_type, &buff);
		if (state_rules.add_char == ADD_CHAR_POST)
			handle_buff(&buff, *input);
		if (state_rules.next_state == eof)
			return (start);
		cur_state = state_rules.next_state;
		input++;
	}
	return (start);
}
