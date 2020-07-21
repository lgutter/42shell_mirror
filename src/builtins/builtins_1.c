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
#include "utils.h"

char			**update_argv(char **argv)
{
	size_t	i;
	char	**new_argv;
	size_t	len;

	len = ft_str_arr_len(argv) + 1;
	i = 1;
	new_argv = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	if (new_argv == NULL)
		return (NULL);
	new_argv[len] = NULL;
	new_argv[0] = ft_strdup("setshell");
	while (i < len)
	{
		new_argv[i] = ft_strdup(argv[i - 1]);
		if (new_argv[i] == NULL)
		{
			free_dchar_arr(new_argv);
			return (NULL);
		}
		i++;
	}
	return (new_argv);
}

int					execute_builtin(t_shell *shell, char **argv)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	if (argv == NULL || argv[0] == NULL)
		return (-1);
	while (g_builtins[i].builtin_name != NULL)
	{
		if (ft_strcmp(argv[0], g_builtins[i].builtin_name) == 0)
		{
			ret = g_builtins[i].f(shell, argv);
			if (shell != NULL)
				ft_setstatus(shell->env, ret);
			return (ret);
		}
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

int					builtin_echo(t_shell *shell, char **argv)
{
	int i;
	int no_newline;

	(void)shell;
	no_newline = 0;
	i = 1;
	if (argv == NULL)
		return (-1);
	if (argv[1] != NULL && ft_str_arr_len(argv) >= 2
				&& ft_strcmp(argv[1], "-n") == 0)
	{
		no_newline++;
		i++;
	}
	while (i < (int)ft_str_arr_len(argv) && argv[i] != NULL)
	{
		ft_printf("%s", argv[i]);
		if (i < (int)ft_str_arr_len(argv) - 1)
			ft_printf(" ");
		i++;
	}
	if (no_newline == 0)
		ft_printf("\n");
	return (0);
}
