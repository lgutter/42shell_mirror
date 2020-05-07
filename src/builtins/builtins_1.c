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
	{"set", builtin_set},
	{"unset", builtin_unset},
	{"setshell", builtin_set},
	{"unsetshell", builtin_unset},
	{"echo", builtin_echo},
	{NULL, NULL},
};

int					execute_builtin(t_command *command, t_env *env)
{
	int	ret;
	int i;

	ret = 0;
	i = 0;
	while (g_builtins[i].builtin_name != NULL)
	{
		if (ft_strcmp(command->argv[0], g_builtins[i].builtin_name) == 0)
			ret = g_builtins[i].f(command, &env);
		i++;
	}
	return (ret);
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
	if (command->argc >= 2 && ft_strcmp(command->argv[1], "-n") == 0)
	{
		no_newline = 1;
		i = 2;
	}
	else
	{
		no_newline = 0;
		i = 1;
	}
	while (i < command->argc)
	{
		ft_printf("%s", command->argv[i]);
		if (i < command->argc - 1)
			ft_printf(" ");
		i++;
	}
	if (!no_newline)
		ft_printf("\n");
	return (0);
}
