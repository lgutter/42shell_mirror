/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 14:56:13 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/16 14:56:15 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *string, void (*function)(unsigned int, char *))
{
	unsigned int index;

	index = 0;
	while (string[index] != '\0')
	{
		((*function)(index, &string[index]));
		index++;
	}
}
