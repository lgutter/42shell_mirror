/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 16:29:21 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/14 16:29:21 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "handle_error.h"
# include "utils.h"

/*
**	Struct to store the environment variables in a linked list.
**	fields:
**	key:	The variable name. i.e. HOME
**	value:	The value of the variable. i.e. /Users/lgutter
**	next:	A pointer to the next element in the list of env variables
*/
typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

/*
**	converts the system char **environ to a linked list of our type t_env
**	returns the start of the list on succes, or NULL on failure.
**	(on failure, error will be printed)
*/
t_env				*dup_sys_env(void);

/*
**	takes the env and a key as argument and returns the value.
**	example: 'ft_getenv("PWD");' will return the path of our current directory.
**	when an error occurs, returns NULL.
**	(on failure, error will be printed)
*/
char				*ft_getenv(t_env *env, const char *key);

/*
**	Takes env, a key, value, and either 'y' or 'n' as arguments.
**	If 'key' exists in env and 'overwrite' is 'y', overwrites the value.
**	If 'key' does not exist, adds it to env and sets the value.
**	Returns the following:
**	0 on succes, an errid error code on failure.
**	(on failure, error will be printed)
*/
int					ft_setenv(t_env *env, const char *key,
									const char *value, char overwrite);

/*
**	takes env and a key as argument and removes it from our environment.
**	returns the following:
**	0 on succes, an errid error code on failure.
**	(on failure, error will be printed)
*/
int					ft_unsetenv(t_env *env, const char *key);

/*
**	converts our linked list of type t_env to the the system style char **envp.
**	returns the an char ** on succes, or NULL on failure.
**	(on failure, error will be printed)
*/
char				**convert_env_to_envp(t_env *list_start);

/*
**	Takes a pointer to a string and the env list,
**	and expands the string correctly if it starts with ~ or $.
**	on succes, frees the old string and replaces it with the new one.
**	on failure, nothing is changed.
**	Returns:
**	- 0 on succes.
**	- errid error code on failure.
*/
int					expand_variable(t_env *env_list, char **string);

/*
**	Takes a pointer to an environment list, and frees everything in it.
**	Returns:
**	- 0 on succes.
**	- errid error code on failure.
*/
int					free_env_list(t_env *env_list);

#endif
