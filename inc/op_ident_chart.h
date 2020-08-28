/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_ident_chart.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 11:45:42 by lgutter       #+#    #+#                 */
/*   Updated: 2020/08/28 11:45:42 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_IDENT_CHART_H
# define OP_IDENT_CHART_H

# include "arimath.h"

static const char *g_op_ident_chart[] = {
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

#endif
