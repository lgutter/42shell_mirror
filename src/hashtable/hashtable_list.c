/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashtable_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 18:43:31 by devan         #+#    #+#                 */
/*   Updated: 2020/07/24 18:43:31 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

static size_t		add_to_hlist(t_hentry *hl, char *exec, char *path)
{
	t_hentry	*list;

	if (exec == NULL || path == NULL)
		return (1);
	list = hl;
	if (list->key != NULL)
	{
		while (list->next != NULL)
			list = list->next;
		list->next = (t_hentry *)ft_memalloc(sizeof(t_hentry));
		list = list->next;
		if (list == NULL)
			return (malloc_error);
	}
	list->key = ft_strdup(exec);
	list->value = ft_strdup(path);
	list->next = NULL;
	if (list->key == NULL || list->value == NULL)
		return (malloc_error);
	return (0);
}

static size_t		update_hentry(t_hashtable *hash,
									t_hentry *entry, char *value)
{
	unsigned long index;

	if (ft_strcmp(entry->value, value) != 0)
	{
		free(entry->value);
		index = create_hash(entry->key, HT_SIZE);
		hash->hit[index] = 0;
		entry->value = ft_strdup(value);
		if (entry->value == NULL)
			return (malloc_error);
	}
	return (0);
}

static size_t		add_to_htable(t_hashtable *table, t_hentry *entry,
									char *exec, char *path)
{
	unsigned long	hash;
	t_hentry		*collision;

	while (entry->next != NULL && ft_strcmp(entry->key, exec) != 0)
		entry = entry->next;
	hash = create_hash(entry->key, table->size_max);
	if (table->ht[hash] == NULL)
		table->ht[hash] = entry;
	else if (ft_strcmp(table->ht[hash]->key, entry->key) != 0)
	{
		collision = table->ht[hash]->next_col;
		while (collision != NULL && ft_strcmp(collision->key, entry->key) != 0)
			collision = collision->next_col;
		if (collision != NULL && ft_strcmp(collision->key, entry->key) == 0)
			return (update_hentry(table, collision, entry->value));
		else
			collision = entry;
	}
	else
		return (update_hentry(table, table->ht[hash], path));
	return (0);
}

size_t				add_to_hash(t_shell *shell, char *path, char *exec)
{
	t_hentry		*head;
	size_t			ret;

	ret = 0;
	if (shell->hash == NULL || exec == NULL || path == NULL)
		return (1);
	if (is_executable(path) != 0)
		return (handle_error_str(cmd_not_found, path));
	if (ft_strstr(path, exec) == NULL)
		return (handle_error_str(cmd_not_found, exec));
	head = shell->hash->hl;
	if (hash_duplicate(exec, shell->hash) == 0)
		ret = add_to_hlist(head, exec, path);
	if (ret == 0)
		ret = add_to_htable(shell->hash, head, exec, path);
	return (ret);
}
