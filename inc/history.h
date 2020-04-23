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

struct						s_hist_list
{
	char			*hist_buff;
	size_t			index;
	t_hist_list		*next;
	t_hist_list		*prev;
};

typedef	struct				s_history
{
	t_hist_list			*hist_list;
	size_t				current_index;
	size_t				max_index;
	size_t				real_num_index;
	size_t				file_size;
	char				*hist_path;
	char				*buff_temp;
}							t_history;

int				get_histfile(t_history *hist);
char			**cut_split_history(t_history *hist, char *history, size_t i);
int				initialize_history(t_history *hist);
int				add_remove_update_history(t_history *hist, char *buff);
t_hist_list		*add_history_element(t_hist_list **start, char *buff, size_t i);
void			free_history(t_history *hist);
void			free_hist_list(t_hist_list **start);

/*
** Add history element will add an t_hist_list to the existing list of **start
** or it will create one if *start == NULL. It will copy the string *buff into
** element->hist_buff. This function will returns NULL if allocation fails for
** either t_hist_list struct or the content hist_buff.
**
** arg: **start: a double pointer marking the start of t_hist_list structs.
** arg: *buff: a character array containing a history line
** arg: i: the index that shoudl be given to the new element of t_hist_list.
** return: t_hist_list*: a pointer to the first element of the likenked list.
**			if allocation fails it will return NULL.
*/

/*
** Free hist list will free all the elements of the t_hist_list list pointed by
** **start. It will also free the buffer within the elements.
**
** arg: **start: a double pointer marking the start of t_hist_list structs.
**/

#endif
