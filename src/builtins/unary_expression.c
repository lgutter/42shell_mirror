/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unary_expression.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 14:21:46 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/30 14:21:46 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "test_expressions.h"
#include "utils.h"
#include <sys/stat.h>
#include <unistd.h>

static int	file_type_check(t_unary_op operator, struct stat statbuf)
{
	if (operator == is_sym_link_f || operator == h_is_sym_link_f)
		return (S_ISLNK(statbuf.st_mode) == true ? UNIX_TRUE : UNIX_FALSE);
	else if (operator == is_block_f)
		return (S_ISBLK(statbuf.st_mode) == true ? UNIX_TRUE : UNIX_FALSE);
	else if (operator == is_char_f)
		return (S_ISCHR(statbuf.st_mode) == true ? UNIX_TRUE : UNIX_FALSE);
	else if (operator == is_dir)
		return (S_ISDIR(statbuf.st_mode) == true ? UNIX_TRUE : UNIX_FALSE);
	else if (operator == is_reg_f)
		return (S_ISREG(statbuf.st_mode) == true ? UNIX_TRUE : UNIX_FALSE);
	else if (operator == is_fifo_f)
		return (S_ISFIFO(statbuf.st_mode) == true ? UNIX_TRUE : UNIX_FALSE);
	else if (operator == is_socket_f)
		return (S_ISSOCK(statbuf.st_mode) == true ? UNIX_TRUE : UNIX_FALSE);
	else
		return (UNIX_TRUE);
}

static int	file_expression(t_unary_op operator, char *operand)
{
	struct stat	statbuf;
	int			ret;

	ft_memset(&statbuf, 0, sizeof(struct stat));
	if (operator == is_sym_link_f || operator == h_is_sym_link_f)
		ret = lstat(operand, &statbuf);
	else
		ret = stat(operand, &statbuf);
	if (ret != 0)
		return (UNIX_FALSE);
	else if (operator == group_id_set_f)
		return ((S_ISGID & statbuf.st_mode) == 0 ? UNIX_FALSE : UNIX_TRUE);
	else if (operator == user_id_set_f)
		return ((S_ISUID & statbuf.st_mode) == 0 ? UNIX_FALSE : UNIX_TRUE);
	else if (operator == is_readable_f)
		return (access(operand, R_OK) == 0 ? UNIX_TRUE : UNIX_FALSE);
	else if (operator == is_writable_f)
		return (access(operand, W_OK) == 0 ? UNIX_TRUE : UNIX_FALSE);
	else if (operator == is_exec_f)
		return (access(operand, X_OK) == 0 ? UNIX_TRUE : UNIX_FALSE);
	else if (operator == is_non_zero_f)
		return (statbuf.st_size > 0 ? UNIX_TRUE : UNIX_FALSE);
	else
		return (file_type_check(operator, statbuf));
}

int			unary_expression(char **expr, char *argz)
{
	t_unary_op	operator;

	if (expr == NULL || expr[0] == NULL || expr[1] == NULL)
		return (SYNTAX_ERROR);
	if (expr[0][0] != '-' || expr[0][1] == '\0' || expr[0][2] != '\0' ||
		ft_strchr(UNARY_OP_STR, expr[0][1]) == NULL)
	{
		ft_dprintf(STDERR_FILENO,
			"Cetushell: %s: %s: unary operator expected\n", argz, expr[0]);
		return (SYNTAX_ERROR);
	}
	operator = (ft_strlenc(UNARY_OP_STR, expr[0][1], unary_op_count));
	if (operator == is_zero_s || operator == is_non_zero_s)
	{
		if ((expr[1][0] == '\0' && operator == is_zero_s) ||
			(expr[1][0] != '\0' && operator == is_non_zero_s))
			return (UNIX_TRUE);
		else
			return (UNIX_FALSE);
	}
	else
		return (file_expression(operator, expr[1]));
}
