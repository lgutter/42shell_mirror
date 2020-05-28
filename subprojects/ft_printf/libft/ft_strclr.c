/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strclr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 14:07:28 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/14 14:07:30 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	ft_strclr(char *string)
{
	int index;

	index = 0;
	while (string[index] != '\0')
	{
		string[index] = '\0';
		index++;
	}
}
