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
#include "processing.h"
#include "substitution.h"

static int		interpreter_module(t_shell *const shell, char **tape)
{
	int					ret;
	struct s_ari_node	*node_list;

	node_list = NULL;
	ret = process_word(shell, tape, ARITHMATIC_TABLE);
	if (ret != 0)
	{
		ft_strdel(tape);
		return (ret);
	}
	ret = create_token_list(shell->env, *tape, &node_list);
	ft_strdel(tape);
	if (ret != 0)
	{
		arithmatic_delete_tokens(&node_list);
		return (ret);
	}
	ret = arithmatic_run_math_operations(tape, shell->env, &node_list);
	arithmatic_delete_tokens(&node_list);
	if (ret == 0 && *tape == NULL)
	{
		return (malloc_error);
	}
	return (ret);
}

static int		insert_result(char **const astring,
					size_t *const awrite_index,
					char *tape,
					size_t temp_index)
{
	char *new_astring;

	if (ft_asprintf(&new_astring, "%.*s%s%s", *awrite_index, *astring,
		tape, *astring + temp_index + 2) == -1)
	{
		free(tape);
		return (malloc_error);
	}
	*awrite_index += ft_strlen(tape);
	free(tape);
	free(*astring);
	*astring = new_astring;
	return (0);
}

int				arithmatic_expansion(t_shell *const shell,
					char **const astring,
					size_t *const aread_index,
					size_t *const awrite_index)
{
	size_t				tmp_ind;
	ssize_t				holder;
	char				*tape;
	int					ret;

	holder = subst_length(*astring + *aread_index + 1) - 2;
	if (holder < 0)
	{
		return (handle_error_str(parsing_error, "no closing parenthesis"));
	}
	tmp_ind = holder + *aread_index + 1;
	tape = ft_strsub(*astring, *aread_index + 3, (tmp_ind - *aread_index) - 3);
	if (tape == NULL)
		return (malloc_error);
	ret = interpreter_module(shell, &tape);
	if (ret != 0)
		return (ret);
	ret = insert_result(astring, awrite_index, tape, tmp_ind);
	if (ret == 0)
		*aread_index = *awrite_index - 1;
	return (ret);
}
