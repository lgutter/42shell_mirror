/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cut_split_history.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/23 16:38:00 by devan         #+#    #+#                 */
/*   Updated: 2020/04/23 16:38:00 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "history.h"
#include "handle_error.h"
#include "utils.h"
#include "environment.h"

static size_t	next_hist_line(char *hist, size_t i)
{
	size_t		check;

	check = 0;
	while (hist[i] != '\0')
	{
		if (i == 0)
			i++;
		if (hist[i] == '\n' && hist[i + 1] == ':')
		{
			i++;
			check = i + 1;
			while (ft_isdigit(hist[check]) == 1)
				check++;
			if (hist[check] == ':')
				return (i);
			else if (hist[check] != '\0')
				i = check + 1;
		}
		else if (hist[i] != '\0')
			i++;
	}
	return (i);
}

static size_t	prev_hist_line(char *hist, size_t i)
{
	size_t		check;

	check = 0;
	while (i > 0)
	{
		if (hist[i] == ':')
		{
			check = i - 1;
			while (check > 0 && ft_isdigit(hist[check]) == 1)
				check--;
			if (hist[check] == ':' && (check == 0 || hist[check - 1] == '\n'))
				return (check);
			else if (check > 0)
				i = check - 1;
		}
		else
			i--;
	}
	return (i);
}

static char		**history_split(t_history *hist, char *hist_str, size_t i)
{
	size_t	temp;
	size_t	str_i;
	char	**split;

	str_i = 0;
	split = (char **)ft_memalloc(sizeof(char *) * (hist->max_index + 2));
	if (split == NULL)
		return (handle_error_p(malloc_error, NULL));
	while (hist_str[i] != '\0' && str_i <= hist->max_index)
	{
		temp = next_hist_line(hist_str, i);
		split[str_i] = ft_strndup(&(hist_str[i]), temp - i - 1);
		if (split[str_i] == NULL)
		{
			free_dchar_arr(split);
			return (handle_error_p(malloc_error, NULL));
		}
		i = temp;
		str_i++;
	}
	return (split);
}

static size_t	offset_i(t_history *hist, t_env *env, char *history, size_t i)
{
	size_t	count;
	size_t	histsize;

	histsize = get_histsize(env);
	count = 0;
	while (histsize > count && i > 0)
	{
		i = prev_hist_line(history, i);
		hist->max_index = count;
		count++;
	}
	hist->current_index = hist->max_index + 1;
	return (i);
}

char			**cut_split_history(t_shell *shell, char *history, size_t i)
{
	char		**split;

	if (history == NULL || shell == NULL || shell->hist == NULL)
		return (NULL);
	i = offset_i(shell->hist, shell->env, history, i);
	if (ft_strlen(&(history[i])) == 0)
		return (NULL);
	split = history_split(shell->hist, history, i);
	return (split);
}
