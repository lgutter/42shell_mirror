/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 22:25:07 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 22:25:08 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_isprint(int character)
{
	if (character <= '~' && character >= ' ')
	{
		return (1);
	}
	return (0);
}
