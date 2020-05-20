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

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cetushell.h"
#include "history.h"
#include "input_control.h"
#include "handle_error.h"
#include "error_str.h"
#include "environment.h"

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

static void	print_history_file(char *path, int oflag, size_t size)
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

Test(add_history_element_unit, invalid_NULL_buffer)
{
	t_hist_list	*list = NULL;
	char		*str1 = NULL;
	size_t		i = 1;
	t_hist_list	*ret;

	ret = add_history_element(&list, str1, i);
	cr_expect_eq(ret, NULL, "expected ret to be NULL, but got %p!", (void *)ret);
}

Test(add_history_element_unit, invalid_NULL_list)
{
	t_hist_list	**list = NULL;
	char		*str1 = "one";
	size_t		i = 1;
	t_hist_list	*ret;

	ret = add_history_element(list, str1, i);
	cr_expect_eq(ret, NULL, "expected ret to be NULL, but got %p!", (void *)ret);
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

Test(cut_split, null_shell_check)
{
	char		**split;

	split = cut_split_history(NULL, "test1", 5);
	cr_expect_null(split);
}

Test(cut_split, empty_history_str_check)
{
	t_history	*hist;
	char		**split;

	hist = (t_history *)ft_memalloc(sizeof(t_history));
	cr_assert_not_null(hist, "MALLOC failed");
	hist->hist_path = NULL;
	hist->max_index = 0;
	hist->current_index = 0;
	t_shell shell;
	memset(&shell, 0, sizeof(t_shell));
	shell.hist = hist;
	split = cut_split_history(&shell, "", 0);
	cr_expect_null(split);
}

Test(cut_split, weird_format_check)
{
	t_history	*hist;
	char		**split;

	hist = (t_history *)ft_memalloc(sizeof(t_history));
	cr_assert_not_null(hist, "MALLOC failed");
	hist->hist_path = NULL;
	hist->max_index = 0;
	hist->current_index = 0;
	t_shell shell;
	memset(&shell, 0, sizeof(t_shell));
	shell.hist = hist;
	split = cut_split_history(&shell, ":0:foo\n:1bar\n", 0);
	cr_assert_not_null(split);
	cr_assert_not_null(split[0]);
	cr_expect_str_eq(":0:foo\n:1bar", split[0]);
}

Test(cut_split, only_newline_check)
{
	t_history	*hist;
	char		**split;

	hist = (t_history *)ft_memalloc(sizeof(t_history));
	cr_assert_not_null(hist, "MALLOC failed");
	hist->hist_path = NULL;
	hist->max_index = 0;
	hist->current_index = 0;
	t_shell shell;
	memset(&shell, 0, sizeof(t_shell));
	shell.hist = hist;
	split = cut_split_history(&shell, "\n", 1);
	cr_assert_not_null(split);
	cr_expect_str_eq(split[0], "");
}

Test(cut_split, null_history_str_check)
{
	t_history	*hist;
	char		**split;

	hist = (t_history *)ft_memalloc(sizeof(t_history));
	cr_assert_not_null(hist, "MALLOC failed");
	hist->hist_path = NULL;
	hist->max_index = 0;
	hist->current_index = 0;
	t_shell shell;
	memset(&shell, 0, sizeof(t_shell));
	shell.hist = hist;
	split = cut_split_history(&shell, NULL, 0);
	cr_expect_null(split);
}

Test(initialize_hist, empty_histfile)
{
	t_history	*hist;
	int			ret;

	ret = 0;
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_empty_histfile");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 0);
	t_shell	shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
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
	t_shell	shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	cr_expect_null(hist->hist_list);
	cr_expect_eq(0, ret);
}

Test(initialize_hist, invalid_NULL_hist)
{
	int			ret;

	ret = 0;
	t_shell	shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = NULL;
	ret = initialize_history(&shell);
	cr_expect_eq(malloc_error, ret);
}

Test(initialize_hist, no_home_env, .init = cr_redirect_stderr)
{
	t_history	*hist;
	int			ret;
	char		buff[1024];
	ret = 0;
	unsetenv("HOME");
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	cr_assert_not_null(hist);
	hist->hist_path = NULL;
	t_shell	shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	fflush(stderr);
	sprintf(buff, "%.1015s: HOME\n", g_error_str[env_not_found]);
	cr_expect_stderr_eq_str(buff);
	cr_expect_null(hist->hist_list);
	cr_expect_eq(env_not_found, ret);
}

Test(initialize_hist, check_format)
{
	t_history	*hist;
	int			ret;
	char		temp[32];
	int			fd;

	ret = 0;
	ft_bzero(temp, 32);
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_check_format");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	fd = open(hist->hist_path, O_CREAT | O_WRONLY , 0644);
	cr_assert_neq(fd, -1);
	ft_dprintf(fd, ":meh:The wheels of the bus go round and round");
	cr_redirect_stderr();
	fflush(stderr);
	t_shell	shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	cr_assert_eq(ret, histfile_format_error);
	cr_assert_stderr_eq_str("Histfile formatted incorrectly\n");
	close(fd);
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
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_check_elements");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 200);
	t_shell	shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	cr_assert_eq(ret, 0, "expected ret of %d, got %d!", 0, ret);
	cr_assert_eq(hist->max_index, 199, "expected max index of %d, got %zu!", 199, hist->max_index);
	cr_assert_eq(hist->real_num_index, 199, "expected real num index of %d, got %zu!", 199, hist->real_num_index);
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
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_single_element");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 1);
	t_shell	shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	remove(hist->hist_path);
	cr_expect_eq(0, ret);
	cr_assert_str_eq(hist->hist_list->hist_buff, ":0:TESTTINGHISTORY0");
	cr_expect_null(hist->hist_list->next);
}

Test(initialize_hist, two_elements_multiline)
{
	t_history	*hist;
	int			ret;
	int			fd_open;


	ret = 0;
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_two_elements_multiline");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	fd_open = open(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_dprintf(fd_open, ":0:TESTING\nHISTORY0\n:1:TESTING\nHISTORY1\n");
	close(fd_open);
	t_shell	shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	remove(hist->hist_path);
	cr_expect_eq(0, ret);
	cr_assert_not_null(hist->hist_list);
	cr_assert_not_null(hist->hist_list->hist_buff);
	cr_expect_str_eq(hist->hist_list->hist_buff, ":0:TESTING\nHISTORY0");
	cr_assert_not_null(hist->hist_list->next);
	hist->hist_list = hist->hist_list->next;
	cr_assert_not_null(hist->hist_list->hist_buff);
	cr_expect_str_eq(hist->hist_list->hist_buff, ":1:TESTING\nHISTORY1");
	cr_expect_null(hist->hist_list->next);
}

Test(initialize_hist, two_elements_tricky_format)
{
	t_history	*hist;
	int			ret;
	int			fd_open;


	ret = 0;
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_two_elements_tricky_format");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	fd_open = open(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_dprintf(fd_open, ":0:TESTING:42:HISTORY0\n:1:TESTING:21:HISTORY1\n");
	close(fd_open);
	t_shell	shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	remove(hist->hist_path);
	cr_expect_eq(0, ret);
	cr_assert_not_null(hist->hist_list);
	cr_assert_not_null(hist->hist_list->hist_buff);
	cr_expect_str_eq(hist->hist_list->hist_buff, ":0:TESTING:42:HISTORY0");
	cr_assert_not_null(hist->hist_list->next);
	hist->hist_list = hist->hist_list->next;
	cr_assert_not_null(hist->hist_list->hist_buff);
	cr_expect_str_eq(hist->hist_list->hist_buff, ":1:TESTING:21:HISTORY1");
	cr_expect_null(hist->hist_list->next);
}

Test(initialize_hist, no_read_acc)
{
	if (getuid() == 0)
		cr_skip_test("Cannot be tested as root!\n");

	t_history	*hist;
	int			ret;
	char		buff[1024];

	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(strdup("/tmp"), "/.test_read_acc");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 1);
	chmod(hist->hist_path, 0222);
	cr_redirect_stderr();
	t_shell	shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	fflush(stderr);
	sprintf(buff, "%s\n", g_error_str[no_read_permission_hist]);
	cr_expect_stderr_eq_str(buff);
	cr_expect_eq(ret, no_read_permission_hist, "expected ret %i, got %i!", no_read_permission_hist, ret);
	remove(hist->hist_path);
}

