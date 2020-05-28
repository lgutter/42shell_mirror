/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 21:56:26 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 21:56:26 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_isalpha(int character)
{
	if (character <= 'Z' && character >= 'A')
	{
		return (1);
	}
	else if (character <= 'z' && character >= 'a')
	{
		return (1);
	}
	return (0);
}
