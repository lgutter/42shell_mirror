/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_type.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 21:31:32 by devan         #+#    #+#                 */
/*   Updated: 2020/07/23 21:31:32 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			builtin_type(t_shell *shell, char **argv)
{
	size_t	i;
	char	*check;

	i = 1;
	while (argv[i] != NULL)
	{
		if (is_builtin(argv[i]) == 1)
			ft_printf("%s is a shell builtin\n", argv[i]);
		else
		{
			if (find_executable(shell->env, &check, argv[i]) != 0)
			{
				if (access(check, X_OK) == 0)
					ft_printf("%s is %s\n", argv[i], argv[i]);
				else
					ft_printf("%s not found\n", argv[i]);
			}
			else
				ft_printf("%s is %s\n", argv[i], check);
			free(check);
		}
		i++;
	}
	return (0);
}
