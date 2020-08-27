/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arithmatic_expansion.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 10:58:15 by aholster      #+#    #+#                 */
/*   Updated: 2020/04/20 10:58:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "arimath.h"

const char *g_op_ident_chart[] = {
	[none] = NULL,
	[penta_increment] = "+++++",
	[penta_decrement] = "-----",
	[tri_increment] = "+++",
	[tri_decrement] = "---",
	[increment] = "++",
	[decrement] = "--",
	[addition] = "+",
	[subtraction] = "-",
	[multiply] = "*",
	[divide] = "/",
	[modulo] = "%",
	[equal_or_less] = "<=",
	[equal_or_greater] = ">=",
	[lessthan] = "<",
	[greaterthan] = ">",
	[equal] = "==",
	[unequal] = "!=",
	[and] = "&&",
	[or] = "||",
	[end_terminator] = NULL,
};
