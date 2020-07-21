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
# include "stdbool.h"
# ifdef __linux__
#  include <linux/limits.h>
# else
#  include <limits.h>
# endif

# define USAGE	10

typedef int			t_builtin_func(t_shell *shell, char **argv);

struct				s_builtin
{
	char			*builtin_name;
	t_builtin_func	*f;
};

typedef struct		s_cd
{
	bool			to_home;
	bool			to_oldpwd;
	bool			link;
	char			*input_path;
	char			link_path[PATH_MAX];
	char			final_path[PATH_MAX];
}					t_cd;

int					is_builtin(char *exec_name);
int					execute_builtin(t_shell *shell, char **argv);
int					builtin_cd(t_shell *shell, char **argv);
int					builtin_env(t_shell *shell, char **argv);
int					builtin_set(t_shell *shell, char **argv);
int					builtin_unset(t_shell *shell, char **argv);
int					builtin_exit(t_shell *shell, char **argv);
int					builtin_echo(t_shell *shell, char **argv);
int					builtin_shellenv(t_shell *shell, char **argv);
int					builtin_jobs(t_shell *shell, char **argv);
int					builtin_bg(t_shell *shell, char **argv);

int					get_cd_options(char **argv, t_cd *cd_s);
int					get_home_oldpw(t_cd *cd_s, t_env *env);
size_t				set_old_new_pwd(t_env *env, t_cd *cd, char *old_path);

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
	{"jobs", builtin_jobs},
	{"bg", builtin_bg},
	{NULL, NULL},
};

#endif
