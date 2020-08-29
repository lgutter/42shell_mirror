/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cut_copy.spec.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by               #+#    #+#                 */
/*   Updated: 0003/01/01 00:00:00 by               ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "prompt.h"
#include "input_handling.h"
#include "criterion/criterion.h"

Test(copy, at_start_from_left_to_right) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 4;
	buffer->rv_start = 0;
	buffer->rv_end = 4;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.current.x = 1;
	cursor.current.y = 0;
	cursor.current.x = 2;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_B);
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "Hello");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(copy, at_start_from_right_to_left) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 0;
	buffer->rv_start = 5;
	buffer->rv_end = 0;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.current.x = 1;
	cursor.current.y = 0;
	cursor.current.x = 2;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_B);
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "Hello");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(copy, at_start_length_null) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 4;
	buffer->rv_start = 4;
	buffer->rv_end = 4;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.current.x = 1;
	cursor.current.y = 0;
	cursor.current.x = 2;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_B);;
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(copy, at_end_from_left_to_right) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 10;
	buffer->rv_start = 6;
	buffer->rv_end = 11;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.current.x = 1;
	cursor.current.y = 0;
	cursor.current.x = 2;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_B);
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "world");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(copy, at_end_from_right_to_left) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 6;
	buffer->rv_start = 11;
	buffer->rv_end = 6;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.current.x = 1;
	cursor.current.y = 0;
	cursor.current.x = 2;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_B);
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "world");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(copy, all_from_right_to_left) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 0;
	buffer->rv_start = 11;
	buffer->rv_end = 0;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.current.x = 1;
	cursor.current.y = 0;
	cursor.current.x = 2;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_B);
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "Hello world");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(copy, two_characters_from_right_to_left) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 10;
	buffer->rv_start = 1;
	buffer->rv_end = 2;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.current.x = 1;
	cursor.current.y = 0;
	cursor.current.x = 2;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_B);;
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "el");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(copy, two_character_from_left_to_right) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 10;
	buffer->rv_start = 3;
	buffer->rv_end = 1;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.current.x = 1;
	cursor.current.y = 0;
	cursor.current.x = 2;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_B);;
	cr_expect_str_eq(buffer->buff, "Hello world");
	cr_expect_str_eq(buffer->copy, "el");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(cut, at_start_from_left_to_right) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 4;
	buffer->rv_start = 0;
	buffer->rv_end = 4;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.max.x = 100;
	cursor.current.x = 20;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_X);
	cr_expect_str_eq(buffer->buff, " world");
	cr_expect_str_eq(buffer->copy, "Hello");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(cut, at_start_from_right_to_left) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 0;
	buffer->rv_start = 5;
	buffer->rv_end = 0;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.max.x = 100;
	cursor.current.x = 2;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_X);
	cr_expect_str_eq(buffer->buff, " world");
	cr_expect_str_eq(buffer->copy, "Hello");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(cut, at_start_length_null) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 4;
	buffer->rv_start = 4;
	buffer->rv_end = 4;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.max.x = 100;
	cursor.current.x = 20;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_X);;
	cr_expect_str_eq(buffer->buff, "Hello world");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(cut, at_end_from_left_to_right) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 10;
	buffer->rv_start = 6;
	buffer->rv_end = 10;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.max.x = 100;
	cursor.current.x = 20;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_X);
	cr_expect_str_eq(buffer->buff, "Hello ");
	cr_expect_str_eq(buffer->copy, "world");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(cut, at_end_from_right_to_left) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 6;
	buffer->rv_start = 11;
	buffer->rv_end = 6;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.max.x = 100;
	cursor.current.x = 20;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_X);
	cr_expect_str_eq(buffer->buff, "Hello ");
	cr_expect_str_eq(buffer->copy, "world");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(cut, all_from_right_to_left) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 0;
	buffer->rv_start = 11;
	buffer->rv_end = 0;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.max.x = 100;
	cursor.current.x = 20;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_X);
	cr_expect_str_eq(buffer->buff, "");
	cr_expect_str_eq(buffer->copy, "Hello world");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(cut, all_from_left_to_right) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 10;
	buffer->rv_start = 0;
	buffer->rv_end = 10;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.max.x = 100;
	cursor.current.x = 20;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_X);;
	cr_expect_str_eq(buffer->buff, "");
	cr_expect_str_eq(buffer->copy, "Hello world");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(cut, two_character_right_to_left) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 11;
	buffer->rv_start = 11;
	buffer->rv_end = 9;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.max.x = 100;
	cursor.current.x = 20;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_X);;
	cr_expect_str_eq(buffer->buff, "Hello wor");
	cr_expect_str_eq(buffer->copy, "ld");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}

Test(cut, two_character_left_to_right) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	buffer->buff = ft_memalloc(sizeof(char) * 64);
	buffer->copy = ft_memalloc(sizeof(char) * 64);
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	cr_assert_neq(buffer->buff, NULL, "Malloc failed!");
	cr_assert_neq(buffer->copy, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->buff_len = 11;
	buffer->index = 11;
	buffer->rv_start = 9;
	buffer->rv_end = 10;
	memset(&cursor, 0, sizeof(t_cursor));
	cursor.max.x = 1000;
	cursor.current.x = 20;
	cursor.current.y = 0;
	cut_copy_paste(buffer, &cursor, CNTRL_X);;
	cr_expect_str_eq(buffer->buff, "Hello wor");
	cr_expect_str_eq(buffer->copy, "ld");
	free(buffer->buff);
	free(buffer->copy);
	free(buffer);
}
