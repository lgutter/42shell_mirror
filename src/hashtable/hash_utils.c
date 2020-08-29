/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/26 22:31:11 by devan         #+#    #+#                 */
/*   Updated: 2020/07/26 22:31:11 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

void			print_hashtable(t_hashtable *hash)
{
	t_hentry		*head;

	if (hash == NULL || hash->hl == NULL || hash->hl->key == NULL)
	{
		handle_prefix_error(empty_hash, "hash");
		return ;
	}
	head = hash->hl;
	ft_printf("Hit:\t%-*sPath:\n", hash->exec_len, "Command:");
	while (head != NULL)
	{
		ft_printf(" %d\t%-*s%s\n", head->hit, hash->exec_len,
					head->key, head->value);
		head = head->next;
	}
}

size_t			hash_duplicate(char *key, t_hashtable *table)
{
	t_hentry	*entry;

	if (table == NULL || key == NULL || table->hl == NULL)
		return (0);
	entry = table->hl;
	while (entry != NULL)
	{
		if (entry->key != NULL && ft_strcmp(entry->key, key) == 0)
			return (1);
		entry = entry->next;
	}
	return (0);
}

unsigned long	create_hash(char *key, size_t size)
{
	unsigned long	hash;

	hash = 0;
	if (key == NULL || size == 0)
		return (0);
	while (*key != '\0')
	{
		hash = ((hash << 5) + hash) + ((unsigned long)*key);
		key++;
	}
	hash = hash & (HT_SIZE - 1);
	return (hash);
}

void			free_hashtable(t_shell *shell)
{
	t_hentry	*entry;
	t_hentry	*temp;

	if (shell == NULL || shell->hash == NULL)
		return ;
	if (shell->hash->hl != NULL)
	{
		entry = shell->hash->hl;
		while (entry != NULL)
		{
			free(entry->value);
			free(entry->key);
			temp = entry->next;
			free(entry);
			entry = temp;
		}
	}
	if (shell->hash->ht != NULL)
		free(shell->hash->ht);
	free(shell->hash);
	shell->hash = NULL;
}
