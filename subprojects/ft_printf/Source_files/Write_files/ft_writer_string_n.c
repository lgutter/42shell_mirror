/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_writer_string_n.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 11:19:04 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/28 11:19:04 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_writer_string_n(void *target, unsigned long long *totallen,\
					const char *string, size_t len)
{
	t_string_n_info	*info;
	size_t			i;

	i = 0;
	info = (t_string_n_info *)target;
	if (len <= 0)
	{
		len = ft_strlen(string);
	}
	while (*(info->index) < info->len && i < len && string[i] != '\0')
	{
		(info->target)[*(info->index)] = string[i];
		*(info->index) += 1;
		i++;
	}
	(info->target)[*(info->index)] = '\0';
	*totallen += i;
}
