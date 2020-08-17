/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_test.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 12:46:54 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/30 12:46:54 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "test_expressions.h"

static int	handle_test_expression(char **expr, char *argz, bool negate)
{
	int		ret;
	size_t	argc;

	ret = SYNTAX_ERROR;
	argc = ft_str_arr_len(expr);
	if (argc == 0)
		ret = UNIX_FALSE;
	else if (argc == 1)
		ret = expr[0][0] == '\0' ? UNIX_FALSE : UNIX_TRUE;
	else if (argc == 2)
		ret = unary_expression(expr, argz);
	else if (argc == 3)
		ret = binary_expression(expr, argz);
	else
		handle_prefix_error(too_many_arguments, argz);
	if (ret != SYNTAX_ERROR && negate == true)
		return (ret == UNIX_TRUE ? UNIX_FALSE : UNIX_TRUE);
	else
		return (ret);
}

int			builtin_test(t_shell *shell, char **argv)
{
	bool	negate;
	char	**expr;

	if (shell == NULL || argv == NULL || argv[0] == NULL ||
		(ft_strequ(argv[0], "[") == false && argv[1] == NULL))
		return (UNIX_FALSE);
	else if (ft_strequ(argv[0], "[") == true && (argv[1] == NULL ||
		ft_strequ(argv[ft_str_arr_len(argv) - 1], "]") == false))
	{
		ft_dprintf(STDERR_FILENO, "Cetushell: %s: ']' expected\n", argv[0]);
		return (SYNTAX_ERROR);
	}
	negate = false;
	if (ft_strequ(argv[1], "!") == true)
		negate = true;
	expr = &(argv[1 + negate]);
	if (ft_strequ(argv[0], "[") == true)
		expr[ft_str_arr_len(expr) - 1] = NULL;
	return (handle_test_expression(expr, argv[0], negate));
}