Test(initialize_hist, no_write_acc)
{
	if (getuid() == 0)
		cr_skip_test("Cannot be tested as root!\n");

	t_history	*hist;
	int			ret;
	char		buff[1024];

	hist = (t_history *)ft_memalloc(sizeof(t_history));
	cr_redirect_stderr();
	hist->hist_path = ft_strjoin(strdup("/tmp"), "/.test_write_acc");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 1);
	chmod(hist->hist_path, 0444);
	t_shell	shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	fflush(stderr);
	sprintf(buff, "%s\n", g_error_str[no_write_permission_hist]);
	cr_expect_stderr_eq_str(buff);
	cr_expect_eq(ret, no_write_permission_hist, "expected ret %i, got %i!", no_write_permission_hist, ret);
}

Test(scroll_hist, invalid_NULL_hist)
{
	t_buff		buffer;
	t_cursor	cursor;
	int			ret;

	ret = scroll_hist(NULL, &buffer, &cursor);
	cr_assert_eq(ret, 1);
}

Test(scroll_hist, invalid_NULL_buffer)
{
	t_history	hist;
	t_cursor	cursor;
	int			ret;

	ret = scroll_hist(&hist, NULL, &cursor);
	cr_assert_eq(ret, 1);
}

Test(scroll_hist, invalid_NULL_cursor)
{
	t_history	hist;
	t_buff		buffer;
	int			ret;

	ret = scroll_hist(&hist, &buffer, NULL);
	cr_assert_eq(ret, 1);
}

