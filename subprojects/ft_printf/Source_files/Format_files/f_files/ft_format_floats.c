/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_format_floats.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/21 12:52:44 by ivan-tey      #+#    #+#                 */
/*   Updated: 2019/11/29 13:06:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_floaty_things(t_info *info, long double f,\
								long long n, char *nb)
{
	size_t	prec;
	char	*temp;

	prec = 0;
	temp = NULL;
	ft_strexpand(&nb, ".");
	while (f > 0 && (prec < 500 || prec < info->precision))
	{
		f = (f - n) * 10;
		n = (long long)f;
		temp = ft_itoa_base(n < 0 ? n * -1 : n, 10);
		ft_strexpand(&nb, temp);
		free(temp);
		prec++;
	}
	nb = ft_float_precision(info, nb);
	info->len = ft_strlen(nb) + ft_correctlen(info);
	if ((info->flags & e_minus) != 0)
		ft_write_order(info, nb, "frw");
	else if ((info->flags & e_zero) != 0)
		ft_write_order(info, nb, "fwr");
	else
		ft_write_order(info, nb, "wfr");
	free(nb);
	return (0);
}

static int		ft_formatlongdfloats(t_info *info, long double f)
{
	long long	n;
	char		*nb;

	n = (long long)f;
	nb = ft_itoa_base(n, 10);
	info->len = ft_strlen(nb);
	if (info->precfound < 0)
		info->precision = 6;
	return (ft_floaty_things(info, f, n, nb));
}

static int		ft_exceptions(t_info *info, long double f)
{
	char *err;

	err = NULL;
	if (f != f)
	{
		info->sign = 0;
		err = "nan";
		info->flags &= e_minus;
	}
	else if (f < __LDBL_MAX__ * -1 || f > __LDBL_MAX__)
	{
		if ((info->flags & e_zero) != 0)
			info->flags -= e_zero;
		err = "inf";
	}
	info->len = ft_strlen(err) + ft_correctlen(info);
	if ((info->flags & e_minus) != 0)
		return (ft_write_order(info, err, "frw"));
	return (ft_write_order(info, err, "wfr"));
}

int				ft_format_floats(t_info *info)
{
	long double	f;

	info->conv = 'f';
	if (info->precfound < 0)
		info->precision = 6;
	if ((info->lenmod & e_L) != 0)
		f = (long double)va_arg(info->arguments, long double);
	else
		f = (long double)va_arg(info->arguments, double);
	if (ft_check_sign(f) == 1)
	{
		f = f * -1;
		info->sign = -1;
	}
	else
		info->sign = 1;
	if (f != f || f > __LDBL_MAX__ || f < __LDBL_MAX__ * -1)
	{
		return (ft_exceptions(info, f));
	}
	if (f > (long double)__LONG_LONG_MAX__)
		return (ft_formatunsignedfloat(info, f));
	return (ft_formatlongdfloats(info, f));
}
