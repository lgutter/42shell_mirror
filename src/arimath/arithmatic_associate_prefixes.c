/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arithmatic_run_crementers.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 10:58:15 by aholster      #+#    #+#                 */
/*   Updated: 2020/04/20 10:58:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "arimath.h"

static int	is_leftover_incrementer(enum e_operator operator)
{
	const bool	operator_chart[] = {
		[penta_decrement] = true,
		[penta_increment] = true,
		[tri_decrement] = true,
		[tri_increment] = true,
		[decrement] = true,
		[increment] = true,
		[end_terminator] = false,
	};

	return (operator_chart[operator]);
}

static int	verify_variable(struct s_ari_node *const cur_node,
				bool *const require_num,
				bool *const flip)
{
	*require_num = 0;
	if (*flip)
	{
		cur_node->value = -(cur_node->value);
	}
	*flip = false;
	if (cur_node->next == NULL)
	{
		return (0);
	}
	if (cur_node->next->operator == none)
	{
		return (handle_error_str(bad_math, "adjacent numbers"));
	}
	if (is_leftover_incrementer(cur_node->next->operator))
	{
		return (handle_error_str(bad_math, "lvalue required"));
	}
	return (0);
}

static int	verify_operator(struct s_ari_node *const cur_node,
				bool *const require_num,
				bool *const flip)
{
	*require_num = true;
	if (is_leftover_incrementer(cur_node->operator))
	{
		return (handle_error_str(bad_math, "lvalue required"));
	}
	if (cur_node->operator == addition)
		cur_node->operator = end_terminator;
	else if (cur_node->operator == subtraction)
	{
		*flip = !(*flip);
		cur_node->operator = end_terminator;
	}
	else
		return (handle_error_str(bad_math, "unexpected operator"));
	return (0);
}

int			associate_prefixes(struct s_ari_node *cur_node)
{
	bool	require_num;
	bool	flip;
	int		holder;

	flip = false;
	require_num = false;
	while (cur_node)
	{
		if (cur_node->operator == none)
		{
			holder = verify_variable(cur_node, &require_num, &flip);
			if (cur_node->next == NULL)
				return (0);
			cur_node = cur_node->next;
		}
		else
			holder = verify_operator(cur_node, &require_num, &flip);
		if (holder != 0)
			return (holder);
		cur_node = cur_node->next;
	}
	if (require_num == true)
		return (handle_error_str(bad_math, "missing number"));
	return (0);
}
