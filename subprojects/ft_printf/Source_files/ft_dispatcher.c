/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dispatcher.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 16:25:46 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/29 15:27:50 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_formatter	ft_dispatcher(char conv_flag)
{
	static const t_formatter formatter[255] = {
		['c'] = &ft_formatchar,
		['s'] = &ft_formatstring,
		['d'] = &ft_formatdecimal,
		['i'] = &ft_formatdecimal,
		['o'] = &ft_format_octal,
		['p'] = &ft_formatpointer,
		['X'] = &ft_format_upphex,
		['x'] = &ft_format_lowhex,
		['u'] = &ft_format_unsigneddecimal,
		['f'] = &ft_format_floats,
	};

	return (formatter[(unsigned int)conv_flag]);
}
