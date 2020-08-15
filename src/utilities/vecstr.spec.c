/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vecstr.spec.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nloomans <nloomans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 0000/00/00 00:00:00 by nloomans      #+#    #+#                 */
/*   Updated: 9999/99/99 99:99:99 by nloomans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include "vecstr.h"
#include "handle_error.h"

Test(vecstr, new_null) {
    t_vecstr str = new_vecstr(NULL);

    cr_expect_null(str.string);
    cr_expect_eq(str.len, 0);
    cr_expect_eq(str.cap, 0);
}

Test(vecstr, new_empty) {
    t_vecstr str = new_vecstr("");

    cr_expect_str_eq(str.string, "");
    cr_expect_eq(str.len, 0);
    cr_expect_eq(str.cap, 64);

    clear_vecstr(&str);
}

Test(vecstr, new_string) {
    t_vecstr str = new_vecstr("foo");

    cr_expect_str_eq(str.string, "foo");
    cr_expect_eq(str.len, 3);
    cr_expect_eq(str.cap, 64);

    clear_vecstr(&str);
}

Test(vecstr, new_full_string) {
    char input[64];
    snprintf(input, sizeof(input), "%*s", (int)sizeof(input) - 1, "");

    t_vecstr str = new_vecstr(input);

    cr_expect_str_eq(str.string, input);
    cr_expect_eq(str.len, 63);
    cr_expect_eq(str.cap, 64);

    clear_vecstr(&str);
}

Test(vecstr, new_full_plus_one_string) {
    char input[65];
    snprintf(input, sizeof(input), "%*s", (int)sizeof(input) - 1, "");

    t_vecstr str = new_vecstr(input);

    cr_expect_str_eq(str.string, input);
    cr_expect_eq(str.len, 64);
    cr_expect_eq(str.cap, 128);

    clear_vecstr(&str);
}

Test(vecstr, clear_nothing) {
    t_vecstr str = new_vecstr(NULL);

    clear_vecstr(&str);

    cr_expect_null(str.string);
    cr_expect_eq(str.len, 0);
    cr_expect_eq(str.cap, 0);
}

Test(vecstr, clear_something) {
    t_vecstr str = new_vecstr("foo");

    clear_vecstr(&str);

    cr_expect_null(str.string);
    cr_expect_eq(str.len, 0);
    cr_expect_eq(str.cap, 0);
}

Test(vecstr, append_byte_to_nothing) {
    t_vecstr str = new_vecstr(NULL);

    char c = 'X';
    cr_assert_eq(vecstr_add(&str, &c, 1), no_error);

    cr_expect_str_eq(str.string, "X");
    cr_expect_eq(str.len, 1);
    cr_expect_eq(str.cap, 64);

    clear_vecstr(&str);
}

Test(vecstr, append_byte_to_empty) {
    t_vecstr str = new_vecstr("");

    char c = 'X';
    cr_assert_eq(vecstr_add(&str, &c, 1), no_error);

    cr_expect_str_eq(str.string, "X");
    cr_expect_eq(str.len, 1);
    cr_expect_eq(str.cap, 64);

    clear_vecstr(&str);
}

Test(vecstr, append_byte_to_string) {
    t_vecstr str = new_vecstr("foo");

    char c = 'X';
    cr_assert_eq(vecstr_add(&str, &c, 1), no_error);

    cr_expect_str_eq(str.string, "fooX");
    cr_expect_eq(str.len, 4);
    cr_expect_eq(str.cap, 64);

    clear_vecstr(&str);
}

Test(vecstr, append_string_to_nothing) {
    t_vecstr str = new_vecstr(NULL);

    cr_assert_eq(vecstr_add(&str, "foo", 3), no_error);

    cr_expect_str_eq(str.string, "foo");
    cr_expect_eq(str.len, 3);
    cr_expect_eq(str.cap, 64);

    clear_vecstr(&str);
}

Test(vecstr, append_string_to_empty) {
    t_vecstr str = new_vecstr("");

    cr_assert_eq(vecstr_add(&str, "foo", 3), no_error);

    cr_expect_str_eq(str.string, "foo");
    cr_expect_eq(str.len, 3);
    cr_expect_eq(str.cap, 64);

    clear_vecstr(&str);
}

Test(vecstr, append_string_to_string) {
    t_vecstr str = new_vecstr("foo");

    cr_assert_eq(vecstr_add(&str, "bar", 3), no_error);

    cr_expect_str_eq(str.string, "foobar");
    cr_expect_eq(str.len, 6);
    cr_expect_eq(str.cap, 64);

    clear_vecstr(&str);
}

Test(vecstr, append_long_string_to_long_string) {
    char input[101];
    snprintf(input, sizeof(input), "%*s", (int)sizeof(input) - 1, "");
    t_vecstr str = new_vecstr(input);

    cr_assert_eq(vecstr_add(&str, input, (int)sizeof(input) - 1), no_error);

    cr_assert_not_null(str.string);
    cr_expect_eq(strlen(str.string), 200);
    cr_expect_eq(str.len, 200);
    cr_expect_eq(str.cap, 256);

    clear_vecstr(&str);
}

Test(vecstr, append_noop) {
    t_vecstr str = new_vecstr(NULL);

    cr_assert_eq(vecstr_add(NULL, "a", 1), var_not_set);
    cr_assert_eq(vecstr_add(&str, NULL, 1), no_error);
    cr_assert_eq(vecstr_add(&str, "a", 0), no_error);

    cr_expect_null(str.string);
    cr_expect_eq(str.len, 0);
    cr_expect_eq(str.cap, 0);
}
