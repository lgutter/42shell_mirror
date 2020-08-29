/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_complete_init.spec.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 16:16:20 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/07/03 16:39:29 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>

#include "autocomplete.h"
#include "input_handling.h"

Test(init_complete, to_complete_dir)
{
    t_buff      buffer;
    t_complete  comp;

    buffer.buff = ft_strdup("cd ./to_comp");
    buffer.index = 12;

    initialize_complete(&comp, &buffer);
    cr_expect_str_eq(comp.to_complete, "./to_comp");
    cr_expect_eq(comp.to_complen, 9);
    cr_assert_eq(comp.options, DIRECTORIES, "is %d , must be %d", (int)comp.options, DIRECTORIES);
}

Test(init_complete, to_complete_dir_multi)
{
    t_buff      buffer;
    t_complete  comp;

    buffer.buff = ft_strdup("echo foo;cd ./to_comp");
    buffer.index = 21;

    initialize_complete(&comp, &buffer);
    cr_expect_str_eq(comp.to_complete, "./to_comp");
    cr_expect_eq(comp.to_complen, 9);
    cr_assert_eq(comp.options, DIRECTORIES, "is %d , must be %d", (int)comp.options, DIRECTORIES);
}


Test(init_complete, to_complete_dirfiles)
{
    t_buff      buffer;
    t_complete  comp;

    buffer.buff = ft_strdup("ls .to_comp");
    buffer.index = 11;

    initialize_complete(&comp, &buffer);
    cr_expect_str_eq(comp.to_complete, ".to_comp");
    cr_expect_eq(comp.to_complen, 8);
    cr_assert_eq(comp.options, (DIRECTORIES + FILES), "is %d , must be %d", (int)comp.options, DIRECTORIES);
}

Test(init_complete, to_complete_dirfiles_multi)
{
    t_buff      buffer;
    t_complete  comp;

    buffer.buff = ft_strdup("echo foo;ls .to_comp");
    buffer.index = 20;

    initialize_complete(&comp, &buffer);
    cr_expect_str_eq(comp.to_complete, ".to_comp");
    cr_expect_eq(comp.to_complen, 8);
    cr_expect_eq(comp.options, (DIRECTORIES + FILES));
}


Test(init_complete, to_complete_exec)
{
    t_buff      buffer;
    t_complete  comp;

    buffer.buff = ft_strdup("crazyexecutablewhichisverylong");
    buffer.index = 31;

    initialize_complete(&comp, &buffer);
    cr_expect_str_eq(comp.to_complete, "crazyexecutablewhichisverylong");
    cr_expect_eq(comp.to_complen, 30);
    cr_expect_eq(comp.options, EXECUTABLES + BUILTINS);
}


Test(init_complete, to_complete_exec_multi)
{
    t_buff      buffer;
    t_complete  comp;

    buffer.buff = ft_strdup("echo foo;crazyexecutablewhichisverylong");
    buffer.index = 40;

    initialize_complete(&comp, &buffer);
    cr_expect_str_eq(comp.to_complete, "crazyexecutablewhichisverylong");
    cr_expect_eq(comp.to_complen, 30);
    cr_expect_eq(comp.options, EXECUTABLES + BUILTINS);
}

Test(init_complete, to_complete_dollar)
{
    t_buff      buffer;
    t_complete  comp;

    buffer.buff = ft_strdup("$PAGE");
    buffer.index = 6;

    initialize_complete(&comp, &buffer);
    cr_expect_str_eq(comp.to_complete, "$PAGE");
    cr_expect_eq(comp.to_complen, 5);
    cr_expect_eq(comp.options, VAR_DOLLAR);
}

Test(init_complete, to_complete_dollar_bracket)
{
    t_buff      buffer;
    t_complete  comp;

    buffer.buff = ft_strdup("${PAGE");
    buffer.index = 7;

    initialize_complete(&comp, &buffer);
    cr_expect_str_eq(comp.to_complete, "${PAGE");
    cr_expect_eq(comp.to_complen, 6);
    cr_expect_eq(comp.options, VAR_DBRACK);
}

Test(init_complete, to_complete_exec_spaces)
{
    t_buff      buffer;
    t_complete  comp;

    buffer.buff = ft_strdup("   spaces");
    buffer.index = 10;

    initialize_complete(&comp, &buffer);
    cr_expect_str_eq(comp.to_complete, "spaces");
    cr_expect_eq(comp.to_complen, 6);
    cr_expect_eq(comp.options, EXECUTABLES + BUILTINS, " is %d and must be %d\n",
                    (int)comp.options, EXECUTABLES + BUILTINS);
}

Test(init_complete, null_checks)
{
    t_buff      buffer;
    t_complete  comp;
    size_t      ret;

    buffer.buff = NULL;
    ret = initialize_complete(&comp, &buffer);
    cr_expect_eq(ret, 1);
    buffer.buff = ft_strdup("   spaces");
    buffer.index = 10;
    ret = initialize_complete(NULL, &buffer);
    cr_expect_eq(ret, 1);
    ret = initialize_complete(&comp, NULL);
    cr_expect_eq(ret, 1);
}
