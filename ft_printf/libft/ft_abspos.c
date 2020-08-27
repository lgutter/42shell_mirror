/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_abspos.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/03 21:24:41 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/03 21:24:42 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

long	ft_abspos(long integer)
{
	if (integer < 0)
	{
		return (integer * -1);
	}
	return (integer);
}
