/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_formatstring.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 16:45:31 by lgutter       #+#    #+#                 */
/*   Updated: 2019/12/04 16:05:55 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_formatstring(t_info *info)
{
	char *str;

	str = NULL;
	info->conv = 's';
	str = va_arg(info->arguments, char *);
	if (str != NULL)
		str = ft_strdup(str);
	if (str == NULL)
		str = ft_strdup("(null)");
	info->len = ft_precision_string(info, &str);
	str[info->len] = '\0';
	if ((info->flags & e_minus) != 0)
	{
		ft_write_order(info, str, "rw");
		free(str);
		return (0);
	}
	ft_write_order(info, str, "wr");
	free(str);
	return (0);
}
