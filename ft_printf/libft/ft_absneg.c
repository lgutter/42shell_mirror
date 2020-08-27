/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_absneg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 19:35:02 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 19:35:03 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

long	ft_absneg(long integer)
{
	if (integer > 0)
	{
		return (integer * -1);
	}
	return (integer);
}
