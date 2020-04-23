/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_history.c                                     :+:    :+:            */
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

static char		*read_history(t_history *hist)
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

static size_t	get_last_index(char **split)
{
	size_t		i;
	size_t		index;
	char		numb[32];

	ft_bzero(numb, 32);
	index = 0;
	while (split[index] != NULL)
		index++;
	index--;
	i = ft_atoi(&split[index][1]);
	return (i);
}

static int		check_history(char **buff)
{
	int		i;
	int		j;

	i = 0;
	if (ft_strlen(buff[0]) == 0)
		return (1);
	while (buff[i] != NULL)
	{
		j = 0;
		if (buff[i][j] != ':')
		{
			return (1);
		}
		while (ft_isdigit(buff[i][0]))
			j++;
		if (buff[i][j] != ':')
			return (1);
		i++;
	}
	return (0);
}

static int		create_history_list(t_hist_list **start, char **buff)
{
	int i;

	i = 0;
	while (buff[i] != NULL)
	{
		*start = add_history_element(start, buff[i], i);
		if (*start == NULL)
			return (0);
		i++;
	}
	return (i);
}

int				initialize_history(t_history *hist)
{
	char	*cut;
	char	**split;
	int		ret;

	hist->hist_list = NULL;
	if (hist == NULL)
		return (1);
	ret = get_histfile(hist);
	if (ret == 0)
	{
		cut = read_history(hist);
		split = cut_split_history(hist, cut, hist->file_size);
		free(cut);
		ret = check_history(split);
		if (ret != 0)
			return (ret);
		hist->real_num_index = get_last_index(split);
		ret = create_history_list(&hist->hist_list, split);
		free_dchar_arr(split);
	}
	return (ret);
}
