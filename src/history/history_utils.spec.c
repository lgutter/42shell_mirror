/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_utils.spec.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/22 17:52:32 by devan         #+#    #+#                 */
/*   Updated: 2020/04/22 17:52:32 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "history.h"
#include <stdio.h>
#include "handle_error.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

#ifdef HISTSIZE
# undef HISTSIZE
# define HISTSIZE 5
#endif


void	print_history_file(char *path, int oflag, size_t size)
{
	size_t		i;
	int			fd_open;

	i = 0;
	fd_open = open(path, oflag, 0644);
	if (i == 0)
		ft_dprintf(fd_open, "");
	while (i < size)
	{
		ft_dprintf(fd_open, ":%d:TESTTINGHISTORY%d\n", i, i);
		i++;
	}
	close(fd_open);
}

Test(initialize_hist, no_histfile)
{
	t_history	*hist;
	int			ret;

	ret = 0;
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_hist");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	ret = initialize_history(hist);
	cr_expect_eq(0, ret);
	ret = initialize_history(hist);
	cr_expect_eq(0, ret);
	cr_assert_str_eq(hist->hist_list->hist_buff, "");
	free_history(hist);
}

Test(initialize_hist, empty_histfile)
{
	t_history	*hist;
	int			ret;

	ret = 0;
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_hist");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 1);
	ret = initialize_history(hist);
	cr_expect_eq(0, ret);
}
