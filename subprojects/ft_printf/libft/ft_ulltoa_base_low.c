/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ulltoa_base_low.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 14:29:16 by ivan-tey      #+#    #+#                 */
/*   Updated: 2019/11/20 17:15:04 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_convert(unsigned long long n, \
							const unsigned base, \
							char *str, size_t i)
{
	int			res;
	char		*bstr;

	res = 0;
	bstr = "0123456789abcdefghijklmnopqrstuvqxyz";
	while (base == 1 && (i <= ft_nbrlenbase_ull(n, base)))
	{
		str[i] = '1';
		i++;
		if (i == ft_nbrlenbase_ull(n, base) - 1)
			return (str);
	}
	if (n > 0)
	{
		res = n % base;
		str[i] = bstr[res];
		i++;
		ft_convert(n / base, base, str, i);
	}
	return (str);
}

char			*ft_ulltoa_base_low(unsigned long long nb, const unsigned base)
{
	int			nb_len;
	char		*str;

	nb_len = 0;
	if (base <= 0)
	{
		return (NULL);
	}
	if (nb == 0)
	{
		return (ft_strdup("0"));
	}
	nb_len = ft_nbrlenbase_ull(nb, base);
	str = (char *)ft_strnew(sizeof(char) * (nb_len + 1));
	if (str != NULL)
	{
		str = ft_convert(nb, base, str, 0);
		str[nb_len] = '\0';
		str = ft_strrev(str, 0);
	}
	return (str);
}
