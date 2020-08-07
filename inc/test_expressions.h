/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_expressions.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 14:34:16 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/30 14:34:16 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_EXPRESSIONS_H
# define TEST_EXPRESSIONS_H

# define UNARY_OP_STR "abcdefghLprSsuwxzn"
# define UNIX_TRUE 0
# define UNIX_FALSE 1
# define SYNTAX_ERROR 2
# define INTEGER_ERROR 3

/*
** abcdefghLprSsuwxzn
*/
typedef enum	e_unary_op {
	a_exists_f,
	is_block_f,
	is_char_f,
	is_dir,
	exists_f,
	is_reg_f,
	group_id_set_f,
	h_is_sym_link_f,
	is_sym_link_f,
	is_fifo_f,
	is_readable_f,
	is_socket_f,
	is_non_zero_f,
	user_id_set_f,
	is_writable_f,
	is_exec_f,
	is_zero_s,
	is_non_zero_s,
	unary_op_count
}				t_unary_op;

int		unary_expression(char **expr, char *argz);
int		binary_expression(char **expr, char *argz);

#endif
