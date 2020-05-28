/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 20:52:48 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/23 20:52:57 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int number, int filedes)
{
	char digit;

	digit = 'a';
	if (number == -2147483648)
		write(filedes, "-2147483648", 11);
	else
	{
		if (number < 0)
		{
			write(filedes, "-", 1);
			number *= -1;
		}
		if (number / 10 > 0)
		{
			ft_putnbr_fd(number / 10, filedes);
			digit = ((number % 10) + 48);
			write(filedes, &digit, 1);
		}
		else
		{
			digit = number + 48;
			write(filedes, &digit, 1);
		}
	}
}
