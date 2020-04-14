/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer.spec.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/04/06 17:03:13 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"
#include "criterion/criterion.h"

Test(remove_char_middle, normal) {
	t_buff		*buffer;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 4;
	remove_char(buffer);
	cr_expect_str_eq(buffer->buff, "Helo world");
	free(buffer);
}

Test(remove_char_begin, normal) {
	t_buff		*buffer;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 0;
	remove_char(buffer);
	cr_expect_str_eq(buffer->buff, "Hello world");
	free(buffer);
}

Test(remove_char_end, normal) {
	t_buff		*buffer;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 11;
	remove_char(buffer);
	cr_expect_str_eq(buffer->buff, "Hello worl");
	free(buffer);
}

Test(remove_char_multiple, normal) {
	t_buff		*buffer;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 5;
	remove_char(buffer);
	remove_char(buffer);
	remove_char(buffer);
	remove_char(buffer);
	remove_char(buffer);
	cr_expect_str_eq(buffer->buff, " world");
	free(buffer);
}

Test(remove_char_empty_string, normal) {
	t_buff		*buffer;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_bzero(&buffer->buff, 30);
	buffer->len = 11;
	buffer->index = 0;
	remove_char(buffer);
	cr_expect_str_eq(buffer->buff, "");
	free(buffer);
}

Test(insert_char_begin, normal) {
	t_buff		*buffer;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 0;
	insert_char(buffer, '!');
	cr_expect_str_eq(buffer->buff, "!Hello world");
	free(buffer);
}

Test(insert_char_middle, normal) {
	t_buff		*buffer;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 5;
	insert_char(buffer, '!');
	cr_expect_str_eq(buffer->buff, "Hello! world");
	free(buffer);
}

Test(insert_char_end, normal) {
	t_buff		*buffer;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 11;
	insert_char(buffer, '!');
	cr_expect_str_eq(buffer->buff, "Hello world!");
	free(buffer);
}

Test(remove_word_start, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 5;
	buffer->rv_end = 0;
	buffer->rv_start = 5;
		cursor.current.x = 20;
		cursor.max.x = 100;
	remove_word(buffer, &cursor);
	cr_expect_str_eq(buffer->buff, " world");
	free(buffer);
}

Test(remove_word_middle, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 8;
	buffer->rv_end = 3;
	buffer->rv_start = 8;
		cursor.current.x = 20;
		cursor.max.x = 100;
	remove_word(buffer, &cursor);
	cr_expect_str_eq(buffer->buff, "Helrld");
	free(buffer);
}

Test(remove_word_end, normal) {
	t_buff		*buffer;
	t_cursor	cursor;

	buffer = ft_memalloc(sizeof(t_buff));
	cr_assert_neq(buffer, NULL, "Malloc failed!");
	ft_strcpy(buffer->buff, "Hello world");
	buffer->len = 11;
	buffer->index = 10;
	buffer->rv_end = 8;
	buffer->rv_start = 11;
	cursor.current.x = 20;
	cursor.max.x = 100;
	remove_word(buffer, &cursor);
	cr_expect_str_eq(buffer->buff, "Hello wo");
	free(buffer);
}
