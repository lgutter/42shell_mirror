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

#include "environment.h"
#include "utils.h"

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
	if (string[i] == NULL)
	{
		free(string);
		return ;
	}
	while (string[i] != NULL)
	{
		free(string[i]);
		i++;
	}
	free(string);
}

int		free_shell(t_shell *shell, int ret)
{
	if (shell != NULL)
	{
		free_history(shell->hist);
		shell->hist = NULL;
		free_buffer_buffs(shell, 1);
		if (shell->buffer != NULL)
			free(shell->buffer);
		shell->buffer = NULL;
		configure_terminal(shell, 0);
		free(shell);
		free_env_list(shell->env);
	}
	return (ret);
}

int		get_here_doc(t_io_here *io_here, t_shell *shell)
{
	char	*temp;
	char	*here_doc;

	temp = NULL;
	here_doc = ft_strdup("");
	if (io_here->here_end == NULL)
		return (handle_error(parsing_error));
	while (1)
	{
		temp = prompt_shell(shell, PROMPT_HEREDOC);
		if (temp != NULL && ft_strcmp(temp, io_here->here_end) == 0)
			break ;
		str_expand_triple(&here_doc, temp, "\n");
		if (here_doc == NULL)
			return (handle_error(malloc_error));
	}
	io_here->here_doc = here_doc;
	return (0);
}

size_t	str_arr_len(char **str_array)
{
	size_t index;

	index = 0;
	if (str_array == NULL)
		return (0);
	while (str_array[index] != NULL)
	{
		index++;
	}
	return (index);
}
