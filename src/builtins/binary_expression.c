/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   binary_expression.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 14:21:46 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/30 14:21:46 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "test_expressions.h"
#include "utils.h"

static int	integer_expression(char **expr, char *argz)
{
	int operand1;
	int operand2;

	operand1 = ft_atoi(expr[0]);
	operand2 = ft_atoi(expr[2]);
	if (ft_strequ("-eq", expr[1]) == true)
		return ((operand1 == operand2) ? UNIX_TRUE : UNIX_FALSE);
	else if (ft_strequ("-ne", expr[1]) == true)
		return ((operand1 != operand2) ? UNIX_TRUE : UNIX_FALSE);
	else if (ft_strequ("-ge", expr[1]) == true)
		return ((operand1 >= operand2) ? UNIX_TRUE : UNIX_FALSE);
	else if (ft_strequ("-gt", expr[1]) == true)
		return ((operand1 > operand2) ? UNIX_TRUE : UNIX_FALSE);
	else if (ft_strequ("-lt", expr[1]) == true)
		return ((operand1 < operand2) ? UNIX_TRUE : UNIX_FALSE);
	else if (ft_strequ("-le", expr[1]) == true)
		return ((operand1 <= operand2) ? UNIX_TRUE : UNIX_FALSE);
	ft_dprintf(STDERR_FILENO,
			"Cetushell: %s: %s: binary operator expected\n", argz, expr[1]);
	return (2);
}

int			binary_expression(char **expr, char *argz)
{
	char	*inv_int;
	int		ret;

	if (expr == NULL || expr[0] == NULL || expr[1] == NULL || expr[2] == NULL)
		return (2);
	inv_int = NULL;
	if (ft_strequ("=", expr[1]) == true || ft_strequ("==", expr[1]) == true)
		return (ft_strequ(expr[0], expr[2]) == true ? UNIX_TRUE : UNIX_FALSE);
	else if (ft_strequ("!=", expr[1]) == true)
		return (ft_strequ(expr[0], expr[2]) == true ? UNIX_FALSE : UNIX_TRUE);
	else if (ft_isdigit(expr[0][0]) == false && expr[0][0] != '-')
		inv_int = expr[0];
	else if (ft_isdigit(expr[2][0]) == false && expr[2][0] != '-')
		inv_int = expr[2];
	ret = integer_expression(expr, argz);
	if (inv_int != NULL && ret != 2)
	{
		ft_dprintf(STDERR_FILENO,
			"Cetushell: %s: %s: integer expression expected\n", argz, inv_int);
		ret = 2;
	}
	return (ret);
}
