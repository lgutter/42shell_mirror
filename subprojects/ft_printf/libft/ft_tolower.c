/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 22:32:17 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 22:32:18 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_tolower(int character)
{
	if (character >= 'A' && character <= 'Z')
	{
		character = character + 32;
	}
	return (character);
}
