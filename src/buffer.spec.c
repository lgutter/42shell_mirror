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
