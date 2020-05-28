/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 17:05:16 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 17:05:17 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int character)
{
	if (character <= '9' && character >= '0')
	{
		return (1);
	}
	return (0);
}
