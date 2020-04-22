/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/10 11:40:38 by devan         #+#    #+#                 */
/*   Updated: 2020/04/10 11:40:38 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# define HISTSIZE 500
# define HISTFILE "/.cetsh_history"
# define HIST_READ_SIZE 5096

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_hist_list	t_hist_list;

struct				s_hist_list
{
	char			*hist_buff;
	size_t			index;
	t_hist_list		*next;
	t_hist_list		*prev;
};

typedef	struct			s_history
{
	t_hist_list			*hist_list;
	size_t				current_index;
	size_t				max_index;
	size_t				real_num_index;
	size_t				file_size;
	char				*hist_path;
	char				*buff_temp;
}						t_history;


void	print_hist_list(t_hist_list **start);
size_t			get_history_size(t_history *hist);
size_t			get_last_index(char	**split);
int				get_hist_path(t_history *hist);

size_t			offset_i(t_history *hist, char *history, size_t i);
void			print_new_history_line(char *path, int oflag, char *buff,
				size_t size);
int				check_history(char **buff);
char			**cut_split_history(t_history *hist, char *history, size_t i);
void			free_dchar_arr(char **string);
int				add_remove_update_history(t_history *hist, char *buff);
char			*read_history(t_history *hist);
void			free_history(t_history *hist);

void			remove_first_element(t_hist_list **start);
int				initialize_history(t_history *hist);
int				create_history_list(t_hist_list **start, char **buff);
t_hist_list		*add_history_element(t_hist_list **start, char *buff, size_t i);
char			*get_hist_str(t_hist_list **start, size_t index);
void			free_hist_list(t_hist_list **start);

#endif
