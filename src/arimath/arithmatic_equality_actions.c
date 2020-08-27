/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arithmatic_expansion.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 10:58:15 by aholster      #+#    #+#                 */
/*   Updated: 2020/04/20 10:58:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

long int	arithmath_equal(long int num1, long int num2)
{
	return (num1 == num2);
}

long int	arithmath_unequal(long int num1, long int num2)
{
	return (num1 != num2);
}

long int	arithmath_equal_or_less(long int num1, long int num2)
{
	return (num1 <= num2);
}

long int	arithmath_equal_or_greater(long int num1, long int num2)
{
	return (num1 >= num2);
}
