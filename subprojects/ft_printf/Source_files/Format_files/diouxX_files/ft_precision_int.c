/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_precision_int.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 14:06:17 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/29 14:48:05 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*final_str(char *number, size_t len, size_t neg, size_t precision)
{
	char	*new;
	size_t	i;

	i = neg;
	new = ft_strnew(precision + neg + 1);
	if (new != NULL)
	{
		if (neg == 1)
			new[0] = '-';
		while (precision > len)
		{
			new[i] = '0';
			precision--;
			i++;
		}
		ft_strcpy(&(new[i]), &(number[neg]));
	}
	free(number);
	return (new);
}

char		*ft_precision_int(t_info *info, char *number)
{
	size_t	len;
	size_t	neg;

	if (number != NULL)
	{
		len = ft_strlen(number);
		neg = 0;
		if (number[0] == '-')
		{
			len--;
			neg = 1;
		}
		else if (number[0] == '0' && info->precision == 0)
		{
			free(number);
			return (ft_strdup(""));
		}
		if (len < info->precision)
		{
			if (info->conv == 'o' && (info->flags & e_hash) != 0)
				info->flags -= e_hash;
			return (final_str(number, len, neg, info->precision));
		}
	}
	return (number);
}
