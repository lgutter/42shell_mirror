/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arithmatic_getint_from_env.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 10:58:15 by aholster      #+#    #+#                 */
/*   Updated: 2020/04/20 10:58:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

const int	g_atoi[256] = {
	['0'] = 0 + 1,
	['1'] = 1 + 1,
	['2'] = 2 + 1,
	['3'] = 3 + 1,
	['4'] = 4 + 1,
	['5'] = 5 + 1,
	['6'] = 6 + 1,
	['7'] = 7 + 1,
	['8'] = 8 + 1,
	['9'] = 9 + 1,
	['a'] = 10 + 1,
	['b'] = 11 + 1,
	['c'] = 12 + 1,
	['d'] = 13 + 1,
	['e'] = 14 + 1,
	['f'] = 15 + 1,
	['A'] = 10 + 1,
	['B'] = 11 + 1,
	['C'] = 12 + 1,
	['D'] = 13 + 1,
	['E'] = 14 + 1,
	['F'] = 15 + 1,
};

long int	arithmatic_atol_base(size_t	*const len, const char *str)
{
	bool				is_neg;
	int					base;
	const unsigned char	*ustr;
	long int			num;
	size_t				index;

	num = 0;
	index = 0;
	base = 10;
	is_neg = false;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			is_neg = true;
		index++;
	}
	ustr = (unsigned char *)str;
	if (ft_strnequ(str + index, "0x", 2) || ft_strnequ(str + index, "0X", 2))
	{
		index += 2;
		base = 16;
	}
	else if (*(str + index) == '0')
		base = 8;
	else if (g_atoi[ustr[index]] == 0)
		*len = 0;//this signals an invalid number
	while (g_atoi[ustr[index]] != 0 && g_atoi[ustr[index]] - 1 < base)
	{
		num *= base;
		num += g_atoi[ustr[index]] - 1;
		index++;
	}
	*len = index;
	if (is_neg)
		return (-num);
	return (num);
}

int			arithmatic_getint_from_env(long int *const alint,
				t_env *const env,
				const char *const key)
{
	char	*env_value;
	size_t	index;
	int		ret;

	ret = 0;
	env_value = ft_getenv(env, key, VAR_TYPE);
	if (env_value == NULL)
	{
		return (env_not_found);
	}
	*alint = arithmatic_atol_base(&index, env_value);
	if (index == 0 || env_value[index] != '\0')
	{
		ft_dprintf(2, "not a valid number: %s\n", env_value);
		ret = parsing_error;
	}
	free(env_value);
	return (ret);
}
