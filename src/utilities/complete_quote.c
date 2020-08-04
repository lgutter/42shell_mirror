/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_quote.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 12:48:27 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/23 16:31:14 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "prompt.h"
#include "token_trans_table.h"
#include "signal_handler.h"

/*
**	checks if the given string contains invalid pipes, single or double quotes,
**	or if it end with a backslash (unterminated backslash).
**	returns:
**	4:	if the string contains an unterminated pipe.
**	3:	if the string contains an unterminated backslash.
**	2:	if the string contains an unterminated double quote.
**	1:	if the string contains an unterminated single quote.
**	0:	if the string does not contain invalid quotes.
**	-1:	on error.
*/

static int	check_type(char *word)
{
	t_rules		rules;
	t_state		state;

	if (word == NULL)
		return (-1);
	state = blank;
	while (1)
	{
		rules = g_token_trans[state].rules[(size_t)*word];
		if (rules.next_state == invalid)
			rules = g_token_trans[state].catch_state;
		if (rules.next_state == unt_squote)
			return (1);
		if (rules.next_state == unt_dquote)
			return (2);
		if (rules.next_state == unt_backslash)
			return (3);
		if (rules.next_state == unt_pipe)
			return (4);
		if (rules.next_state == eof)
			return (0);
		state = rules.next_state;
		word++;
	}
}

static int	get_extra_input(t_shell *shell, char **temp, int type)
{
	char				*buff;
	static const char	*prompts[] = {
			"", PROMPT_QUOTE, PROMPT_DQUOTE, PROMPT_BACKSLASH, PROMPT_PIPE};

	buff = NULL;
	while (type > 0)
	{
		ft_strexpand(temp, "\n");
		buff = prompt_shell(shell, prompts[type]);
		if (buff == NULL && shell->interactive != 1)
			return (handle_error_str(parsing_error, "unexpected EOF"));
		ft_strexpand(temp, buff);
		free(buff);
		if (*temp == NULL)
			return (-1);
		if ((g_signal_handler & (1 << SIGINT)) != 0)
		{
			*temp[0] = '\0';
			return (-1);
		}
		type = check_type(*temp);
	}
	return (0);
}

int			complete_unterminated(t_shell *shell, char **word)
{
	char	*temp;
	int		ret;
	int		type;

	ret = 0;
	if (shell == NULL || word == NULL || *word == NULL)
		return (malloc_error);
	temp = ft_strdup(*word);
	if (temp == NULL)
		return (malloc_error);
	type = check_type(temp);
	ret = get_extra_input(shell, &temp, type);
	free(*word);
	*word = temp;
	return (ret);
}
