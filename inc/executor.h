/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:36:54 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/08 17:39:26 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "handle_error.h"
# include "parser_structs.h"
# include "environment.h"
# include "job_control.h"
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>

/*
**	contains the required information to execute a command.
**	fields:
**		path:	the absolute path of the executable,
**				or an empty string in case of builtin. can be freed after use.
**		argc:	the amount of argumentd contained in argv.
**		argv:	an array of strings containing the arguments,
**				with argv[0] being the command name. SHOULD NOT BE FREED!
**		envp:	a copy of the environment as an array of strings.
**				can be freed after use.
*/
typedef struct	s_command
{
	char		*path;
	int			argc;
	char		**argv;
	char		**envp;
}				t_command;

/*
**	a linked list containing file descriptors and there original position.
**	fields:
**		fd:		the file descriptor.
**		og_fd:	the original number associated with the descriptor,
**				or -1 if it was not originally associated with a descriptor.
**		next:	a pointer to the next element in the list.
*/
typedef	struct	s_fd_list
{
	int					fd;
	int					og_fd;
	struct s_fd_list	*next;
}				t_fd_list;

/*
**	contains information needed to properly handle redirections.
**	fields:
**		std_fds:	an array of 3 integers used to hold the original fd's
**					for stdin(index 0), stdout (index 1), and stderr(index 2).
**		fd_list:	a linked list containing all fd's that are opened during
**					setup of the redirections, so they can be freed afterwards.
*/
typedef struct	s_redir_info
{
	int					std_fds[3];
	struct s_fd_list	*fd_list;

}				t_redir_info;

/*
**	sets up a file redirection, linking the file specified in io_file
**	to the fd specified by left_fd. It also places any new or replaced fd's
**	in the fd_list in redir_info as needed.
**	args:
**	redir_info:	the redirection info struct containing the fd list.
**	left_fd:	the fd to which we need to link.
**	io_file:	the io_file struct containing the filename to be linked to
**				left_fd, or an fd if it is an fd instead of file.
**	returns:
**	0 on succes.
**	an error code on failure.
*/
int				set_up_io_file(t_redir_info *redir_info, int left_fd,
								t_io_file *io_file);

/*
**	sets up all redirections in the redirect list. It also places any new
**	or replaced fd's in the fd_list in redir_info, and the original stdin,
**	stdout, and stderr in std_fds in redir_info, which it returns upon succes.
**	args:
**	redirrect:	a pointer to the first redirect struct in the list of redirects.
**	returns:
**	a pointer to the redir_info struct containing info about fd's on success.
**	NULL in case of failure.
*/
t_redir_info	*set_up_redirections(t_io_redirect *redirect);
int				reset_redirections(t_redir_info **redir_info);

/*
**	add fd and og_fd to the list of file descriptors.
**	-1 is a valid value for og_fd, specifying that there was no original fd.
**	args:
**		fd:		the file descriptor.
**		og_fd:		the original number associated with the descriptor,
**					or -1 if it was not originally associated with a descriptor.
**		redir_info:	a pointer to the redir_info struct containing the fd list.
**	returns:
**	0 on succes.
**	an error code on failure.
*/
int				add_fd_to_list(int fd, int og_fd, t_redir_info *redir_info);
int				exec_complete_command(t_shell *shell, t_complete_cmd *comp_cmd);
int				exec_pipe_sequence(t_pipe_sequence *pipe_seq, t_shell *shell,
									t_job *job);
int				exec_simple_command(t_simple_cmd *simple_cmd, t_shell *shell);
int				find_executable(t_env *env_list, char **path, char *arg_zero,
					bool print_warnings);
int				execute_command(t_command *command, t_shell *shell);

#endif
