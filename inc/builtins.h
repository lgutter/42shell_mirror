/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/02 19:55:06 by devan         #+#    #+#                 */
/*   Updated: 2020/07/09 16:39:05 by devanando     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "environment.h"
# include "executor.h"

typedef int			t_builtin_func(t_command *command, t_env *env);

struct				s_builtin
{
	char			*builtin_name;
	t_builtin_func	*f;
};

int					is_builtin(char *exec_name);
int					execute_builtin(t_command *command, t_env *env);
int					builtin_cd(char **argv, t_shell *shell);
int					builtin_env(char **argv, t_shell *shell);
int					builtin_set(char **argv, t_shell *shell);
int					builtin_unset(char **argv, t_shell *shell);
int					builtin_exit(char **argv, t_shell *shell);
int					builtin_echo(char **argv, t_shell *shell);
int					builtin_shellenv(char **argv, t_shell *shell);

static const struct s_builtin	g_builtins[] = {
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

#endif
