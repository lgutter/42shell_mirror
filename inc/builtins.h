/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:23:25 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/29 16:23:25 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "environment.h"
# include "executor.h"

typedef int		t_builtin_func(t_command *command, t_env **env);

struct			s_builtin
{
	char			*builtin_name;
	t_builtin_func	*f;
};

int			builtin_cd(t_command *command, t_env **env);
int			builtin_env(t_command *command, struct s_env **env);
int			builtin_set(t_command *comm, t_env **env);
int			builtin_unset(t_command *command, t_env **env);
int			builtin_echo(t_command *command, t_env **env);
int			builtin_shellenv(t_command *command, struct s_env **env);

#endif
