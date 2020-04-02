/* ************************************************************************** */
/*                                                                            */
/*   cetushell - 21 Shell                                 ::::::::            */
/*                                                      :+:    :+:            */
/*   By: dkroeke <dkroeke@student.codam.nl>            +:+                    */
/*       lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*                                                 #+#    #+#                 */
/*   License: GPLv3                                ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"
#include "criterion/criterion.h"

Test(copy_start_left_right, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 4;
	buffer->rv_start = 0;
	buffer->rv_end = 4;
	cursor.current.x = 1;
	cursor.current.x = 2;
	cut_copy_paste(buffer, &cursor, NULL, CNTRL_X);
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "Hello");
	free(buffer->copy);
	free(buffer);
}

Test(copy_start_right_left, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 0;
	buffer->rv_start = 5;
	buffer->rv_end = 0;
	cursor.current.x = 1;
	cursor.current.x = 2;
	cut_copy_paste(buffer, &cursor, NULL, CNTRL_X);
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "Hello");
	free(buffer->copy);
	free(buffer);
}

Test(copy_start_null, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 4;
	buffer->rv_start = 4;
	buffer->rv_end = 4;
	cursor.current.x = 1;
	cursor.current.x = 2;
	cut_copy_paste(buffer, &cursor, NULL, CNTRL_X);;
	cr_expect_str_eq(buffer->buff, "Hello world");
	free(buffer);
}

Test(copy_end_left_right, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 10;
	buffer->rv_start = 6;
	buffer->rv_end = 11;
	cursor.current.x = 1;
	cursor.current.x = 2;
	cut_copy_paste(buffer, &cursor, NULL, CNTRL_X);
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "world");
	free(buffer->copy);
	free(buffer);
}

Test(copy_end_right_left, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 6;
	buffer->rv_start = 11;
	buffer->rv_end = 6;
	cursor.current.x = 1;
	cursor.current.x = 2;
	cut_copy_paste(buffer, &cursor, NULL, CNTRL_X);
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "world");
	free(buffer->copy);
	free(buffer);
}

Test(copy_all_right_left, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 0;
	buffer->rv_start = 11;
	buffer->rv_end = 0;
	cursor.current.x = 1;
	cursor.current.x = 2;
	cut_copy_paste(buffer, &cursor, NULL, CNTRL_X);
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "Hello world");
	free(buffer->copy);
	free(buffer);
}

Test(copy_all_left_right, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 10;
	buffer->rv_start = 0;
	buffer->rv_end = 11;
	cursor.current.x = 1;
	cursor.current.x = 2;
	cut_copy_paste(buffer, &cursor, NULL, CNTRL_X);;
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "Hello world");
	free(buffer->copy);
	free(buffer);
}

Test(cut_start_left_right, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 4;
	buffer->rv_start = 0;
	buffer->rv_end = 4;
	cursor.max.x = 100;
	cursor.current.x = 20;
	cut_copy_paste(buffer, &cursor, CNTRL_LEFT, 0);
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	cr_expect_str_eq(buffer->buff, " world");
	cr_expect_str_eq(buffer->copy, "Hello");
	free(buffer->copy);
	free(buffer);
}

Test(cut_start_right_left, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 0;
	buffer->rv_start = 5;
	buffer->rv_end = 0;
	cursor.max.x = 100;
	cursor.current.x = 2;
	cut_copy_paste(buffer, &cursor, CNTRL_LEFT, 0);
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	cr_expect_str_eq(buffer->buff, " world");
	cr_expect_str_eq(buffer->copy, "Hello");
	free(buffer->copy);
	free(buffer);
}

Test(cut_start_null, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 4;
	buffer->rv_start = 4;
	buffer->rv_end = 4;
	cursor.max.x = 100;
	cursor.current.x = 20;
	cut_copy_paste(buffer, &cursor, CNTRL_LEFT, 0);;
	cr_expect_str_eq(buffer->buff, "Hello world");
	free(buffer);
}

Test(cut_end_left_right, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 10;
	buffer->rv_start = 6;
	buffer->rv_end = 10;
	cursor.max.x = 100;
	cursor.current.x = 20;
	cut_copy_paste(buffer, &cursor, CNTRL_LEFT, 0);
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	cr_expect_str_eq(buffer->buff, "Hello ");
	cr_expect_str_eq(buffer->copy, "world");
	free(buffer->copy);
	free(buffer);
}

Test(cut_end_right_left, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 6;
	buffer->rv_start = 11;
	buffer->rv_end = 6;
	cursor.max.x = 100;
	cursor.current.x = 20;
	cut_copy_paste(buffer, &cursor, CNTRL_LEFT, 0);
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	cr_expect_str_eq(buffer->buff, "Hello ");
	cr_expect_str_eq(buffer->copy, "world");
	free(buffer->copy);
	free(buffer);
}

Test(cut_all_right_left, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 0;
	buffer->rv_start = 11;
	buffer->rv_end = 0;
	cursor.max.x = 100;
	cursor.current.x = 20;
	cut_copy_paste(buffer, &cursor, CNTRL_LEFT, 0);
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	cr_expect_str_eq(buffer->buff, "");
	cr_expect_str_eq(buffer->copy, "Hello world");
	free(buffer->copy);
	free(buffer);
}

Test(cut_all_left_right, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 10;
	buffer->rv_start = 0;
	buffer->rv_end = 10;
	cursor.max.x = 100;
	cursor.current.x = 20;
	cut_copy_paste(buffer, &cursor, CNTRL_LEFT, 0);;
	cr_expect_str_eq(buffer->buff, "");
	cr_expect_str_eq(buffer->copy, "Hello world");
	free(buffer->copy);
	free(buffer);
}

Test(cut_two_char, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 11;
	buffer->rv_start = 11;
	buffer->rv_end = 9;
	cursor.max.x = 100;
	cursor.current.x = 20;
	cut_copy_paste(buffer, &cursor, CNTRL_LEFT, 0);;
	cr_expect_str_eq(buffer->buff, "Hello wor");
	cr_expect_str_eq(buffer->copy, "ld");
	free(buffer->copy);
	free(buffer);
}

Test(cut_two_char_left, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 11;
	buffer->rv_start = 9;
	buffer->rv_end = 10;
	cursor.max.x = 1000;
	cursor.current.x = 20;
	cut_copy_paste(buffer, &cursor, CNTRL_LEFT, 0);;
	cr_expect_str_eq(buffer->buff, "Hello wor");
	cr_expect_str_eq(buffer->copy, "ld");
	free(buffer->copy);
	free(buffer);
}
