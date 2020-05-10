/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_1.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/07 23:10:37 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"

struct s_builtin	g_builtins[] = {
	{"cd", builtin_cd},
	{"env", builtin_env},
	{"shellenv", builtin_shellenv},
	{"setenv", builtin_set},
	{"unsetenv", builtin_unset},
	{"setshell", builtin_set},
	{"unsetshell", builtin_unset},
	{"echo", builtin_echo},
	{"exit", builtin_exit},
	{NULL, NULL},
};

int					execute_builtin(t_command *command, t_env *env)
{
	int i;

	i = 0;
	if (command == NULL || command->argv == NULL || command->argv[0] == NULL)
		return (-1);
	while (g_builtins[i].builtin_name != NULL)
	{
		if (ft_strcmp(command->argv[0], g_builtins[i].builtin_name) == 0)
			return (g_builtins[i].f(command, &env));
		i++;
	}
	return (-1);
}

int					is_builtin(char *exec_name)
{
	size_t				i;

	i = 0;
	while (g_builtins[i].builtin_name != NULL)
	{
		if (ft_strcmp(g_builtins[i].builtin_name, exec_name) == 0)
			return (1);
		i++;
	}
	return (0);
}

int					builtin_echo(t_command *command, t_env **env)
{
	int i;
	int no_newline;

	(void)env;
	no_newline = 0;
	i = 1;
	if (command == NULL || command->argv == NULL)
		return (-1);
	if (command->argv[1] != NULL && command->argc >= 2
		&& ft_strcmp(command->argv[1], "-n") == 0)
	{
		no_newline++;
		i++;
	}
	while (i < command->argc && command->argv[i] != NULL)
	{
		ft_printf("%s", command->argv[i]);
		if (i < command->argc - 1)
			ft_printf(" ");
		i++;
	}
	if (no_newline == 0)
		ft_printf("\n");
	return (0);
}
