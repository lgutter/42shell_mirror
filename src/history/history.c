/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/10 14:19:16 by devan         #+#    #+#                 */
/*   Updated: 2020/04/10 14:19:16 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "cetushell.h"
#include "environment.h"
#include "input_control.h"

int		add_remove_update_history(t_history *hist, char *buff)
{
	char	*tmp;
	size_t	len;

	tmp = NULL;
	if (buff == NULL || ft_strlen(buff) == 0)
		return (0);
	if (hist->hist_list != NULL)
		hist->real_num_index++;
	len = ft_intlen(hist->real_num_index) + ft_strlen(buff) + 3;
	tmp = (char *)ft_memalloc(sizeof(char) * len + 1);
	if (tmp == NULL)
		return (1);
	ft_snprintf(tmp, len, ":%d:%s", hist->real_num_index, buff);
	if (hist->max_index < HISTSIZE)
		hist->max_index++;
	add_history_element(&hist->hist_list, tmp, hist->max_index);
	if (hist->max_index >= HISTSIZE)
		remove_first_element(&hist->hist_list);
	print_new_history_line(hist->hist_path, O_WRONLY | O_CREAT | O_APPEND,
							tmp, 0);
	hist->current_index = hist->max_index + 1;
	free(hist->buff_temp);
	hist->buff_temp = NULL;
	free(tmp);
	return (0);
}

size_t	scroll_hist(t_history *hist, t_buff *buffer, t_cursor *cursor, char dir)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (dir == 'U')
		hist->current_index--;
	if (dir == 'D')
		hist->current_index++;
	get_temp_hist_buff(buffer, hist);
	remove_buff(buffer, cursor, hist);
	if (hist->current_index == hist->max_index + 1)
		temp = ft_strdup(hist->buff_temp);
	else
		temp = get_hist_str(&hist->hist_list, hist->current_index);
	if (temp == NULL)
		return (1);
	if (ft_strlen(temp) != 0 &&
	insert_word(buffer, cursor, &temp[i], ft_strlen(&temp[i])) != 0)
		return (1);
	free(temp);
	return (0);
}

char	*read_history(t_history *hist)
{
	int		fd_hist;
	int		ret;
	char	*temp;
	size_t	i;

	i = 0;
	ret = 1;
	temp = ft_memalloc(sizeof(char) * (hist->file_size) + 1);
	if (temp == NULL)
		return (NULL);
	fd_hist = open(hist->hist_path, O_RDONLY | O_CREAT, 0664);
	if (fd_hist == -1)
		return (NULL);
	while (ret != 0)
	{
		ret = read(fd_hist, &temp[i], 1);
		if (ret == -1)
			return (NULL);
		i = i + ret;
	}
	if (i == 0)
		return (NULL);
	hist->file_size = i;
	close(fd_hist);
	return (temp);
}

int		initialize_history(t_history *hist)
{
	char	*cut;
	char	**split;

	hist->hist_list = NULL;
	if (get_hist_path(hist) == 1)
		return (3);
	if (access(hist->hist_path, F_OK) == 0)
		if (access(hist->hist_path, R_OK | W_OK) != 0)
			return (4);
	if (get_history_size(hist) == 1)
		return (5);
	cut = read_history(hist);
	if (cut == NULL)
		return (6);
	split = cut_split_history(hist, cut, hist->file_size);
	free(cut);
	if (split == NULL || split[0] == NULL)
		return (7);
	if (check_history(split) == 1)
		return (8);
	hist->real_num_index = get_last_index(split);
	create_history_list(&hist->hist_list, split);
	free_dchar_arr(split);
	return (0);
}
