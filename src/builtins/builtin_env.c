/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env.c                                      :+:    :+:            */
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

int				builtin_env(t_shell *shell, char **argv)
{
	t_env	*head;

	(void)argv;
	head = shell->env;
	if (head == NULL)
		return (1);
	while (head != NULL)
	{
		if ((head->type & ENV_VAR) != 0)
			ft_printf("%s=%s%c", head->key, head->value, '\n');
		head = head->next;
	}
	return (0);
}

int				builtin_shellenv(t_shell *shell, char **argv)
{
	t_env	*head;

	(void)argv;
	head = shell->env;
	if (head == NULL)
		return (1);
	while (head != NULL)
	{
		if ((head->type & SHELL_VAR) != 0)
			ft_printf("%s=%s%c", head->key, head->value, '\n');
		head = head->next;
	}
	return (0);
}
