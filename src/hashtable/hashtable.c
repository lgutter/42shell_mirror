/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashtable.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 18:43:31 by devan         #+#    #+#                 */
/*   Updated: 2020/08/07 17:04:45 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "hashtable.h"
#include "executor.h"

void			find_hash_exec(t_hashtable *table, char **path, char *exec)
{
	t_hentry		*head;
	unsigned long	hash;

	if (table == NULL || exec == NULL || table->ht == NULL || table->hl == NULL
		|| path == NULL)
		return ;
	hash = create_hash(exec, HT_SIZE);
	if (table->ht[hash] != NULL &&
			ft_strcmp(table->ht[hash]->key, exec) == 0)
		*path = ft_strdup(table->ht[hash]->value);
	else if (table->ht[hash] != NULL
			&& table->ht[hash]->next_col != NULL)
	{
		head = table->ht[hash]->next_col;
		while (head != NULL)
		{
			if (ft_strcmp(head->key, exec) == 0)
				*path = ft_strdup(head->value);
			head = head->next_col;
		}
	}
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

static size_t	add_hash_col(t_shell *shell, t_hentry *col, char *argz)
{
	t_hentry	*entry;
	char		*path;
	size_t		ret;

	path = NULL;
	ret = 0;
	if (ft_strcmp(col->key, argz) != 0)
	{
		entry = col;
		while (entry->next_col != NULL &&
				ft_strcmp(entry->next_col->key, argz) != 0)
			entry = entry->next_col;
		if (entry->next_col == NULL)
		{
			if (find_executable(shell->env, &path, argz) == 0)
				ret = add_to_hash(shell, path, argz);
			free(path);
		}
		entry->next_col->hit++;
	}
	return (ret);
}

void			set_hash(t_shell *shell, char *argz)
{
	unsigned long	hash;
	char			*path;
	size_t			ret;

	path = NULL;
	if (shell == NULL || shell->env == NULL || argz == NULL ||
		shell->hash == NULL || is_builtin(argz) == true
		|| ft_strchr(argz, '/') != NULL)
		return ;
	hash = create_hash(argz, HT_SIZE);
	if (shell->hash->ht[hash] == NULL)
	{
		ret = find_executable(shell->env, &path, argz);
		if (ret == 0)
		{
			add_to_hash(shell, path, argz);
			shell->hash->ht[hash]->hit++;
		}
		else if (ret == cmd_not_found)
			handle_prefix_error_str(cmd_not_found, "hash", argz);
		free(path);
	}
	else if (ft_strcmp(argz, shell->hash->ht[hash]->key) == 0)
		shell->hash->ht[hash]->hit++;
	else
		add_hash_col(shell, shell->hash->ht[hash], argz);
}
