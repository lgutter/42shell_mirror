/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_set.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/08 01:13:03 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtins.h"
#include "executor.h"

int				builtin_set(t_shell *shell, char **argv)
{
	t_env	*head;

	(void)argv;
	if (shell == NULL)
		return (1);
	if (ft_str_arr_len(argv) > 1)
		ft_printf("set: no arguments needed, arguments ignored\n\n");
	head = shell->env;
	while (head != NULL)
	{
		if ((head->type & SHELL_VAR) != 0)
			ft_printf("%s=%s%c", head->key, head->value, '\n');
		head = head->next;
	}
	return (0);
}

int				builtin_env(t_shell *shell, char **argv)
{
	t_env	*head;

	(void)argv;
	if (shell == NULL)
		return (1);
	head = shell->env;
	while (head != NULL)
	{
		if ((head->type & ENV_VAR) != 0)
			ft_printf("%s=%s%c", head->key, head->value, '\n');
		head = head->next;
	}
	return (0);
}
