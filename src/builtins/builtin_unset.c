/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/08 01:22:28 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtins.h"
#include "executor.h"

static int	get_unset_opts(char **argv, int *i)
{
	int		opts;

	opts = (ft_strcmp(argv[0], "unsetenv") == 0) ? ENV_VAR : SHELL_VAR;
	while (argv[*i] != NULL && argv[*i][0] == '-' && argv[*i][1] == '-')
	{
		if (ft_strcmp(argv[*i], "--help") == 0)
		{
			ft_dprintf(2, "Usage: %s [OPTION]... [KEY=VALUE]...\n\n", argv[0]);
			ft_dprintf(2, "Options:\n\t--help:\tprint this usage.\n");
			ft_dprintf(2, "\t--force:\tread only attributes are ignored.\n");
			return (-1);
		}
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

static int	handle_unsetenv(char *arg, char *argz, t_env *env, int opts)
{
	int ret;

	ret = ft_unsetenv(env, arg, opts);
	if (ret != 0)
		handle_prefix_error_str(ret, argz, arg);
	return (ret);
}

int			builtin_unset(t_command *comm, t_env *env)
{
	int		i;
	int		ret;
	int		opts;

	i = 1;
	ret = 0;
	if (comm == NULL || env == NULL || comm->argv == NULL)
		return (-1);
	if (comm->argc == 1)
	{
		handle_prefix_error(too_few_arguments, comm->argv[0]);
		return (1);
	}
	opts = get_unset_opts(comm->argv, &i);
	if (opts < 0)
		return (1);
	while (i < comm->argc && comm->argv[i] != NULL)
	{
		if (handle_unsetenv(comm->argv[i], comm->argv[0], env, opts) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
