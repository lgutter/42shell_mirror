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

static char		*is_op_offset(t_buff *buffer)
{
	size_t	i;
	char	*op;

	i = (buffer->index != 0) ? buffer->index - 1 : buffer->index;
	while (i > 0)
	{
		if (buffer->buff[i] == '|' || buffer->buff[i] == ';' ||
			buffer->buff[i] == '&' || buffer->buff[i] == '>' ||
				buffer->buff[i] == '<')
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

static size_t	get_to_complete(t_complete *comp, char *simple_command)
{
	int		i;
	int		j;

	j = ft_strlen(simple_command);
	comp->command = ft_strsplit_t_s(simple_command);
	if (comp->command == NULL || comp->command[0] == NULL)
		return (1);
	i = 0;
	while (comp->command[i] != NULL)
		i++;
	if (i > 0 && simple_command[j - 1] == ' ')
		comp->to_complete = ft_strdup("");
	else
		comp->to_complete = ft_strdup(comp->command[i - 1]);
	if (comp->to_complete == NULL)
		return (1);
	comp->to_complen = ft_strlen(comp->to_complete);
	return (0);
}

static t_opt	get_autocomp_opt(t_complete *comp)
{
	t_opt	options;

	options = 0;
	if (strncmp("${", comp->to_complete, 2) == 0)
		options |= VAR_DBRACK;
	else if (comp->to_complete[0] == '$')
		options |= VAR_DOLLAR;
	else if (comp->command[1] == NULL && comp->to_complen != 0 &&
		comp->to_complete[0] != '.' && comp->to_complete[0] != '/')
		options = (BUILTINS | EXECUTABLES);
	else
	{
		options |= FILES | DIRECTORIES;
		if (ft_strncmp("cd", comp->command[0], 2) == 0)
			options ^= FILES;
	}
	return (options);
}

size_t			initialize_complete(t_complete *com, t_buff *buffer)
{
	char	*simple_command;
	char	*trim;
	size_t	ret;

	ret = 0;
	if (com == NULL || buffer == NULL || buffer->buff == NULL)
		return (1);
	simple_command = is_op_offset(buffer);
	if (simple_command == NULL)
		return (1);
	trim = ft_strtrim(simple_command);
	if (ft_strlen(trim) == 0)
		ret = 2;
	if (ret == 0 && get_to_complete(com, simple_command) != 0)
		ret = 1;
	com->options = get_autocomp_opt(com);
	free(trim);
	free(simple_command);
	return (ret);
}
