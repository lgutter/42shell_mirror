/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/04/06 17:03:13 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "input_control.h"

void	ft_swap_rv(t_buff *buffer)
{
	size_t		temp;

	if (buffer->rv_start < buffer->rv_end)
	{
		temp = buffer->rv_start;
		buffer->rv_start = buffer->rv_end;
		buffer->rv_end = temp;
		buffer->rv_start++;
	}
}

void	free_dchar_arr(char **string)
{
	size_t		i;

	i = 0;
	if (string == NULL)
		return ;
	while (string[i] != NULL)
	{
		free(string[i]);
		i++;
	}
	free(string);
}

int		free_shell(t_shell *shell, int ret)
{
	free_history(shell->hist);
	free(shell->buffer->prompt);
	free(shell->buffer);
	free(shell);
	configure_terminal(shell, 0);
	return (ret);
}
