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

size_t			is_executable(char *path)
{
	struct stat		statbuff;

	if (path == NULL)
		return (1);
	if (lstat(path, &statbuff) == -1)
		return (1);
	if ((statbuff.st_mode & S_IXUSR))
		return (0);
	return (1);
}

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
	if (shell->hash == NULL)
		return (1);
	shell->hash->hl = ft_memalloc(sizeof(t_hentry));
	if (shell->hash->hl == NULL)
		return (1);
	shell->hash->ht = ft_memalloc(sizeof(t_hentry *) * HT_SIZE);
	if (shell->hash->ht == NULL)
		return (1);
	shell->hash->hit = ft_memalloc(sizeof(size_t) * HT_SIZE);
	if (shell->hash->hit == NULL)
		return (1);
	return (0);
}

void	set_hashhit(t_shell *shell, t_pipe_sequence *pipe)
{
	unsigned long	hash;
	t_pipe_sequence *head;

	head = pipe;
	if (shell->hash == NULL || shell->hash->hit == NULL)
		return ;
	while (head != NULL)
	{
		hash = create_hash(pipe->simple_command->argv[0], HT_SIZE);
		if (shell->hash != NULL && shell->hash->hit != NULL)
		{
			shell->hash->hit[hash] = shell->hash->hit[hash] + 1;
		}
		head = head->next;
	}
}
