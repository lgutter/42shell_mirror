/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 22:12:46 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 22:12:47 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_isascii(int character)
{
	if (character <= '\x7f' && character >= '\0')
	{
		return (1);
	}
	return (0);
}
