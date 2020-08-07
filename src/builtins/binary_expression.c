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
#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

static bool	is_valid_integer(char *string)
{
	size_t		i;
	size_t		max_len;
	long long	operand;

	max_len = ft_nbrlenbase_ull(__LONG_LONG_MAX__, 10);
	i = 1;
	if (string[0] == '-' || string[0] == '+')
		max_len++;
	else if (ft_isdigit(string[0]) == false)
		return (false);
	while (string[i] != '\0')
	{
		if (ft_isdigit(string[i]) == false || i > max_len)
			return (false);
		i++;
	}
	if (i == max_len)
	{
		operand = ft_atoll(string);
		if (string[0] == '-')
			return (operand < 0 ? true : false);
		else if (operand < 0)
			return (false);
	}
	return (true);
}

static int	integer_expression(char **expr, char *argz)
{
	long long	operand1;
	long long	operand2;

	operand1 = ft_atoll(expr[0]);
	operand2 = ft_atoll(expr[2]);
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
	return (SYNTAX_ERROR);
}

int			binary_expression(char **expr, char *argz)
{
	char	*inv_int;
	int		ret;

	if (expr == NULL || expr[0] == NULL || expr[1] == NULL || expr[2] == NULL)
		return (SYNTAX_ERROR);
	inv_int = NULL;
	if (ft_strequ("=", expr[1]) == true || ft_strequ("==", expr[1]) == true)
		return (ft_strequ(expr[0], expr[2]) == true ? UNIX_TRUE : UNIX_FALSE);
	else if (ft_strequ("!=", expr[1]) == true)
		return (ft_strequ(expr[0], expr[2]) == true ? UNIX_FALSE : UNIX_TRUE);
	else if (is_valid_integer(expr[0]) == false)
		inv_int = expr[0];
	else if (is_valid_integer(expr[2]) == false)
		inv_int = expr[2];
	ret = integer_expression(expr, argz);
	if (inv_int != NULL && ret != SYNTAX_ERROR)
	{
		ft_dprintf(STDERR_FILENO,
			"Cetushell: %s: %s: integer expression expected\n", argz, inv_int);
		ret = SYNTAX_ERROR;
	}
	return (ret);
}
