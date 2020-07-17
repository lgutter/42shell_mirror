/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_error.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:35:25 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/07 22:51:21 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_ERROR_H
# define HANDLE_ERROR_H
# include <unistd.h>
# include "ft_printf.h"

/*
**	global variable used to store the most recent internal error code.
**	this can be used to check an error state. After the error state is
**	handled, it should be set back to 0.
*/
int					g_error_internal;

/*
**	enumerations used to indentify error codes easier.
*/
typedef enum		e_error
{
	no_error,
	malloc_error,
	invalid_token,
	parsing_error,
	read_error,
	env_write_error,
	env_not_found,
	env_empty_error,
	histfile_format_error,
	error_histpath,
	no_read_permission_hist,
	no_write_permission_hist,
	history_filesize_error,
	no_such_file_or_dir,
	cmd_not_found,
	pipe_failure,
	fork_failure,
	execve_failure,
	access_denied,
	bad_fd_error,
	is_dir_error,
	ambig_redirect,
	error_ronly,
	error_inv_format,
	too_many_arguments,
	too_few_arguments,
	invalid_option,
	var_not_set,
	restore_fd_fail,
	dup2_fd_fail,
	exit_shell_code,
	not_a_dir_error,
	readdir_error,
	internal_error,
	getcwd_error,
	illegal_option,
	no_job_control,
	error_count,
}					t_error;

/*
**	handle_error takes an error_code (see error enums), and prints the
**	relevant error message, after which it returns the error code again.
**
**	arg: error_code: the error code as can be found in the error enumerations.
**	returns: the error code given as argument.
*/
int		handle_error(int error_code);

/*
**	handle_error_str takes an error_code (see error enums) and string
**	as args, and prints the relevant error message followed by the
**	string, after which it returns the error code again.
**
**	arg: error_code: the error code as can be found in the error enumerations.
**	arg: str: the string to be printed after the error message.
**	returns: the error code given as argument.
*/
int		handle_error_str(int error_code, const char *str);

/*
**	handle_error_str takes an error_code (see error enums) and integer
**	as args, and prints the relevant error message followed by the
**	integer, after which it returns the error code again.
**
**	arg: error_code: the error code as can be found in the error enumerations.
**	arg: number: the number to be printed after the error message.
**	returns: the error code given as argument.
*/
int		handle_error_int(int error_code, int number);

/*
**	handle_error_str_p takes an error_code (see error enums), a string,
**	and a pointer as args, and prints the relevant error message
**	followed by the string, after which it returns the pointer given
**	as argument. This function is useful to call in a return statement
**	when the function it is called from returns something different than an int.
**
**	arg: error_code: the error code as can be found in the error enumerations.
**	arg: str: the string to be printed after the error message.
**	returns: the error code given as argument.
*/
void	*handle_error_str_p(int error_code, const char *str, void *pointer);

/*
**	handle_error_p takes an error_code (see error enums) and a pointer
**	as args, and prints the relevant error message, after which it
**	returns the pointer given as argument. This function is useful to
**	call in a return statement when the function it is called from
**	returns something different than an int.
**
**	arg: error_code: the error code as can be found in the error enumerations.
**	arg: pointer: the pointer to be returned after the error message is printed.
**	returns: the error code given as argument.
*/
void	*handle_error_p(int error_code, void *pointer);

/*
**	d_handle_error takes an error_code (see error enums), and prints the
**	relevant error message to fd, after which it returns the error code again.
**
**	arg: error_code: the error code as can be found in the error enumerations.
**	returns: the error code given as argument.
*/
int		d_handle_error(int fd, int error_code);

/*
**	d_handle_error_str takes an error_code (see error enums) and string
**	as args, and prints the relevant error message followed by the
**	string to fd, after which it returns the error code again.
**
**	arg: fd: the file descriptor to print to.
**	arg: error_code: the error code as can be found in the error enumerations.
**	arg: str: the string to be printed after the error message.
**	returns: the error code given as argument.
*/
int		d_handle_error_str(int fd, int error_code, const char *str);

/*
**	d_handle_error_str takes an error_code (see error enums) and integer
**	as args, and prints the relevant error message followed by the
**	integer to fd, after which it returns the error code again.
**
**	arg: fd: the file descriptor to print to.
**	arg: error_code: the error code as can be found in the error enumerations.
**	arg: number: the number to be printed after the error message.
**	returns: the error code given as argument.
*/
int		d_handle_error_int(int fd, int error_code, int number);

/*
**	d_handle_error_str_p takes an error_code (see error enums), a string,
**	and a pointer as args, and prints the relevant error message
**	followed by the string to fd, after which it returns the pointer given
**	as argument. This function is useful to call in a return statement
**	when the function it is called from returns something different than an int.
**
**	arg: fd: the file descriptor to print to.
**	arg: error_code: the error code as can be found in the error enumerations.
**	arg: str: the string to be printed after the error message.
**	returns: the error code given as argument.
*/
void	*d_handle_error_str_p(int fd, int error_code,
							const char *str, void *pointer);

/*
**	d_handle_error_p takes an error_code (see error enums) and a pointer
**	as args, and prints the relevant error message to fd, after which it
**	returns the pointer given as argument. This function is useful to
**	call in a return statement when the function it is called from
**	returns something different than an int.
**
**	arg: fd: the file descriptor to print to.
**	arg: error_code: the error code as can be found in the error enumerations.
**	arg: pointer: the pointer to be returned after the error message is printed.
**	returns: the error code given as argument.
*/
void	*d_handle_error_p(int fd, int error_code, void *pointer);

int		handle_prefix_error(int error_code, char *prefix);
int		handle_prefix_error_str(int error_code, char *prefix,
								char *str);

#endif
