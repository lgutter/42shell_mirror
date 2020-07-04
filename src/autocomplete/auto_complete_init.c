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

static size_t	search_cd(char *string)
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

static char		*is_op_offset(t_buff *buffer)
{
	size_t 	i;
	char	*op;
	
	i = (buffer->index != 0) ? buffer->index - 1 : buffer->index;
	while (i > 0)
	{
		if (buffer->buff[i] == '|' || buffer->buff[i] == ';' || buffer->buff[i] == '&'
			|| buffer->buff[i] == '>' || buffer->buff[i] == '<')
		{
			i++;
			break ;
		}
		i--;
	}
	if (i >= buffer->index)
		op = ft_strdup("");
	else
		op = ft_strdup(&buffer->buff[i]);
	return (op);
}

static char		*is_space_offset(char *simple_command)
{
	int		i;
	char	*trim;

	trim = ft_strtrim(simple_command);
	i = (int)ft_strlen(trim) - 1;
	while (i > 0)
	{
		if (trim[i] == ' ')
		{
			i++;
			break ;
		}
		i--;
	}
	if (i < 0)
		i = 0;
	return (ft_strdup(&trim[i]));
}

static t_opt	get_autocomp_opt(char *to_complete, char *command)
{
	t_opt	options;

	options = 0;
	if (strncmp("${", to_complete, 2) == 0)
		options |= VAR_DBRACK;
	else if (to_complete[0] == '$')
		options |= VAR_DOLLAR;
	else if (to_complete[0] != '.' && to_complete[0] != '/')
		options = (BUILTINS | EXECUTABLES);
	else
	{
		options |= FILES | DIRECTORIES;
		if (search_cd(command) == 0)
			options ^= FILES;
	}
	return (options);
}

size_t			initialize_complete(t_complete *com, t_buff *buffer)
{
	char	*simple_command;

	if (com == NULL || buffer == NULL || buffer->buff == NULL)
		return (1);
	simple_command = is_op_offset(buffer);
	if (simple_command == NULL)
		return (1);
	com->to_complete = is_space_offset(simple_command);
	if (com->to_complete == NULL)
	{
		free(simple_command);
		return (1);
	}
	com->to_complen = ft_strlen(com->to_complete);
	com->options = get_autocomp_opt(com->to_complete, simple_command);
	free(simple_command);
	return (0);
}