Test(scroll_hist, invalid_blank_buffer_cursor_structs)
{
	t_history	hist;
	t_buff		buffer;
	t_cursor	cursor;
	int			ret;

	ft_bzero(&hist, sizeof(t_history));
	ft_bzero(&buffer, sizeof(t_buff));
	ft_bzero(&cursor, sizeof(t_cursor));
	hist.hist_path = ft_strjoin(getenv("HOME"), "/.test_scroll_hist_blank_buff_cursor");
	cr_assert_not_null(hist.hist_path, "MALLOC failed");
	remove(hist.hist_path);
	print_history_file(hist.hist_path, O_CREAT | O_WRONLY | O_TRUNC, 10);
	t_shell		shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = &hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	remove(hist.hist_path);
	cr_assert_eq(hist.max_index, 9);
	cr_assert_eq(hist.real_num_index, 9);
	cr_assert_str_eq(hist.hist_list->hist_buff, ":0:TESTTINGHISTORY0");
	cr_assert_str_eq(hist.hist_list->next->hist_buff, ":1:TESTTINGHISTORY1");
	cr_assert_str_eq(hist.hist_list->next->next->hist_buff, ":2:TESTTINGHISTORY2");
	cr_expect_eq(0, ret);

	ret = scroll_hist(&hist, &buffer, &cursor);
	cr_assert_eq(ret, 1);
}

Test(scroll_hist, invalid_NULL_hist_list)
{
	t_history	hist;
	t_buff		buffer;
	t_cursor	cursor;
	int			ret;

	ft_bzero(&hist, sizeof(t_history));
	ft_bzero(&buffer, sizeof(t_buff));
	ft_bzero(&cursor, sizeof(t_cursor));
	hist.hist_path = ft_strjoin(getenv("HOME"), "/.test_scroll_hist_NULL_hist_list");
	cr_assert_not_null(hist.hist_path, "MALLOC failed");
	remove(hist.hist_path);
	print_history_file(hist.hist_path, O_CREAT | O_WRONLY | O_TRUNC, 10);
	t_shell		shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = &hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	remove(hist.hist_path);
	cr_expect_eq(hist.max_index, 9);
	cr_expect_eq(hist.real_num_index, 9);
	cr_expect_eq(0, ret);
	hist.hist_list = NULL;

	ret = scroll_hist(&hist, &buffer, &cursor);
	cr_assert_eq(ret, 1);
}

