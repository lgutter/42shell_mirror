/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_fd_to_list.spec.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/05 14:26:11 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/05 14:26:11 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "executor.h"

Test(add_fd_to_list_unit, valid_add_first_element)
{
	t_redir_info	info = {NULL, NULL};
	int				fd = 42;
	int				og_fd = -1;
	int				ret;
	int				exp_ret = 0;

	ret = add_fd_to_list(fd, og_fd, &info);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
	cr_expect_null(info.std_fds);
	cr_assert_not_null(info.fd_list);
	cr_expect_eq(info.fd_list->fd, fd, "expect fd %i in list item, but got %i!", fd, info.fd_list->fd);
	cr_expect_eq(info.fd_list->og_fd, og_fd, "expect og_fd %i in list item, but got %i!", og_fd, info.fd_list->og_fd);
	cr_expect_null(info.fd_list->next, "was only expecting 1 list element, but next is not null!");
}

Test(add_fd_to_list_unit, valid_add_first_two_elements)
{
	t_redir_info	info = {NULL, NULL};
	int				fd = 42;
	int				og_fd = -1;
	int				ret;
	int				exp_ret = 0;

	ret = add_fd_to_list(fd, og_fd, &info);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
	cr_expect_null(info.std_fds);
	cr_expect_not_null(info.fd_list);
	cr_assert_not_null(info.fd_list);
	cr_expect_eq(info.fd_list->fd, fd, "expect fd %i in list item, but got %i!", fd, info.fd_list->fd);
	cr_expect_eq(info.fd_list->og_fd, og_fd, "expect og_fd %i in list item, but got %i!", og_fd, info.fd_list->og_fd);
	cr_expect_null(info.fd_list->next, "was only expecting 1 list element, but next is not null!");
	ret = add_fd_to_list(fd, og_fd, &info);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
	cr_expect_null(info.std_fds);
	cr_assert_not_null(info.fd_list);
	cr_assert_not_null(info.fd_list->next, "was expecting another list element, but next is null!");
	info.fd_list = info.fd_list->next;
	cr_expect_eq(info.fd_list->fd, fd, "expect fd %i in list item, but got %i!", fd, info.fd_list->fd);
	cr_expect_eq(info.fd_list->og_fd, og_fd, "expect og_fd %i in list item, but got %i!", og_fd, info.fd_list->og_fd);
	cr_expect_null(info.fd_list->next, "was not expecting another list element, but next is not null!");
}

Test(add_fd_to_list_unit, invalid_NULL_info_pointer)
{
	int				fd = 42;
	int				og_fd = -1;
	int				ret;
	int				exp_ret = -1;

	ret = add_fd_to_list(fd, og_fd, NULL);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
}
