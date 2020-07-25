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

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
# ifdef __linux__
#  include <linux/limits.h>
# else
#  include <limits.h>
# endif

#include "hashtable.h"

size_t			free_hl_elem(t_hentry *hl, size_t returm)
{
	free(hl->key);
	hl->key = NULL;
	free(hl->value);
	hl->value = NULL;
	free(hl);
	hl = NULL;
	return (returm);
}

size_t		is_executable(char *file, char *path)
{
	struct stat		statbuff;
	char			complete_path[PATH_MAX];

	if (file == NULL || path == NULL || file[0] == '.')
		return (1);
	ft_snprintf(complete_path, PATH_MAX, "%s/%s", path, file);
	if (lstat(complete_path, &statbuff) == -1)
		return (1);
	if ((statbuff.st_mode & S_IXUSR))
		return (0);
	return (1);
}

int			init_hashtable(t_shell *shell)
{
	int			size;

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
	shell->hash->size_max = HT_SIZE;
	return (0);
}
