/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt_str.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 17:28:43 by devan         #+#    #+#                 */
/*   Updated: 2020/04/15 17:28:43 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_STR_H
#define PROMPT_STR_H

typedef enum		e_prompt_type
{
	NORMAL,
	QUOTE,
	DQUOTE,
	PIPE,
	HEREDOC,
	PROMPT_COUNT,
}					t_prompt_type;

static const char	*g_prompt[PROMPT_COUNT] = {
	[NORMAL] = "cetushell>>",
	[QUOTE] = "quote>",
	[DQUOTE] = "dquote>",
	[PIPE] = "pipe>",
	[HEREDOC] = "heredoc>",
};

#endif
