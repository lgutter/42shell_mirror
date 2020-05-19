/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cetushell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:35:25 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/02/10 16:45:21 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CETUSHELL_H
# define CETUSHELL_H
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <term.h>
# include "ft_printf.h"
# include "libft.h"

# define INPUT_BUFF_SIZE 32
# define CUR_BUFF_SIZE 32
# define REALLOC_SIZE 32
# define INPUT_STATE 0
# define RETURN_STATE 1
# define HISTORY_STATE 2

typedef struct			s_buff
{
	char				*buff;
	char				*copy;
	char				*prompt;
	size_t				prompt_len;
	size_t				state;
	size_t				copy_size;
	size_t				buff_size;
	size_t				buff_len;
	size_t				index;
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
}						t_cursor;

typedef struct			s_shell
{
	struct termios		term;
	char				**envi;
	t_cursor			cursor;
	struct winsize		winsize;
	t_buff				*buffer;
	struct s_history	*hist;
	struct s_env		*env;
}						t_shell;

int						free_shell(t_shell *shell, int ret);
void					free_dchar_arr(char **string);
void					configure_terminal(t_shell *shell, int activator);

#endif
