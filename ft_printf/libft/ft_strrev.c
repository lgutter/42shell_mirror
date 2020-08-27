/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrev.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/27 13:40:07 by ivan-tey      #+#    #+#                 */
/*   Updated: 2019/10/22 12:00:46 by ivan-tey      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrev(char *str, int start)
{
	int i;
	int len;

	i = start;
	len = ft_strlen(str) - 1;
	while (i < len)
	{
		ft_swap(&str[i], &str[len]);
		i++;
		len--;
	}
	return (str);
}
