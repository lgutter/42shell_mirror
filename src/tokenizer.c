/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/14 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "utils.h"

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
**	returns: 0 on success, error code on error.
*/

static int		expand_buff(char **buff, char new)
{
	static size_t	size = BUFFER_SIZE;
	size_t			i;
	char			*temp;

	i = 0;
	if (*buff == NULL)
	{
		*buff = (char *)ft_memalloc(size);
		if (*buff == NULL)
			return (handle_error(malloc_error));
	}
	i = ft_strlen(*buff);
	if (i >= (size - 1))
	{
		temp = ft_memalloc(size * 2);
		if (temp == NULL)
			return (handle_error(malloc_error));
		temp = ft_strcpy(temp, *buff);
		free(*buff);
		*buff = temp;
		size = size * 2;
	}
	(*buff)[i] = new;
	return (0);
}

static t_rules	init_state(t_state cur_state, char next)
{
	t_rules	state_rules;

	state_rules = g_token_trans[cur_state].rules[(size_t)next];
	if (state_rules.next_state == invalid)
	{
		state_rules = g_token_trans[cur_state].catch_state;
	}
	return (state_rules);
}

static int		handle_token(t_rules state_rules, t_token **start,
							char **buff, char input)
{
	int	ret;

	ret = 0;
	if (ret == 0 && state_rules.add_char == ADD_CHAR_PRE)
		ret = expand_buff(buff, input);
	if (ret == 0 && state_rules.delimit_type != undetermined)
		ret = add_token(start, state_rules.delimit_type, buff);
	if (ret == 0 && state_rules.add_char == ADD_CHAR_POST)
		ret = expand_buff(buff, input);
	return (ret);
}

static int		check_unquoted(t_rules *state_rules, char **input)
{
	if (state_rules->next_state == unt_dquote)
	{
		if (complete_quote(input) != 0)
			return (-1);
		*state_rules = init_state(unt_dquote, '\0');
	}
	else if (state_rules->next_state == unt_squote)
	{
		if (complete_quote(input) != 0)
			return (-1);
		*state_rules = init_state(unt_squote, '\0');
	}
	return (0);
}

t_token			*tokenizer(char *input)
{
	t_rules		state_rules;
	t_token		*start;
	t_state		cur_state;
	static char	*buff = NULL;
	size_t		i;

	start = NULL;
	cur_state = blank;
	i = 0;
	while (1)
	{
		state_rules = init_state(cur_state, input[i]);
		if (check_unquoted(&state_rules, &input) != 0)
			return (free_token_list(&start));
		if (handle_token(state_rules, &start, &buff, input[i]) != 0)
			return (free_token_list(&start));
		if (state_rules.next_state == eof)
			return (start);
		cur_state = state_rules.next_state;
		i++;
	}
}