Test(scroll_hist, valid_buffer_state_input)
{
	t_history	hist;
	t_buff		buffer;
	t_cursor	cursor;
	int			ret;

	ret = 0;
	hist.hist_path = ft_strjoin(getenv("HOME"), "/.test_scroll_hist_valid_buffer_state_input");
	cr_expect_not_null(hist.hist_path, "MALLOC failed");
	remove(hist.hist_path);
	print_history_file(hist.hist_path, O_CREAT | O_WRONLY | O_TRUNC, 20);
	t_shell		shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = &hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	remove(hist.hist_path);
	cr_expect_eq(hist.max_index, 19);
	cr_expect_eq(hist.real_num_index, 19);
	cr_expect_str_eq(hist.hist_list->hist_buff, ":0:TESTTINGHISTORY0");
	cr_expect_str_eq(hist.hist_list->next->hist_buff, ":1:TESTTINGHISTORY1");
	cr_expect_str_eq(hist.hist_list->next->next->hist_buff, ":2:TESTTINGHISTORY2");
	cr_expect_eq(0, ret);

	ft_bzero(&buffer, sizeof(t_buff));
	ft_bzero(&cursor, sizeof(t_cursor));

	buffer.state = INPUT_STATE;
	hist.buff_temp = ft_strdup("temp");
	buffer.buff = ft_strdup("buffer");
	buffer.buff_len = 6;
	buffer.prompt_len = 10;
	cr_expect_not_null(hist.buff_temp);
	cr_expect_not_null(buffer.buff);
	ret = scroll_hist(&hist, &buffer, &cursor);
	cr_assert_eq(ret, 0);

}

Test(scroll_hist, up_down_test)
{
	t_history	hist;
	t_buff		buffer;
	t_cursor	cursor;
	int			ret;

	ret = 0;
	hist.hist_path = ft_strjoin(getenv("HOME"), "/.test_up_down");
	cr_expect_not_null(hist.hist_path, "MALLOC failed");
	remove(hist.hist_path);
	print_history_file(hist.hist_path, O_CREAT | O_WRONLY | O_TRUNC, 200);
	t_shell		shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = &hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	remove(hist.hist_path);
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
	ret = scroll_hist(&hist, &buffer, &cursor);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(buffer.buff, "TESTTINGHISTORY199");
	hist.current_index--;
	ret = scroll_hist(&hist, &buffer, &cursor);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(buffer.buff, "TESTTINGHISTORY198");
	hist.current_index++;
	ret = scroll_hist(&hist, &buffer, &cursor);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(buffer.buff, "TESTTINGHISTORY199");
	hist.current_index++;
	ret = scroll_hist(&hist, &buffer, &cursor);
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
	hist.hist_path = ft_strjoin(getenv("HOME"), "/.test_whole_list");
	cr_expect_not_null(hist.hist_path, "MALLOC failed");
	remove(hist.hist_path);
	print_history_file(hist.hist_path, O_CREAT | O_WRONLY | O_TRUNC, 200);
	t_shell		shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = &hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	remove(hist.hist_path);
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
		ret = scroll_hist(&hist, &buffer, &cursor);
		cr_assert_eq(ret, 0);
		i++;
	}
	cr_assert_str_eq(buffer.buff, "TESTTINGHISTORY0");
	while (i  > 0)
	{
		hist.current_index++;
		ret = scroll_hist(&hist, &buffer, &cursor);
		cr_assert_eq(ret, 0);
		i--;

	}
	cr_assert_str_eq(buffer.buff, "temp");
}

Test(add_remove_update_hist, invalid_NULL_hist)
{
	int ret;

	ret = update_history(NULL, NULL, "foo");
	cr_expect_eq(ret, 0);
}

Test(add_remove_update_hist, invalid_NULL_buffer)
{
	t_history hist;
	int ret;

	ft_bzero(&hist, sizeof(t_history));
	ret = update_history(&hist, NULL, NULL);
	cr_expect_eq(ret, 0);
}

