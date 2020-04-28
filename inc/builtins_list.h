/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_list.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:23:25 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/29 16:23:25 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_LIST_H
# define BUILTINS_LIST_H

static const char	*g_builtins[] =
{
	"echo",
	"cd",
	"setenv",
	"unsetenv",
	"env",
	"exit",
	"setshell",
	"unsetshell",
	NULL
};

#endif
