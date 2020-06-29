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
# define VAR_DOLLAR     4
# define DIRECTORIES    8
# define FILES          16
# define VAR_DBRACK		32

size_t		auto_complete(t_shell *shell);
size_t		complete_var(t_env *env, t_complete *comp);
size_t		complete_exec(t_complete *comp, t_env *env);
size_t		add_complete_list(t_complete *comp, char *match);
void    	debug_complete_list(t_complete *comp);
size_t		initialize_complete(t_complete *com, t_buff *buffer);
#endif