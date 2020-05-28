/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 20:17:09 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/23 20:17:16 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *string, int filedes)
{
	write(filedes, string, ft_strlen(string));
	write(filedes, "\n", 1);
}
