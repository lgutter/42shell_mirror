/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_str.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:35:25 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/08 00:47:14 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_STR_H
# define ERROR_STR_H
# include "handle_error.h"

/*
**	an array of all the error strings, using the error enums as index.
**	these strings will be used to print a relevant error message.
*/
static const char	*g_error_str[error_count] = {
	[no_error] = "Error code indicates no error",
	[malloc_error] = "Malloc failed to allocate memory",
	[invalid_token] = "Token is invalid",
	[parsing_error] = "Parsing error detected",
	[read_error] = "Error while read() call",
	[env_write_error] = "Environment key exists and overwrite is off",
	[env_not_found] = "Environment key not found",
	[env_empty_error] = "Environment is empty",
	[histfile_format_error] = "Histfile formatted incorrectly",
	[error_histpath] = "Error in resolving the history path",
	[no_read_permission_hist] = "No read access for histfile",
	[no_write_permission_hist] = "No write access for histfile",
	[history_filesize_error] = "Can't resolve history filesize",
	[no_such_file_or_dir] = "No such file or directory",
	[cmd_not_found] = "Command not found",
	[pipe_failure] = "Call to pipe failed",
	[fork_failure] = "Call to fork failed",
	[execve_failure] = "Call to execve failed",
	[access_denied] = "Access denied",
	[bad_fd_error] = "Bad file descriptor",
	[is_dir_error] = "Is a directory",
	[ambig_redirect] = "Ambiguous redirect",
	[error_ronly] = "Variable is read-only",
	[error_inv_format] = "Invalid format",
	[too_many_arguments] = "Too many arguments given",
	[too_few_arguments] = "Too few arguments given",
	[invalid_option] = "invalid option",
	[var_not_set] = "Variable not set",
	[restore_fd_fail] = "Failed to restore fd",
	[dup2_fd_fail] = "Failed to redirect fd",
	[exit_shell_code] = "exit code, this should not have been printed",
	[not_a_dir_error] = "Not a directory",
};
#endif
