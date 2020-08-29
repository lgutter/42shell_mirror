/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cetushell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:35:25 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/07/08 17:34:16 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CETUSHELL_H
# define CETUSHELL_H
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <term.h>
# include <stdbool.h>
# include "ft_printf.h"

# define INP_BUFF_SIZE 32
# define CUR_BUFF_SIZE 32
# define REALLOC_SIZE 32
# define INPUT_STATE 0
# define RETURN_STATE 1
# define HISTORY_STATE 2

typedef struct			s_buff
{
	char				*buff;
	char				*read_buff;
	char				*copy;
	char				*prompt;
	size_t				prompt_len;
	size_t				state;
	size_t				copy_size;
	size_t				buff_size;
	size_t				buff_len;
	size_t				index;
	size_t				read_index;
	size_t				rv_start;
	size_t				rv_end;
}						t_buff;

typedef struct			s_point
{
	size_t					x;
	size_t					y;
}						t_point;

typedef struct			s_cursor
{
	t_point				start;
	t_point				current;
	t_point				max;
	char				cur_buff[CUR_BUFF_SIZE];
	size_t				new_line;
	size_t				new_line_x;
	int					direction;
}						t_cursor;

/*
**	a linked list containing file descriptors and there original position.
**	fields:
**		fd:		the file descriptor.
**		og_fd:	the original number associated with the descriptor,
**				or -1 if it was not originally associated with a descriptor.
**		next:	a pointer to the next element in the list.
*/
typedef	struct			s_fd_list
{
	int					fd;
	int					og_fd;
	struct s_fd_list	*next;
}						t_fd_list;

typedef struct			s_shell
{
	bool				interactive;
	pid_t				pid;
	pid_t				pgid;
	struct termios		term;
	t_cursor			cursor;
	struct winsize		winsize;
	t_buff				*buffer;
	struct s_history	*hist;
	struct s_job_cont	*job_control;
	struct s_env		*env;
	struct s_hashtable	*hash;
	t_fd_list			*process_subst_fds;
}						t_shell;

t_shell					*init_shell(bool interactive);
int						free_shell(t_shell *shell, int ret);
void					free_dchar_arr(char **string);
void					configure_terminal(t_shell *shell, int activator);

#endif
