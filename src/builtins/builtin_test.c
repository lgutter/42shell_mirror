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

static int	handle_test_expression(char **expr, size_t argc, char *argz)
{
	int ret;

	ret = 2;
	if (argc == 0)
		ret = 1;
	else if (argc == 1)
		ret = 0;
	else if (argc == 2)
		ret = unary_expression(expr, argz);
	else if (argc == 3)
		ret = binary_expression(expr, argz);
	else
		handle_prefix_error(too_many_arguments, argz);
	return (ret);
}

int			builtin_test(t_shell *shell, char **argv)
{
	bool	negate;
	size_t	argc;
	char	**expr;
	int		ret;

	if (shell == NULL || argv == NULL || argv[0] == NULL || argv[1] == NULL)
		return (1);
	if (ft_strequ(argv[0], "[") == true &&
		ft_strequ(argv[ft_str_arr_len(argv) - 1], "]") == false)
	{
		ft_dprintf(STDERR_FILENO, "Cetushell: %s: ']' expected\n", argv[0]);
		return (2);
	}
	negate = false;
	if (ft_strequ(argv[1], "!") == true)
		negate = true;
	expr = &(argv[1 + negate]);
	if (ft_strequ(argv[0], "[") == true)
		expr[ft_str_arr_len(expr) - 1] = NULL;
	argc = ft_str_arr_len(expr);
	ret = handle_test_expression(expr, argc, argv[0]);
	if (ret != 2 && negate == true)
		return (ret == 0 ? 1 : 0);
	else
		return (ret);
}
