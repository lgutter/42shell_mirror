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
#include "input_control.h"
#include <stdio.h>
#include "handle_error.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

static t_hist_list	*init_list_item(char *buff, size_t index, t_hist_list *next)
{
	t_hist_list	*temp = (t_hist_list *)malloc(sizeof(t_hist_list) * 1);
	if (temp != NULL)
	{
		temp->hist_buff = strdup(buff);
		if (temp->hist_buff == NULL)
		{
			free(temp);
			return (NULL);
		}
		temp->index = index;
		temp->next = next;
		temp->prev = NULL;
	}
	return (temp);
}

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

Test(add_history_element_unit, valid_init_empty_list)
{
	t_hist_list	*list = NULL;
	char		*str1 = "one";
	size_t		i = 1;

	add_history_element(&list, str1, i);
	cr_assert_neq(list, NULL);
	cr_expect_eq(list->index, i, "expected index %zu but got %zu!", i, list->index);
	cr_expect_eq(list->prev, NULL);
	cr_assert_neq(list->hist_buff, NULL);
	cr_expect_str_eq(list->hist_buff, str1);
	cr_expect_eq(list->next, NULL);
}

Test(add_history_element_unit, valid_2_elements)
{
	t_hist_list	*list2;
	t_hist_list	*list;
	char		*str1 = "one";
	char		*str2 = "two";
	char		*str3 = "foo";
	size_t		i = 25;
	list2 = init_list_item(str2, 1, NULL);
	cr_assert_neq(NULL, list2, "malloc failed!");
	list = init_list_item(str1, 0, list2);
	cr_assert_neq(NULL, list, "malloc failed!");
	list2->prev = list;

	add_history_element(&list, str3, i);
	list = list2->next;
	cr_assert_neq(list, NULL);
	cr_expect_eq(list->index, i, "expected index %zu but got %zu!", i, list->index);
	cr_expect_eq(list->next, NULL);
	cr_expect_eq(list->prev, list2);
	cr_assert_neq(list->hist_buff, NULL);
	cr_expect_str_eq(list->hist_buff, "foo");
}

Test(initialize_hist, empty_histfile)
{
	t_history	*hist;
	int			ret;

	ret = 0;
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_hist");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 0);
	ret = initialize_history(hist);
	remove(hist->hist_path);
	cr_expect_eq(0, ret);
}

Test(initialize_hist, bad_hist_path)
{
	t_history	*hist;
	int			ret;

	ret = 0;
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strdup("testingthis");
	ret = initialize_history(hist);
	cr_expect_null(hist->hist_list);
	cr_expect_eq(0, ret);
}

Test(initialize_hist, check_elements)
{
	t_history	*hist;
	int			ret;
	int			i;
	char		temp[32];

	i = 0;
	ret = 0;
	ft_bzero(temp, 32);
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_hist");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 200);
	ret = initialize_history(hist);
	cr_assert_eq(hist->max_index, 199);
	cr_assert_eq(hist->real_num_index, 199);
	while(hist->hist_list->next != NULL)
	{
		ft_snprintf(temp, 32, ":%d:TESTTINGHISTORY%d", i, i);
		cr_expect_not_null(temp);
		cr_assert_str_eq(hist->hist_list->hist_buff, temp);
		i++;
		hist->hist_list = hist->hist_list->next;
	}
	cr_expect_eq(0, ret);
}

Test(initialize_hist, single_element)
{
	t_history	*hist;
	int			ret;

	ret = 0;
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_hist");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 1);
	ret = initialize_history(hist);
	cr_expect_eq(0, ret);
	cr_assert_str_eq(hist->hist_list->hist_buff, ":0:TESTTINGHISTORY0");
	cr_expect_null(hist->hist_list->next);
}

// Test(initialize_hist, no_read_acc)
// {
// 	t_history	*hist;
// 	int			ret;

// 	hist = (t_history *)ft_memalloc(sizeof(t_history));
// 	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_hist");
// 	cr_expect_not_null(hist->hist_path, "MALLOC failed");
// 	remove(hist->hist_path);
// 	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 1);
// 	chmod(hist->hist_path, 0222);
// 	ret = initialize_history(hist);
// 	cr_expect_eq(ret, no_read_permission_hist);
// }

// Test(initialize_hist, no_write_acc)
// {
// 	t_history	*hist;
// 	int			ret;

