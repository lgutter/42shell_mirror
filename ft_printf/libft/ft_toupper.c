/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 22:27:45 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 22:27:46 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_toupper(int character)
{
	if (character >= 'a' && character <= 'z')
	{
		character = character - 32;
	}
	return (character);
}
