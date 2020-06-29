/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_complete.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: devanando <devanando@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 21:56:01 by devanando     #+#    #+#                 */
/*   Updated: 2020/06/24 15:22:05 by devanando     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input_handling.h"
#include "cetushell.h"
#include "autocomplete.h"
#include "handle_error.h"
/*
 * structure:
 * When tab pressed:
 * 1. check input give options back 
 *      > cd        : only directories
 *      > ""        : executables in PATH + builtins
 *      > "ascii"   : current dir
 *      > $ or ${}  : env + internal variables 
 * 2. check possibilities complete(dir, options)
 *      > 1 match               :complete 
 *      > fit screen 1+ match   : create matrix / selection
 *      > small creen 1+ match  : create matrix / set viewcoordinates / selection with scrolling matrix
 * 
*/

size_t        search_cd(char *string)
{
	char	**split;
	size_t	ret;
	char	*trimmed;

	trimmed = ft_strtrim(string);
	if (trimmed == NULL)
		return (1);
	split = ft_strsplit_t_s(trimmed);
	free(trimmed);
	if (split[0] != NULL && ft_strcmp(split[0], "cd") == 0)
		ret = 0;
	else
		ret = 1;
	free_dchar_arr(split);
	return (ret);
}

int			is_op_offset(size_t i, char *string)
{
	i = (i != 0) ? i - 1 : i;
	while (i > 0)
	{
		if (string[i] == '|' || string[i] == ';' || string[i] == '&')
		{
			i++;
			break ;
		}
		i--;
	}
	return (i);
}

int			is_space_offset(char *simple_command)
{
	size_t i;

	i = ft_strlen(simple_command) - 1;
	while (i > 0)
	{
		if (simple_command[i] == ' ')
		{
			i++;
			break ;
		}
		i--;
	}
	return (i);
}

t_opt		get_auto_complete_opt(char *to_complete, char *command, size_t i)
{
	t_opt	options;

	options = 0;
	options |= BUILTINS | EXECUTABLES;
	if (to_complete[0] == '$')
		options = (options & ~(BUILTINS | EXECUTABLES)) | SHELLVAR;
	else if (i != 0)
	{
		options = (options & ~(BUILTINS | EXECUTABLES)) | FILES | DIRECTORIES;
		if (search_cd(command) == 0)
			options &= ~FILES;
	}
	return (options);
}

size_t		initialize_complete(t_complete *com, t_buff *buffer)
{
	size_t	i;
	char	*simple_command;

	i = is_op_offset(buffer->index, buffer->buff);
	simple_command = ft_strdup(&buffer->buff[i]);
	if (simple_command == NULL)
		return (1);
	i = is_space_offset(simple_command);
	com->to_complete = ft_strdup(&simple_command[i]);
	if (com->to_complete == NULL)
	{
		free(simple_command);
		return (1);
	}
	com->options = get_auto_complete_opt(com->to_complete, simple_command, i);
	free(simple_command);
	return (0);
}

int			free_complete(t_complete *com, size_t ret)
{
	com = (void *)com;
	return (ret);
}

int			complete(t_complete *com)
{
	com = (void *)com;
	return (0);
}

int			auto_complete(t_shell *shell)
{
	t_complete	comp;

	if (initialize_complete(&comp, shell->buffer) != 0)
		return (handle_error(free_complete(&comp, malloc_error)));
	if (complete(&comp) != 0)
		return (handle_error(free_complete(&comp, malloc_error)));
	int fd = open("test", O_CREAT | O_APPEND | O_WRONLY, 0644);
	ft_dprintf(fd, "TEST == (%d), (%s) (%d)  \n", shell->buffer->index, comp.to_complete, comp.options);
	close(fd);
	return (0);
}
