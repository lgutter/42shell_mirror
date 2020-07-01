/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_complete_init.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 16:18:16 by devan         #+#    #+#                 */
/*   Updated: 2020/06/29 16:18:16 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

size_t		search_cd(char *string)
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
	int		i;

	i = (int)ft_strlen(simple_command) - 1;
	while (i > 0)
	{
		if (simple_command[i] == ' ')
		{
			i++;
			break ;
		}
		i--;
	}
	if (i < 0)
		i = 0;
	return (i);
}

t_opt		get_auto_complete_opt(char *to_complete, char *command, size_t i)
{
	t_opt	options;

	options = 0;
	if (strncmp("${", to_complete, 2) == 0)
		options |= VAR_DBRACK;
	else if (to_complete[0] == '$')
		options |= VAR_DOLLAR;
	else if (i < 1 && to_complete[0] != '.' && to_complete[0] != '/')
		options = (BUILTINS | EXECUTABLES);
	else
	{
		options |= FILES | DIRECTORIES;
		if (search_cd(command) == 0)
			options ^= FILES;
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
	com->to_complen = ft_strlen(com->to_complete);
	com->options = get_auto_complete_opt(com->to_complete, simple_command, i);
	free(simple_command);
	return (0);
}
