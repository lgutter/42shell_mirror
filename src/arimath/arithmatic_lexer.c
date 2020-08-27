/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arithmatic_lexer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 10:58:15 by aholster      #+#    #+#                 */
/*   Updated: 2020/04/20 10:58:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "arimath_fsm.h"
#include "arimath.h"

static int				add_number_token(const char **const atape,
							struct s_ari_node **const node_list)
{
	long int	num;
	size_t		index;

	num = arithmatic_atol_base(&index, *atape);
	if (index == 0)
	{
		return (parsing_error);
	}
	*atape += index;
	return (arithmatic_add_token(node_list, NULL, num, none));
}

static int				add_operator_token(const char **const atape,
							struct s_ari_node **const node_list)
{
	enum e_operator	ident_iter;
	size_t			operator_len;
	const char		*operator_str;

	ident_iter = none;
	while (ident_iter != end_terminator)
	{
		operator_str = g_op_ident_chart[ident_iter];
		if (operator_str != NULL)
		{
			operator_len = ft_strlen(operator_str);
			if (ft_strnequ(*atape, operator_str, operator_len) == true)
			{
				*atape += operator_len;
				return (arithmatic_add_token(node_list, NULL, 0, ident_iter));
			}
		}
		ident_iter++;
	}
	return (parsing_error);
}

static int				add_variable_token(const char **const atape,
							t_env *const env,
							struct s_ari_node **const node_list)
{
	size_t		len;
	char		*key;
	long int	int_value;
	int			ret_holder;

	len = 0;
	while (ft_isalnum((*atape)[len]) || (*atape)[len] == '_')
		len++;
	if (len == 0)
		return (parsing_error);
	key = ft_strndup(*atape, len);
	if (key == NULL)
		return (malloc_error);
	*atape += len;
	ret_holder = arithmatic_getint_from_env(&int_value, env, key);
	if (ret_holder == 0)
	{
		ret_holder = arithmatic_add_token(node_list, key, int_value, none);
	}
	free(key);
	if (ret_holder == env_not_found)
		return (0);
	return (ret_holder);
}

const bool g_valid_char_tbl[256] = {
	[' '] = true,
	['\t'] = true,
	['_'] = true,
	['+'] = true,
	['-'] = true,
	['*'] = true,
	['/'] = true,
	['%'] = true,
	['<'] = true,
	['>'] = true,
	['='] = true,
	['!'] = true,
	['&'] = true,
	['|'] = true,
};

static enum e_ari_state	next_state(enum e_ari_state current_state,
							const char cur_char)
{
	const struct s_ari_fsm_state	*next_state_def;
	enum e_ari_state				default_next_state;
	unsigned char					char_index;

	char_index = cur_char;
	if (g_valid_char_tbl[char_index] != true && ft_isalnum(char_index) == false)
	{
		ft_dprintf(2, "Cetushell: unexpected character: %c\n", cur_char);
		return (invalid_state);
	}
	next_state_def = &(g_arithmatic_fsm_def[current_state]);
	default_next_state = next_state_def->rules[char_index].next_state;
	if (default_next_state != invalid_state)
	{
		return (default_next_state);
	}
	else
	{
		return (next_state_def->catch_rule.next_state);
	}
}

int						create_token_list(t_env *const env,
							const char *tape,
							struct s_ari_node **const node_list)
{
	enum e_ari_state	state;
	int					status;

	state = st_encounterer;
	while (state != invalid_state && *tape != '\0')
	{
		state = next_state(state, *tape);
		if (state == st_number)
			status = add_number_token(&tape, node_list);
		else if (state == st_operator)
			status = add_operator_token(&tape, node_list);
		else if (state == st_variable)
			status = add_variable_token(&tape, env, node_list);
		else
			tape++;
		if (status != 0)
			break ;
	}
	if (*tape != '\0' || state == invalid_state)
	{
		ft_dprintf(2, "Cetushell: arithmath parsing error\n");
		return (-1);
	}
	return (0);
}
