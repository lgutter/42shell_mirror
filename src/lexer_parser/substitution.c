/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   substitution.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nloomans <nloomans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by nloomans      #+#    #+#                 */
/*   Updated: Invalid date        by nloomans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_printf.h"
#include "substitution.h"

static ssize_t	find_squote(const char *input, ssize_t acc)
{
	if (input[0] == '\0')
		return (-1);
	if (input[0] == '\'')
		return (subst_length_tail(input + 1, acc + 1));
	return (find_squote(input + 1, acc + 1));
}

static ssize_t	find_dquote(const char *input, ssize_t acc)
{
	int sub_subst_length;

	if (input[0] == '\0')
		return (-1);
	if (input[0] == '"')
		return (subst_length_tail(input + 1, acc + 1));
	if (input[0] == '\\')
	{
		if (input[1] == '\0')
			return (-1);
		return (find_dquote(input + 2, acc + 2));
	}
	if (input[0] == '$' && input[1] == '(')
	{
		sub_subst_length = subst_length(input + 1) + 1;
		if (sub_subst_length == -1)
			return (-1);
		return (find_dquote(input + sub_subst_length,
			acc + sub_subst_length));
	}
	return (find_dquote(input + 1, acc + 1));
}

ssize_t			arith_length_tail(const char *input, ssize_t acc)
{
	int sub_subst_length;

	if (input[0] == '\0')
		return (-1);
	if (input[0] == ')' && input[1] == ')')
		return (acc + 2);
	if (input[0] == '$' && input[1] == '(')
	{
		sub_subst_length = subst_length(input + 1) + 1;
		if (sub_subst_length == -1)
			return (-1);
		return (arith_length_tail(input + sub_subst_length,
			acc + sub_subst_length));
	}
	return (arith_length_tail(input + 1, acc + 1));
}

ssize_t			subst_length_tail(const char *input, ssize_t acc)
{
	int sub_subst_length;

	if (input[0] == '\0')
		return (-1);
	if (input[0] == '\'')
		return (find_squote(input + 1, acc + 1));
	if (input[0] == '"')
		return (find_dquote(input + 1, acc + 1));
	if (input[0] == ')')
		return (acc + 1);
	if (input[0] == '\\')
	{
		if (input[1] == '\0')
			return (-1);
		return (subst_length_tail(input + 2, acc + 2));
	}
	if (ft_strchr("$<>", input[0]) != NULL && input[1] == '(')
	{
		sub_subst_length = subst_length(input + 1) + 1;
		if (sub_subst_length == -1)
			return (-1);
		return (subst_length_tail(input + sub_subst_length,
			acc + sub_subst_length));
	}
	return (subst_length_tail(input + 1, acc + 1));
}

ssize_t			subst_length(const char *input)
{
	if (input == NULL || input[0] != '(')
		return (-1);
	if (input[1] == '(')
		return (arith_length_tail(input + 2, 2));
	return (subst_length_tail(input + 1, 1));
}
