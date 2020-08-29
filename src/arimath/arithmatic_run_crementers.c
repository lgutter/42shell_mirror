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

static int	crement_var(t_env *const env,
				const bool is_prefix,
				const enum e_operator type,
				struct s_ari_node *const cur_node)
{
	long int	new_num;
	int			ret;
	char		num_buf[40];

	ret = arithmatic_getint_from_env(&new_num, env, cur_node->original_key);
	if (ret != 0)
	{
		return (ret);
	}
	if (type == decrement || type == tri_decrement || type == penta_decrement)
		new_num--;
	else
		new_num++;
	if (is_prefix == true)
	{
		cur_node->value = new_num;
	}
	ft_snprintf(num_buf, sizeof(num_buf), "%ld", new_num);
	ret = ft_setenv(env, cur_node->original_key, num_buf, VAR_TYPE);
	if (ret == error_ronly)
	{
		handle_error_str(error_ronly, cur_node->original_key);
	}
	return (ret);
}

static int	find_first_valid_crementer(t_env *const env,
				struct s_ari_node *cur_node)
{
	int						holder;
	const enum e_operator	downgrade_tbl[] = {
		[penta_increment] = tri_increment,
		[tri_increment] = addition,
		[increment] = end_terminator,
		[penta_decrement] = tri_decrement,
		[tri_decrement] = subtraction,
		[decrement] = end_terminator,
		[end_terminator] = none,
	};

	if (cur_node->prev && downgrade_tbl[cur_node->prev->operator] != none)
	{
		holder = crement_var(env, true, cur_node->prev->operator, cur_node);
		cur_node->prev->operator = downgrade_tbl[cur_node->prev->operator];
		return (holder);
	}
	else if (cur_node->next && downgrade_tbl[cur_node->next->operator] != none)
	{
		holder = crement_var(env, false, cur_node->next->operator, cur_node);
		cur_node->next->operator = downgrade_tbl[cur_node->next->operator];
		return (holder);
	}
	return (0);
}

static void	purge_terminators(struct s_ari_node **node_list)
{
	struct s_ari_node	*cleanup_trail;

	while ((*node_list))
	{
		if ((*node_list)->operator == end_terminator)
		{
			cleanup_trail = *node_list;
			*node_list = (*node_list)->next;
			arithmatic_remove_token(cleanup_trail);
		}
		else
		{
			node_list = &(*node_list)->next;
		}
	}
}

/*
**	in here we will slate nodes for deletion by setting them as
**	operator = 'end_terminator'
*/

int			run_crementers(t_env *const env,
				struct s_ari_node **node_list)
{
	struct s_ari_node	*iter;
	int					ret;

	iter = *node_list;
	ret = 0;
	while (iter)
	{
		if (iter->original_key)
		{
			ret = find_first_valid_crementer(env, iter);
			if (ret != 0)
				return (handle_error(ret));
		}
		iter = iter->next;
	}
	purge_terminators(node_list);
	ret = associate_prefixes(*node_list);
	purge_terminators(node_list);
	return (ret);
}
