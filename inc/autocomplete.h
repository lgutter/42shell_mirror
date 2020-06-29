/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   autocomplete.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: devanando <devanando@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 22:41:30 by devanando     #+#    #+#                 */
/*   Updated: 2020/06/24 15:25:12 by devanando     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETE_H
# define AUTOCOMPLETE_H

# include "input_handling.h"
# include "environment.h"

typedef unsigned long	t_opt;

typedef struct			s_clist
{
	char				*match;
	size_t				length;
	size_t				type;
	struct s_clist		*next;
}						t_clist;

typedef struct			s_complete
{
	char				*to_complete;
	size_t				to_complen;
	t_opt				options;
	size_t				max_len;
	t_clist				*list;
}						t_complete;

# define EXECUTABLES    1
# define BUILTINS       2
# define SHELLVAR       4
# define DIRECTORIES    8
# define FILES          16

int		auto_complete(t_shell *shell);
int		complete_var(t_env *env, t_complete *comp);
int		add_complete_list(t_complete *comp, char *match);
#endif