// 	hist = (t_history *)ft_memalloc(sizeof(t_history));
// 	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_hist");
// 	cr_expect_not_null(hist->hist_path, "MALLOC failed");
// 	remove(hist->hist_path);
// 	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 1);
// 	chmod(hist->hist_path, 0444);
// 	ret = initialize_history(hist);
// 	cr_expect_eq(ret, no_write_permission_hist);
// }

Test(scroll_hist, all_null)
{
	t_history	hist;
	t_buff		buffer;
	t_cursor	cursor;
	int			ret;

	ft_bzero(&hist, sizeof(t_history));
	ft_bzero(&buffer, sizeof(t_buff));
	ft_bzero(&cursor, sizeof(t_cursor));

	ret = scroll_hist(&hist, &buffer, &cursor, 'U');
	cr_assert_eq(ret, 1);
}

Test(scroll_hist, up_down_test)
{
	t_history	hist;
	t_buff		buffer;
	t_cursor	cursor;
	int			ret;

	ret = 0;
	hist.hist_path = ft_strjoin(getenv("HOME"), "/.test_hist");
	cr_expect_not_null(hist.hist_path, "MALLOC failed");
	remove(hist.hist_path);
	print_history_file(hist.hist_path, O_CREAT | O_WRONLY | O_TRUNC, 200);
	ret = initialize_history(&hist);
	cr_assert_eq(hist.max_index, 199);
	cr_assert_eq(hist.real_num_index, 199);
	cr_assert_str_eq(hist.hist_list->hist_buff, ":0:TESTTINGHISTORY0");
	cr_assert_str_eq(hist.hist_list->next->hist_buff, ":1:TESTTINGHISTORY1");
	cr_assert_str_eq(hist.hist_list->next->next->hist_buff, ":2:TESTTINGHISTORY2");
	cr_expect_eq(0, ret);

	ft_bzero(&buffer, sizeof(t_buff));
	ft_bzero(&cursor, sizeof(t_cursor));

	buffer.state = HISTORY_STATE;
	hist.buff_temp = ft_strdup("temp");
	buffer.buff = ft_strdup("temp");
	buffer.buff_len = 4;
	buffer.prompt_len = 10;
	cr_expect_not_null(hist.buff_temp);
	cr_expect_not_null(buffer.buff);
	hist.current_index--;
	ret = scroll_hist(&hist, &buffer, &cursor, 'U');
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(buffer.buff, "TESTTINGHISTORY199");
	hist.current_index--;
	ret = scroll_hist(&hist, &buffer, &cursor, 'U');
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(buffer.buff, "TESTTINGHISTORY198");
	hist.current_index++;
	ret = scroll_hist(&hist, &buffer, &cursor, 'D');
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(buffer.buff, "TESTTINGHISTORY199");
	hist.current_index++;
	ret = scroll_hist(&hist, &buffer, &cursor, 'U');
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(buffer.buff, "temp");
}

Test(scroll_hist, whole_list)
{
	t_history	hist;
	t_buff		buffer;
	t_cursor	cursor;
	int			ret;

	ret = 0;
	hist.hist_path = ft_strjoin(getenv("HOME"), "/.test_hist");
	cr_expect_not_null(hist.hist_path, "MALLOC failed");
	remove(hist.hist_path);
	print_history_file(hist.hist_path, O_CREAT | O_WRONLY | O_TRUNC, 200);
	ret = initialize_history(&hist);
	cr_assert_eq(hist.max_index, 199);
	cr_assert_eq(hist.real_num_index, 199);
	cr_assert_str_eq(hist.hist_list->hist_buff, ":0:TESTTINGHISTORY0");
	cr_assert_str_eq(hist.hist_list->next->hist_buff, ":1:TESTTINGHISTORY1");
	cr_assert_str_eq(hist.hist_list->next->next->hist_buff, ":2:TESTTINGHISTORY2");
	cr_expect_eq(0, ret);

	ft_bzero(&buffer, sizeof(t_buff));
	ft_bzero(&cursor, sizeof(t_cursor));

	buffer.state = HISTORY_STATE;
	hist.buff_temp = ft_strdup("temp");
	buffer.buff = ft_strdup("temp");
	cr_expect_not_null(hist.buff_temp);
	cr_expect_not_null(buffer.buff);
	buffer.buff_len = 4;
	buffer.prompt_len = 10;
	int i = 0;
	while (i < 200)
	{
		hist.current_index--;
		ret = scroll_hist(&hist, &buffer, &cursor, 'U');
		cr_assert_eq(ret, 0);
		i++;
	}
	cr_assert_str_eq(buffer.buff, "TESTTINGHISTORY0");
	while (i  > 0)
	{
		hist.current_index++;
		ret = scroll_hist(&hist, &buffer, &cursor, 'D');
		cr_assert_eq(ret, 0);
		i--;

	}
	cr_assert_str_eq(buffer.buff, "temp");
}

