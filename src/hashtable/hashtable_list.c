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

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

#include "hashtable.h"

size_t	create_hash(char *key, size_t size)
{
	unsigned long	hash;

	hash = 0;
	while (*key != '\0')
	{
		hash = ((hash << 5) + hash) + (*key);
		key++;
	}
	hash = hash % size;
	return (hash);
}

size_t		*add_to_hlist(t_hentry *hl, char *exec, char *path)
{
	t_hentry	*list;

	if (exec == NULL || path == NULL)
		return (NULL);
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

size_t		update_hentry(t_hentry *entry, char *value)
{
	if (ft_strcmp(entry->value, value) != 0)
	{
		free(entry->value);
		entry->value = ft_strdup(value);
		entry->hit = 0;
		if (entry->value == NULL)
			return (malloc_error);
	}
	else
		entry->hit++;
	return (0);
}

size_t		add_to_htable(t_hashtable *table, t_hentry *entry)
{
	unsigned long	hash;
	t_hentry		*collision;

	hash = create_hash(entry->key, table->size);
	if (table->ht[hash] == NULL)
		table->ht[hash] = entry;
	else if (ft_strcmp(table->ht[hash], entry->key) != 0)
	{
		collision = table->ht[hash]->next_col;
		while (collision != NULL && ft_strcmp(collision->key, entry->key) != 0)
			collision = collision->next_col;
		if (collision != NULL && ft_strcmp(collision->key, entry->key) == 0)
			return (update_hentry(collision, entry->value));
		else
			collision = entry;
	}
	else
		return (update_hentry(table->ht[hash], entry->value));
	return (0);
}

size_t		add_to_hash(t_hashtable *table, char *path, char *exec)
{
	char			*complete_path;
	t_hentry		*head;
	size_t			ret;

	ret = 0;
	if (table == NULL || path == NULL || exec == NULL)
		return (1);
	head = table->hl;
	complete_path = ft_strdup(path);
	if (complete_path == NULL)
		return (malloc_error);
	str_expand_triple(&complete_path, "/", exec);
	ret = add_to_hlist(head, exec, complete_path);
	if (ret == 0)
		ret = add_to_htable(table, head);
	free(complete_path);
	return (ret);
}
