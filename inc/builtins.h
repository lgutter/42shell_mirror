/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/02 19:55:06 by devan         #+#    #+#                 */
/*   Updated: 2020/05/10 00:41:52 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "environment.h"
# include "executor.h"

typedef int			t_builtin_func(t_command *command, t_env **env);

struct				s_builtin
{
	char			*builtin_name;
	t_builtin_func	*f;
};

int					is_builtin(char *exec_name);
int					execute_builtin(t_command *command, t_env *env);
int					builtin_cd(t_command *command, t_env **env);
int					builtin_env(t_command *command, t_env **env);
int					builtin_set(t_command *comm, t_env **env);
int					builtin_unset(t_command *command, t_env **env);
int					builtin_exit(t_command *command, t_env **env);
int					builtin_echo(t_command *command, t_env **env);
int					builtin_shellenv(t_command *command, t_env **env);

#endif
