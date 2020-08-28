/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arithmatic_run_math_operations.c                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 10:58:15 by aholster      #+#    #+#                 */
/*   Updated: 2020/04/20 10:58:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "arimath.h"
#include "op_ident_chart.h"

static int	run_basic_operator(struct s_ari_node *iter,
				enum e_operator const cur_op,
				t_math_action cur_action)
{
	while (iter != NULL && iter->next != NULL)
	{
		if (iter->next->operator == cur_op)
		{
			if (iter->next->next == NULL || iter->next->next->operator != none)
			{
				return (handle_error_str(parsing_error,
													g_op_ident_chart[cur_op]));
			}
			iter->value = cur_action(iter->value, iter->next->next->value);
			arithmatic_remove_token(iter->next);
			arithmatic_remove_token(iter->next);
		}
		else
		{
			if (iter->next->next != NULL && iter->next->next->operator != none)
			{
				return (handle_error_str(parsing_error,
								g_op_ident_chart[iter->next->next->operator]));
			}
			iter = iter->next->next;
		}
	}
	return (0);
}

static const struct s_action_kvp g_op_queue[] = {
	{multiply, arithmath_multiply},
	{divide, arithmath_divide},
	{modulo, arithmath_modulo},
	{addition, arithmath_addition},
	{subtraction, arithmath_subtraction},
	{lessthan, arithmath_lessthan},
	{greaterthan, arithmath_greaterthan},
	{equal_or_less, arithmath_equal_or_less},
	{equal_or_greater, arithmath_equal_or_greater},
	{equal, arithmath_equal},
	{unequal, arithmath_unequal},
	{and, arithmath_and},
	{or, arithmath_or},
};

static int	iter_operations(struct s_ari_node **const node_list)
{
	size_t	iter;
	int		ret;

	iter = 0;
	while (iter < (sizeof(g_op_queue) / sizeof(struct s_action_kvp)))
	{
		ret = run_basic_operator(*node_list, g_op_queue[iter].operator, \
			g_op_queue[iter].action);
		if (ret != 0)
		{
			return (ret);
		}
		iter++;
	}
	return (0);
}

int			arithmatic_run_math_operations(char **tape,
				t_env *const env,
				struct s_ari_node **const node_list)
{
	int		ret;

	if (*node_list == NULL)
	{
		*tape = ft_strdup("0");
		return (0);
	}
	ret = run_crementers(env, node_list);
	if (ret != 0)
		return (ret);
	if ((*node_list)->operator != none)
	{
		return (handle_error_str(parsing_error,
									g_op_ident_chart[(*node_list)->operator]));
	}
	ret = iter_operations(node_list);
	if (ret != 0)
		return (ret);
	if ((*node_list)->next)
		return (handle_error_str(parsing_error, "end of arithmetic expansion"));
	ft_asprintf(tape, "%ld", (*node_list)->value);
	return (0);
}
