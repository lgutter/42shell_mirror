/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_setvar.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/10 00:36:28 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtins.h"
#include "executor.h"

static int		get_set_opts(char **argv, int *i)
{
	int		opts;

	opts = (ft_strcmp(argv[0], "setenv") == 0) ? ENV_VAR : SHELL_VAR;
	while (argv[*i] != NULL && argv[*i][0] == '-' && argv[*i][1] == '-')
	{
		if (ft_strcmp(argv[*i], "--help") == 0)
		{
			ft_dprintf(2, "Usage: %s [OPTION]... [KEY=VALUE]...\n\n", argv[0]);
			ft_dprintf(2, "Options:\n\t--help:\tprint this usage.\n");
			ft_dprintf(2, "\t--readonly:\tvariables are made read only.\n");
			ft_dprintf(2, "\t--force:\tread only attributes are ignored.\n");
			return (-1);
		}
		else if (ft_strcmp(argv[*i], "--readonly") == 0)
			opts |= RO_VAR;
		else if (ft_strcmp(argv[*i], "--force") == 0)
			opts |= FORCE_VAR;
		else
		{
			handle_prefix_error_str(invalid_option, argv[0], argv[*i]);
			return (-1);
		}
		(*i)++;
	}
	return (opts);
}

int				builtin_setvar(t_shell *shell, char **argv)
{
	int		i;
	int		ret;
	int		opts;

	i = 1;
	ret = 0;
	if (shell == NULL || shell->env == NULL ||
		argv == NULL || argv[0] == NULL)
		return (-1);
	if (argv[1] == NULL)
	{
		if (ft_strcmp(argv[0], "setenv") == 0)
			return (builtin_env(shell, argv));
		return (builtin_set(shell, argv));
	}
	opts = get_set_opts(argv, &i);
	if (opts < 0)
		return (1);
	while (argv[i] != NULL)
	{
		if (setenv_key_value(shell->env, argv[i], argv[0], opts) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
