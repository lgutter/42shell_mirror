/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_home.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 11:25:53 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/25 11:25:53 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int				expand_home(t_env *env_list, char **string,
													size_t *read, size_t *write)
{
	char	*temp;
	char	*value;

	if (string == NULL || *string == NULL || read == NULL || write == NULL)
		return (-1);
	temp = *string;
	if (temp[0] == '~' && (temp[1] == '\0' || temp[1] == '/'))
	{
		value = ft_getenv(env_list, "HOME", VAR_TYPE);
		if (value == NULL)
			return (0);
		temp = ft_strjoin(value, (temp + 1));
		if (temp == NULL)
		{
			free(value);
			return (-1);
		}
		*write += ft_strlen(value);
		*read = *write;
		free(value);
		free(*string);
		*string = temp;
	}
	return (0);
}
