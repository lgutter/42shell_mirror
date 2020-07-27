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
# define HASHTABLE_H

# include "environment.h"
# include "executor.h"
# include "ft_printf.h"

# define HT_SIZE 400

typedef struct		s_hentry
{
	char			*key;
	char			*value;
	unsigned long	hit;
	struct s_hentry *next_col;
	struct s_hentry	*next;
}					t_hentry;

typedef struct		s_hashtable
{
	t_hentry		**ht;
	t_hentry		*hl;
	size_t			exec_len;
}					t_hashtable;

int				init_hashtable(t_shell *shell);
size_t			add_to_hash(t_shell *shell, char *path, char *exec);
void			free_hashtable(t_shell *shell);
unsigned long	create_hash(char *key, size_t size);
void			find_hash_exec(t_hashtable *table, char **path, char *exec);
void			print_hashtable(t_hashtable *hash);
size_t			hash_duplicate(char *key, t_hashtable *table);
size_t			set_hash(t_shell *shell, t_pipe_sequence *pipe);
void			initialize_hashes(t_shell *shell);

#endif
