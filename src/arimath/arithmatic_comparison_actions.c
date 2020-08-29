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

long int	arithmath_lessthan(long int num1, long int num2)
{
	return (num1 < num2);
}

long int	arithmath_greaterthan(long int num1, long int num2)
{
	return (num1 > num2);
}

long int	arithmath_and(long int num1, long int num2)
{
	return (num1 && num2);
}

long int	arithmath_or(long int num1, long int num2)
{
	return (num1 || num2);
}
