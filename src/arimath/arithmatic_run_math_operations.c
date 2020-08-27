/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arithmatic_expansion.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 10:58:15 by aholster      #+#    #+#                 */
/*   Updated: 2020/04/20 10:58:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "arimath.h"

static int	run_basic_operator(struct s_ari_node **const node_list,
				enum e_operator const cur_op,
				t_math_action cur_action)
{
	struct s_ari_node	*iter;

	iter = *node_list;
	while (iter != NULL && iter->next != NULL)
	{
		if ( iter->next->operator == cur_op)
		{
			if (iter->next->next == NULL || iter->next->next->operator != none)
			{
				return (-1);
			}
			iter->value = cur_action(iter->value, iter->next->next->value);
			arithmatic_remove_token(iter->next);
			arithmatic_remove_token(iter->next);
		}
		else
		{
			if (iter->next->next == NULL)
				break ;
			if (iter->next->next->operator != none)
				return (-1);
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

char		*arithmatic_run_math_operations(t_env *const env,
				struct s_ari_node **const node_list)
{
	size_t	iter;
	char	num_buf[40];

	if (*node_list == NULL)
	{
		return (ft_strdup("0"));
	}
	iter = 0;
	if (run_crementers(env, node_list) != 0)
	{
		return (NULL);
	}
	if ((*node_list)->operator != none)
	{
		printf("bad token at start of list\n");
		return (NULL);
	}
	while (iter < sizeof(g_op_queue) / sizeof(t_math_action))
	{
		if (run_basic_operator(node_list, g_op_queue[iter].operator, \
			g_op_queue[iter].action) != 0)
		{
			printf("equation invalid\n");
			return (NULL);
		}
		iter++;
	}
	if ((*node_list)->next)
	{
		printf("leftover tokens!\n");
		return (NULL);
	}
	ft_snprintf(num_buf, sizeof(num_buf), "%ld", (*node_list)->value);
	return (ft_strdup(num_buf));
}