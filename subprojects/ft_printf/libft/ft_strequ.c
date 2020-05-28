/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strequ.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 10:47:11 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/17 10:47:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_strequ(char const *string1, char const *string2)
{
	int index;

	index = 0;
	while (string1[index] != '\0' && string2[index] != '\0')
	{
		if (string1[index] != string2[index])
			return (0);
		index++;
	}
	if (string1[index] != string2[index])
		return (0);
	return (1);
}
