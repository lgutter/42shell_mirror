/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 15:07:53 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/16 15:29:19 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	ft_striter(char *string, void (*function)(char *))
{
	unsigned int index;

	index = 0;
	while (string[index] != '\0')
	{
		((*function)(&string[index]));
		index++;
	}
}