Test(add_remove_update_hist, invalid_empty_buffer)
{
	t_history hist;
	int ret;

	ft_bzero(&hist, sizeof(t_history));
	ret = update_history(&hist, NULL, "");
	cr_expect_eq(ret, 0);
}

Test(add_remove_update_hist, invalid_NULL_hist_list)
{
	t_history	hist;
	t_buff		buffer;
	t_cursor	cursor;
	int			ret;

	ft_bzero(&hist, sizeof(t_history));
	ft_bzero(&buffer, sizeof(t_buff));
	ft_bzero(&cursor, sizeof(t_cursor));
	hist.hist_path = ft_strjoin(getenv("HOME"), "/.test_add_remove_update_hist_NULL_hist_list");
	cr_assert_not_null(hist.hist_path, "MALLOC failed");
	remove(hist.hist_path);
	print_history_file(hist.hist_path, O_CREAT | O_WRONLY | O_TRUNC, 10);
	t_shell		shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = &hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	remove(hist.hist_path);
	cr_expect_eq(hist.max_index, 9);
	cr_expect_eq(hist.real_num_index, 9);
	cr_expect_eq(0, ret);
	hist.hist_list = NULL;
	ret = update_history(&hist, NULL, "foobar");
	cr_expect_eq(ret, 0);
	cr_assert_not_null(hist.hist_list);
	cr_expect_str_eq(hist.hist_list->hist_buff, ":9:foobar");
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
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_empty_hist");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 0);
	t_shell		shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	cr_expect_eq(0, ret);
	ret = update_history(hist, NULL, "testing add_remove_update_hist");
	cr_expect_eq(0, ret);
	cr_assert_str_eq(hist->hist_list->hist_buff, ":0:testing add_remove_update_hist");
	int fd = open(hist->hist_path, O_RDONLY, 0644);
	cr_expect_neq(fd, -1);
	ret = 1;
	i = 0;
	while (ret > 0)
	{
		ret = read(fd, &temp[i], 1);
		i++;
	}
	cr_expect_neq(ret, -1);
	cr_assert_str_eq(temp, ":0:testing add_remove_update_hist\n");
	ret = update_history(hist, NULL, NULL);
	cr_expect_eq(0, ret);
	cr_assert_str_eq(hist->hist_list->hist_buff, ":0:testing add_remove_update_hist");

	hist->hist_list = NULL;
	ret = update_history(hist, NULL, "Hist list Null test");
	cr_expect_eq(0, ret);
	remove(hist->hist_path);
}

Test(add_remove_update_hist, normal_small_size)
{
	t_history	*hist;
	int			ret;
	char		temp[64];
	int			i;

	ret = 0;
	i = 0;
	ft_bzero(temp, 64);
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_small_size");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 200);
	t_shell		shell;
	ft_bzero(&shell, sizeof(t_shell));
	shell.hist = hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	cr_expect_eq(0, ret);
	ret = update_history(hist, NULL, "testing add_remove_update_hist");
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
	remove(hist->hist_path);
}

Test(add_remove_update_hist, normal_larger_size)
{
	t_shell		shell;
	t_history	*hist;
	int			ret;
	char		temp[64];
	int			i;

	ret = 0;
	ft_bzero(&shell, sizeof(t_shell));
	ft_bzero(temp, 64);
	hist = (t_history *)ft_memalloc(sizeof(t_history));
	hist->hist_path = ft_strjoin(getenv("HOME"), "/.test_larger_size");
	cr_expect_not_null(hist->hist_path, "MALLOC failed");
	remove(hist->hist_path);
	print_history_file(hist->hist_path, O_CREAT | O_WRONLY | O_TRUNC, 600);
	shell.hist = hist;
	shell.env = dup_sys_env();
	ret = initialize_history(&shell);
	cr_expect_eq(0, ret);
	cr_assert_str_eq(hist->hist_list->hist_buff, ":100:TESTTINGHISTORY100");
	ret = update_history(hist, NULL, "testing add_remove_update_hist");
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
	remove(hist->hist_path);
}

Test(get_histfile_unit, invalid_NULL_shell)
{
	int ret;

	ret = get_histfile(NULL);
	cr_expect_eq(ret, malloc_error);
}

