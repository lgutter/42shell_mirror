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

#include <stdio.h>
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
}

static size_t	find_length(const char *string, size_t aread_index)
{
	int     	par_counter;
	size_t  	temp_index;
	
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

	//do all dollar expansions
	ret = process_word(shell, tape, ALL_QUOTES_TABLE);
	if (ret != 0)
	{
		printf("dollarsign expansions failed\n");
		return (ret);
	}

	
	ret = create_token_list(shell->env, *tape, node_list);
	printf("actual tape:\033[33m %s\033[0m\n", *tape);//temporary
	reconstruct_input_from_list(*node_list);//temporary
	return (ret);
}

int				arithmatic_expansion(t_shell *const shell,
					char **const astring,
					size_t *const aread_index,
					size_t *const awrite_index)
{
	struct s_ari_node	*token_list;
	size_t  			temp_index;
	char				*tape;
	char				*new_astring;

	temp_index = find_length(*astring, *aread_index);
	if ((*astring)[temp_index] == '\0')
	{
		ft_dprintf(2, "Cetushell: arithmatic expansion missing closing parenthesis\n");
		return (bad_subst_err);
	}
	tape = ft_strsub(*astring, *aread_index + 3, (temp_index - *aread_index) - 3);
	printf("|%s|\n", tape);
	if (tape == NULL)
	{
		return (bad_subst_err);
	}
	token_list = NULL;
	if (interpreter_module(shell, &tape, &token_list) != 0)
	{
		return (bad_subst_err);
	}
	free(tape);
	tape = arithmatic_run_math_operations(shell->env, &token_list);
	reconstruct_input_from_list(token_list); //temporary
	arithmatic_delete_tokens(&token_list);

	ft_asprintf(&new_astring, "%.*s%s%s", *awrite_index, *astring,
		tape, *astring + temp_index + 2);
	*awrite_index += ft_strlen(tape);
	*aread_index = *awrite_index - 1;
	free(*astring);
	*astring = new_astring;

	free(tape); //insert number to astring
	(void)awrite_index;
	return (0);
}
