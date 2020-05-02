/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/02 11:28:01 by devan         #+#    #+#                 */
/*   Updated: 2020/05/02 11:28:01 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_list.h"
#include "executor.h"

struct s_builtin	g_builtins[] = {
	{"cd", builtin_cd},
	{"env", builtin_env},
	{"set", builtin_set},
	{"unset", builtin_unset},
	{"setshell", builtin_setshell},
	{"unsetshell", builtin_unsetshell},
	{"echo", builtin_echo},
	{"exit", builtin_exit},
	{NULL, NULL},
};

static int	execute_builtin(t_command *command, t_env *env);
{
	int	ret;
	int i;

	ret = 0;
	i = 0;
	while (g_builtins[i].builtin_name != NULL)
	{
		if (ft_strcmp(command->argv[0], g_builtins[i].builtin_name) == 0)
		{
			ret = g_builtins[i].func(command, env);
			if (ret != 0)
				handle_name_error(ret,  g_builtins[i].builtin_name);
		}
		i++;
	}
	return (ret);
}

int		is_builtin(char *exec_name)
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


