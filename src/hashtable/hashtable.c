/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashtable.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 18:43:31 by devan         #+#    #+#                 */
/*   Updated: 2020/07/24 18:43:31 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "hashtable.h"
#include "executor.h"

static size_t	find_hashcol(t_hentry *entry, char **path, char *exec)
{
	t_hentry		*head;

	head = entry->next_col;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, exec) == 0)
		{
			*path = ft_strdup(head->value);
			return (0);
		}
		head = head->next_col;
	}
	return (0);
}

size_t			find_hashexec(t_hashtable *table, char **path, char *exec)
{
	unsigned long	hash;

	if (table == NULL || exec == NULL || table->ht == NULL || table->hl == NULL
		|| path == NULL)
		return (1);
	hash = create_hash(exec, HT_SIZE);
	if (table->ht[hash] != NULL &&
			ft_strcmp(table->ht[hash]->key, exec) == 0)
	{
		*path = ft_strdup(table->ht[hash]->value);
		return (0);
	}
	else if (table->ht[hash] != NULL
			&& table->ht[hash]->next_col != NULL)
	{
		if (find_hashcol(table->ht[hash], path, exec) != 0)
			return (0);
	}
	return (1);
}

int				init_hashtable(t_shell *shell)
{
	if (shell == NULL)
		return (1);
	shell->hash = ft_memalloc(sizeof(t_hashtable));
	shell->hash->exec_len = 14;
	if (shell->hash == NULL)
		return (1);
	shell->hash->hl = ft_memalloc(sizeof(t_hentry));
	if (shell->hash->hl == NULL)
		return (1);
	shell->hash->ht = ft_memalloc(sizeof(t_hentry *) * HT_SIZE);
	if (shell->hash->ht == NULL)
		return (1);
	return (0);
}

static size_t	add_hash_col(t_shell *shell, t_hentry *col, char *path,
								char *argz)
{
	t_hentry *entry;

	entry = col;
	while (entry->next_col != NULL &&
			ft_strcmp(entry->next_col->key, argz) != 0)
		entry = entry->next_col;
	if (entry->next_col == NULL)
		if (add_to_hash(shell, path, argz) != 0)
			return (1);
	if (entry->next_col != NULL)
		entry->next_col->hit++;
	return (0);
}

size_t			set_hash(t_shell *shell, t_pipe_sequence *pipe)
{
	unsigned long	hash;
	char			*argz;
	char			*path;

	path = NULL;
	argz = pipe->simple_command->argv[0];
	if (shell == NULL || shell->env == NULL || argz == NULL
		|| ft_strlen(path) == 0)
		return (1);
	hash = create_hash(argz, HT_SIZE);
	if (find_executable(shell->env, &path, argz) != 0)
		return (1);
	if (shell->hash->ht[hash] == NULL)
	{
		if (add_to_hash(shell, path, argz) != 0)
			return (1);
	}
	else if (ft_strcmp(shell->hash->ht[hash]->key, argz) != 0)
	{
		if (add_hash_col(shell, shell->hash->ht[hash], path, argz) != 0)
			return (1);
		return (0);
	}
	shell->hash->ht[hash]->hit++;
	return (0);
}

