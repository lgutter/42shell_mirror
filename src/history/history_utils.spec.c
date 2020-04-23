// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   history_utils.spec.c                               :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: devan <devan@student.codam.nl>               +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2020/04/22 17:52:32 by devan         #+#    #+#                 */
// /*   Updated: 2020/04/22 17:52:32 by devan         ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cetushell.h"
// #include "history.h"
// #include <criterion/criterion.h>
// #include <criterion/redirect.h>
// #include <criterion/assert.h>

// #ifdef HISTSIZE
// # undef HISTSIZE
// # define HISTSIZE 5
// #endif

// #ifdef HISTFILE
// # undef HISTFILE
// # define HISTFILE
// #endif

// Test(split_test, correct_string)
// {
// 	char	**split;
// 	t_history hist = {.file_size = 128,
// 	.current_index = 0, .max_index = 0};
// 	char	correct_hist[128] = ":0:dit is de eerste test\n:1:dit is de tweede\
//  	test\n:2:dit is de derde test\n:3:dit is de vierde test\n:4:dit is de\
// 	 vijfde test\n";

// 	split = cut_split_history(&hist, correct_hist, hist.file_size);
// 	cr_expect_not_null(split, "cut_split_history Failed");
// 	cr_expect_not_null(split[0], "cut_split_history Failed");
// 	cr_assert_str_eq(split[0], ":0:dit is de eerste test");
// 	cr_assert_str_eq(split[1], ":1:dit is de tweede test");
// 	cr_assert_str_eq(split[2], ":2:dit is de derde test");
// 	cr_assert_str_eq(split[3], ":3:dit is de vierde test");
// 	cr_assert_str_eq(split[4], ":4:dit is de vijfde test");
// }

// Test(split_test, NULL_string)
// {
// 	char	**split;
// 	t_history hist = {.file_size = 128,
// 	.current_index = 0, .max_index = 0};

// 	split = cut_split_history(&hist, NULL, hist.file_size);
// 	cr_expect_null(split, "cut_split_history Failed");
// }

// Test(split_test, empty_string)
// {
// 	char	**split;
// 	t_history hist = {.file_size = 128,
// 	.current_index = 0, .max_index = 0};

// 	split = cut_split_history(&hist, "", hist.file_size);
// 	cr_expect_not_null(split, "cut_split_history Failed");
// 	cr_expect_not_null(split[0], "cut_split_history Failed");
// 	cr_assert_str_eq(split[0], "");
// }

// Test(offset_i_test, correct_string)
// {
// 	size_t	i;
// 	char	correct_hist[128] = ":0:dit is de eerste test\n:1:dit is de tweede\
//  	test\n:2:dit is de derde test\n:3:dit is de vierde test\n:4:dit is de\
// 	 vijfde test\n";
// 	t_history hist = {.file_size = 128,
// 	.current_index = 0, .max_index = 0};

// 	i = offset_i(&hist, correct_hist, 128);
// 	cr_assert_eq(i, 0);
// 	cr_assert_eq(hist.current_index, HISTSIZE + 1);
// 	cr_assert_eq(hist.max_index, HISTSIZE);
// }

// Test(init_hist, normal)
// {
// `	t_history	hist;
// 	initialize_history(&hist);
// }
