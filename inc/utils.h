/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 16:43:48 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/14 16:43:48 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cetushell.h"
# include "parser_structs.h"
# include "stdbool.h"
# ifdef __linux__
#  include <linux/limits.h>
# else
#  include <limits.h>
# endif

/*
** ft_swap_rv requires as input a pointer to a t_buff struct and a string seq.
** This function will swap the highlighted text start and end position to always
** match rv_end < rv_start. The function will take the cursor into account which
** makes it different then normal ft_swap.
**
** arg: *buffer: pointer to struct t_buff defined in cetushell.h
*/
void		ft_swap_rv(t_buff *buffer);

/*
**	will re-allocate and expand the char * pointed to by source with addition.
**	if *source is NULL, it will allocate a new string for addition.
*/
void		ft_strexpand(char **source, const char *addition);

/*
**	will re-allocate and expand the char * pointed to by source with both
**	additions in order.
**	if *source is NULL, it will allocate a new string for the additions.
*/
void		str_expand_triple(char **source, char *add1, char *add2);

/*
**	will allocate a duplicate of the given string, up to length len.
*/
char		*ft_strndup(const char *string, size_t len);

/*
**	will allocate a duplicate of the given string, up to charachter delim.
*/
char		*ft_strcdup(const char *string, char delim);

/*
**	returns the length of string up to charachter delim, or length size,
**	whichever comes first.
*/
size_t		ft_strlenc(const char *string, int delim, size_t size);

/*
**	completes an unterminated quote, backslash, or pipe in word.
**	returns:
**	-1: on failure.
**	 0:	on succes.
*/
int			complete_unterminated(t_shell *shell, char **word);

/*
**	asks the user for more input for the heredoc.
**	arguments:
**		io_here: the io_here struct containing the here_end and target here_doc.
**		shell:	 the shell struct, required for prompt_shell to ask for input.
**	returns:
**		0 on succes;
**		error code in case of error.
*/
int			get_here_doc(t_io_here *io_here, t_shell *shell);

/*
**	duplicates the standard file descriptors for stdin, stdout and stderr,
**	and places them in the array pointed to by old_fds in the following order:
**		index 0: stdin
**		index 1: stdout
**		index 2: stderr
*/
void		std_fd_backup(int old[3]);

/*
**	restores the standard file descriptors for stdin, stdout and stderr,
**	using the array of ints pointed to by old_fds in the following order:
**		index 0: stdin
**		index 1: stdout
**		index 2: stderr
*/
void		std_fd_restore(int old[3]);

/*
**	determines if the given command name is a builtin or not.
**	returns:
**		true: if the name referes to a builtin.
**		false: if the name does not refer to a builtin.
*/
int			is_builtin(char *exec_name);

/*
**	takes a double char array and returns the amount of char * in the array.
*/
size_t		str_arr_len(char **str_array);

/*
**	check if the 3 standard file descriptors (stdin, stdout & stderr) can be
**	read from or written to.
**	returns 0 if all 3 fd's are working as expected, or an error code otherwise.
*/
int			check_fds(t_shell *shell);

/*
**	retrieves the correct exit code from EXIT_CODE or $?.
**	if neither is present in the env/shell variables, returns 0.
*/
int			get_exit_code(t_shell *shell);

size_t		ft_index_nchar(char *string, char c, size_t n);

size_t		ft_countchar(char *string, char c);

/*
** This function will take in a pointer to a string (curr) and a double
** char array (dest) with its size. it will then add or remove paths
** depending on given dest[i] which can be "." ".." or an actual path.
** it will update the string curr or set it so NULL when failing.
** this function will also free the given double char array.
*/
void		follow_links(char **curr, char **dest, size_t cur_size);

/*
** This function will take in a char array Path and will check if the path
** is an executable file. It will return true when the file mentioned by
** path is an executable.
*/
bool		is_executable(char *path);

/*
** This function will take in a char array file and path and will check if
** the path/file is a directory. if file == NULL it will check if path is an
** directory. It will return true when the specified path is a directory.
*/
bool		is_directory(char *file, char *path);

#endif