Test(add_remove_update_hist, empty_histlist)
{
	t_history	*hist;
	int			ret;
	char		temp[64];
	int			i;

	ret = 0;
	ft_bzero(temp, 64);
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_hist");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 0);
	ret = initialize_history(hist);
	cr_expect_eq(0, ret);
	ret = add_remove_update_history(hist, "testing add_remove_update_hist");
	cr_expect_eq(0, ret);
	cr_assert_str_eq(hist->hist_list->hist_buff, ":0:testing add_remove_update_hist");
	int fd = open(hist->hist_path, O_RDONLY, 0644);
	cr_expect_neq(fd, -1);
	ret = 1;
	i = 0;
	while (ret > 0)
	{
		ret = read(fd, &temp[i], 1);
		cr_expect_neq(ret, -1);
		i++;
	}
	cr_assert_str_eq(temp, ":0:testing add_remove_update_hist\n");
}

Test(add_remove_update_hist, normal_small_size)
{
	t_history	*hist;
	int			ret;
	char		temp[64];
	int			i;

	ret = 0;
	ft_bzero(temp, 64);
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_hist");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 200);
	ret = initialize_history(hist);
	cr_expect_eq(0, ret);
	ret = add_remove_update_history(hist, "testing add_remove_update_hist");
	cr_expect_eq(0, ret);
	ft_bzero(temp, 64);
	while(hist->hist_list->next != NULL)
	{
		ft_snprintf(temp, 64, ":%d:TESTTINGHISTORY%d", i, i);
		cr_expect_not_null(temp);
		cr_assert_str_eq(hist->hist_list->hist_buff, temp);
		i++;
		hist->hist_list = hist->hist_list->next;
	}
	cr_assert_str_eq(hist->hist_list->hist_buff, ":200:testing add_remove_update_hist");
}

Test(add_remove_update_hist, normal_larger_size)
{
	t_history	*hist;
	int			ret;
	char		temp[64];
	int			i;

	ret = 0;
	ft_bzero(temp, 64);
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_hist");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 600);
	ret = initialize_history(hist);
	cr_expect_eq(0, ret);
	cr_assert_str_eq(hist->hist_list->hist_buff, ":100:TESTTINGHISTORY100");
	ret = add_remove_update_history(hist, "testing add_remove_update_hist");
	cr_assert_str_eq(hist->hist_list->hist_buff, ":101:TESTTINGHISTORY101");
	cr_expect_eq(0, ret);
	ft_bzero(temp, 64);
	i = 101;
	while(hist->hist_list->next != NULL)
	{
		ft_snprintf(temp, 64, ":%d:TESTTINGHISTORY%d", i, i);
		cr_expect_not_null(temp);
		cr_assert_str_eq(hist->hist_list->hist_buff, temp);
		i++;
		hist->hist_list = hist->hist_list->next;
	}
	cr_assert_str_eq(hist->hist_list->hist_buff, ":600:testing add_remove_update_hist");
}

Test(free_hist_list_unit, valid_last_of_3_elements)
{
	t_hist_list	*list3;
	t_hist_list	*list2;
	t_hist_list	*list;
	char		*str1 = "one";
	char		*str2 = "twoo";
	char		*str3 = "threee";
	list3 = init_list_item(str3, 2, NULL);
	cr_assert_neq(NULL, list3, "malloc failed!");
	list2 = init_list_item(str2, 1, list3);
	cr_assert_neq(NULL, list2, "malloc failed!");
	list = init_list_item(str1, 0, list2);
	cr_assert_neq(NULL, list, "malloc failed!");
	list2->prev = list;
	list3->prev = list2;

	free_hist_list(&list);
}
