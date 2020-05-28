/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_precision_float.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/26 15:43:10 by lgutter       #+#    #+#                 */
/*   Updated: 2019/12/04 12:42:49 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_add_one(char *nb, size_t *prec)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * (ft_strlen(nb) + 2));
	if (temp != NULL)
	{
		temp[0] = '1';
		temp[1] = '0';
		ft_strcpy(&temp[2], &nb[1]);
		*prec += 1;
	}
	return (temp);
}

static char		*ft_padzeros(char *nb, size_t prec)
{
	char	*new;
	size_t	i;

	i = 0;
	new = (char *)malloc(sizeof(char) * (prec + 2));
	if (new != NULL)
	{
		while (ft_isdigit(nb[i]) == 1 || nb[i] == '.')
		{
			new[i] = nb[i];
			i++;
		}
		while (i <= prec)
		{
			new[i] = new[i] == '.' ? '.' : '0';
			i++;
		}
		free(nb);
		new[i] = '\0';
	}
	return (new);
}

static size_t	ft_five_exception(char *nb, size_t i)
{
	size_t	j;

	j = i + 1;
	while (nb[j] != '\0')
	{
		if (nb[j] != '0' && nb[j] != '.')
		{
			nb[i]++;
			return (i);
		}
		j++;
	}
	j = i - (1 + (i > 1 && nb[i - 1] == '.'));
	if (nb[j] % 2 == 0)
		return (j);
	nb[i]++;
	return (i);
}

static char		*ft_round_float(char *nb, size_t i, size_t *prec)
{
	i = *prec + 1;
	if (nb[i] < '5' && nb[i] >= '0')
		return (nb);
	if (nb[i] == '5')
		i = ft_five_exception(nb, i);
	if (nb[i] > '4' && nb[i] <= '9')
	{
		i = i == 0 ? 0 : i - 1;
		while (i > 0 && (nb[i] == '9' || nb[i] == '.'))
		{
			if (nb[i] != '.')
				nb[i] = '0';
			i -= (1 + (i > 1 && nb[i - 1] == '.'));
		}
		if (i == 0)
		{
			if (nb[i] == '9')
				return (ft_add_one(nb, prec));
		}
		nb[i]++;
	}
	return (nb);
}

char			*ft_float_precision(t_info *info, char *nb)
{
	size_t	i;
	size_t	prec;

	prec = 0;
	while (nb[prec] != '.')
		prec++;
	prec += info->precision;
	i = ft_strlen(nb);
	if (i <= prec)
		return (ft_padzeros(nb, prec));
	nb = ft_round_float(nb, i, &prec);
	nb[prec + (info->precision != 0 || (info->flags & e_hash) == 1)] = '\0';
	return (nb);
}
