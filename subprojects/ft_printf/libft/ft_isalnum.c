/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 22:06:46 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 22:06:47 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_isalnum(int character)
{
	if (character <= 'Z' && character >= 'A')
	{
		return (1);
	}
	else if (character <= 'z' && character >= 'a')
	{
		return (1);
	}
	else if (character <= '9' && character >= '0')
	{
		return (1);
	}
	return (0);
}
