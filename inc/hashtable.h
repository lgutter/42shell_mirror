/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashtable.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 18:44:51 by devan         #+#    #+#                 */
/*   Updated: 2020/07/24 18:44:51 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASTABLE_H

#include "environment.h"
#include "cetushell.h"
#include <stdbool.h>

# define HT_SIZE 400

typedef struct		s_hentry
{
	char			*key;
	char			*value;
	size_t			coll_prot;
	size_t			hit;
	struct s_hentry *next_col;
	struct s_hentry	*next;
}					t_hentry;

typedef struct		s_hashtable
{
	t_hentry		**ht;
	t_hentry		*hl;
	int				size_max;
	int				size;
}					t_hashtable;

int			init_hashtable(t_shell *shell);

#endif