Test(get_histfile_unit, invalid_no_HOME, .init = cr_redirect_stderr)
{
	t_shell		shell;
	t_history	hist;
	int			ret;
	char		buff[1024];

	ft_bzero(&shell, sizeof(t_shell));
	ft_bzero(&hist, sizeof(t_history));
	shell.hist = &hist;
	shell.env = dup_sys_env();
	ft_unsetenv(shell.env, "HOME", VAR_TYPE);
	ret = get_histfile(&shell);
	cr_expect_eq(ret, env_not_found);
	fflush(stderr);
	sprintf(buff, "%.1015s: HOME\n", g_error_str[env_not_found]);
	cr_expect_stderr_eq_str(buff);
}

Test(get_histfile_unit, valid_from_HOME_normal)
{
	t_shell		shell;
	t_history	hist;
	t_env		env = {"HOME", "/tmp", ENV_VAR, NULL};
	t_env		*temp_env;
	int			ret;

	ft_bzero(&shell, sizeof(t_shell));
	ft_bzero(&hist, sizeof(t_history));
	shell.hist = &hist;
	shell.env = &env;
	ret = get_histfile(&shell);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(hist.hist_path, "/tmp/.cetsh_history");
	cr_assert_not_null(env.next);
	temp_env = env.next;
	cr_expect_str_eq(temp_env->key, "HISTFILE");
	cr_expect_str_eq(temp_env->value, "/tmp/.cetsh_history");
	cr_expect_eq(temp_env->type, SHELL_VAR | RO_VAR);
	cr_expect_null(temp_env->next);
}

Test(free_history_unit, invalid_NULL_hist)
{
	t_history	*hist = NULL;

	free_history(hist);
}

Test(free_history_unit, invalid_NULL_hist_path)
{
	t_history	*hist = (t_history *)ft_memalloc(sizeof(t_history) * 1);
	cr_assert_not_null(hist);

	hist->hist_list = (t_hist_list *)ft_memalloc(sizeof(t_hist_list) * 1);
	cr_expect_not_null(hist->hist_list);
	hist->buff_temp = (char *)ft_memalloc(sizeof(char) * 1);
	cr_expect_not_null(hist->buff_temp);
	free_history(hist);
}

Test(free_history_unit, invalid_NULL_hist_list)
{
	t_history	*hist = (t_history *)ft_memalloc(sizeof(t_history) * 1);
	cr_assert_not_null(hist);

	hist->hist_path = (char *)ft_memalloc(sizeof(char) * 1);
	cr_expect_not_null(hist->hist_path);
	hist->buff_temp = (char *)ft_memalloc(sizeof(char) * 1);
	cr_expect_not_null(hist->buff_temp);
	free_history(hist);
}

Test(free_history_unit, invalid_NULL_buff_temp)
{
	t_history	*hist = (t_history *)ft_memalloc(sizeof(t_history) * 1);
	cr_assert_not_null(hist);

	hist->hist_list = (t_hist_list *)ft_memalloc(sizeof(t_hist_list) * 1);
	cr_expect_not_null(hist->hist_list);
	hist->hist_path = (char *)ft_memalloc(sizeof(char) * 1);
	cr_expect_not_null(hist->hist_path);
	free_history(hist);
}

Test(free_history_unit, valid_free_all)
{
	t_history	*hist = (t_history *)ft_memalloc(sizeof(t_history) * 1);
	cr_assert_not_null(hist);

	hist->hist_list = (t_hist_list *)ft_memalloc(sizeof(t_hist_list) * 1);
	cr_expect_not_null(hist->hist_list);
	hist->hist_path = (char *)ft_memalloc(sizeof(char) * 1);
	cr_expect_not_null(hist->hist_path);
	hist->buff_temp = (char *)ft_memalloc(sizeof(char) * 1);
	cr_expect_not_null(hist->buff_temp);
	free_history(hist);
}

Test(free_hist_list_unit, invalid_NULL_list)
{
	t_hist_list	*list = NULL;

	free_hist_list(&list);
}

Test(free_hist_list_unit, invalid_NULL_list_pointer)
{
	t_hist_list	**list = NULL;

	free_hist_list(list);
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
