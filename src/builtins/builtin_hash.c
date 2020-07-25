/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_hash.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 20:39:16 by devan         #+#    #+#                 */
/*   Updated: 2020/07/25 20:39:16 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "hashtable.h"

int				builtin_hash(t_shell *shell, char **argv)
{
	if (argv[1] == NULL)
		print_hastable();
	else if (ft_strcmp(argv[0]))
}