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

void						print_hist_list(t_hist_list **start);
size_t						get_history_size(t_history *hist);
size_t						get_last_index(char	**split);
int							get_hist_path(t_history *hist);

size_t						offset_i(t_history *hist, char *history, size_t i);
void						print_new_history_line(char *path, int oflag,
												char *buff, size_t size);
int							check_history(char **buff);
char						**cut_split_history(t_history *hist,
												char *history, size_t i);
void						free_dchar_arr(char **string);
int							add_remove_update_history(t_history *hist,
													char *buff);
char						*read_history(t_history *hist);
void						free_history(t_history *hist);

int							initialize_history(t_history *hist);

/*
** This function will remove the first element of the t_hist_list linked list.
** The input will be a pointer to the struct marking the start of the list.
** This function does not check if *start is null and assumes there is always
** a list since this funtion is only called when there is one. The function
** moves the pointer to *start to the next element and will free the previous
** one.
**
** arg: **start: a double pointer marking the start of t_hist_list structs.
*/
void						remove_first_element(t_hist_list **start);

/*
** Create_history_list will create a linked list of t_hist_list struct with as
** many elements as the buff[n] has. it allocatate memory for the t_hist_list
** elements and will assign a pointer to the next and previous linked list
** elements if present. it will then copy the content of buff[n] into the
** t_hist_list struct.
**
** arg: **start: a double pointer marking the start of t_hist_list structs.
** arg **buff: duble char array containing history lines.
** return: int: Succes(0) or failure(0) when failed to allocate for t_hist_list
** 			 or element->hist_buff.
*/
int							create_history_list(t_hist_list **start,
												char **buff);

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
t_hist_list					*add_history_element(t_hist_list **start,
												char *buff, size_t i);

/*
** Get hist string will take a pointer to the start of a t_hist_list list and
** will search the hist_list element->index for comparison with size_t index.
** When element is found it will return an allocated string with the history
** lines without the index markings (:int:string).
**
** arg: **start: a double pointer marking the start of t_hist_list structs.
** arg: index: the index indicating which element to find.
** return: char*: a string which holds the history line. if allocation fails,
** 				 it will return NULL some for a non existing index and .
*/
char						*get_hist_str(t_hist_list **start, size_t index);

/*
** Free hist list will free all the elements of the t_hist_list list pointed by
** **start. It will also free the buffer within the elements.
**
** arg: **start: a double pointer marking the start of t_hist_list structs.
*/
void						free_hist_list(t_hist_list **start);

#endif
