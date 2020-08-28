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

static void		reconstruct_input_from_list(struct s_ari_node *iter)
{
	printf("reconstructing input from tokens:\033[94m\n");
	while (iter != NULL)
	{
		if (iter->original_key != NULL)
			printf("%s=%ld ", iter->original_key, iter->value);
		else if (iter->operator != none)
			printf("%s ", g_op_ident_chart[iter->operator]);
		else
			printf("%ld ", iter->value);
		iter = iter->next;
	}
	printf("\033[0m\n");
}//this entire function is for debugging

static size_t	find_length(const char *string, size_t aread_index)
{
	int			par_counter;
	size_t		temp_index;

	par_counter = 0;
	temp_index = aread_index + 3;
	while ((string)[temp_index] != '\0')
	{
		if (ft_strncmp((string) + temp_index, "))", 2) == 0 && par_counter == 0)
			break ;
		else if ((string)[temp_index] == '(')
			par_counter++;
		else if ((string)[temp_index] == ')')
			par_counter--;
		temp_index++;
	}
	return (temp_index);
}

static int		interpreter_module(t_shell *const shell,
					char **tape,
					struct s_ari_node **const node_list)
{
	int		ret;

	ret = process_word(shell, tape, ARITHMATIC_TABLE);
	if (ret != 0)
	{
		printf("dollarsign expansions failed\n");
		return (ret);
	}
	ret = create_token_list(shell->env, *tape, node_list);
	ft_strdel(tape);
	if (ret != 0)
	{
		return (bad_subst_err);
	}
	reconstruct_input_from_list(*node_list); //temporary
	*tape = arithmatic_run_math_operations(shell->env, node_list);
	reconstruct_input_from_list(*node_list); //temporary
	arithmatic_delete_tokens(node_list);
	if (*tape == NULL)
	{
		return (bad_subst_err);
	}
	return (ret);
}

int				arithmatic_expansion(t_shell *const shell,
					char **const astring,
					size_t *const aread_index,
					size_t *const awrite_index)
{
	struct s_ari_node	*token_list;
	size_t				tmp_ind;
	char				*tape;
	char				*new_astring;

	tmp_ind = find_length(*astring, *aread_index);
	if ((*astring)[tmp_ind] == '\0')
	{
		ft_dprintf(2, "Cetushell: arithmatic expansion missing closing parenthesis\n");
		return (bad_subst_err);
	}
	tape = ft_strsub(*astring, *aread_index + 3, (tmp_ind - *aread_index) - 3);
	if (tape == NULL)
		return (malloc_error);
	token_list = NULL;
	if (interpreter_module(shell, &tape, &token_list) != 0)
		return (bad_subst_err);
	if (ft_asprintf(&new_astring, "%.*s%s%s", *awrite_index, *astring,
		tape, *astring + tmp_ind + 2) == -1)
		return (malloc_error);
	free(tape);
	*awrite_index += ft_strlen(tape);
	*aread_index = *awrite_index - 1;
	free(*astring);
	*astring = new_astring;
	return (0);
}
