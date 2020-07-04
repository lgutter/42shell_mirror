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

    buffer.buff = ft_strdup("cd to_comp");
    buffer.index = 10;

    initialize_complete(&comp, &buffer);
    cr_expect_str_eq(comp.to_complete, "to_comp");
    cr_expect_eq(comp.to_complen, 7);
    cr_expect_eq(comp.options, DIRECTORIES);
}

Test(init_complete, to_complete_dirfiles)
{
    t_buff      buffer;
    t_complete  comp;

    buffer.buff = ft_strdup("ls to_comp");
    buffer.index = 10;

    initialize_complete(&comp, &buffer);
    cr_expect_str_eq(comp.to_complete, "to_comp");
    cr_expect_eq(comp.to_complen, 7);
    cr_expect_eq(comp.options, DIRECTORIES + FILES);
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

Test(init_complete, to_complete_spaces)
{
    t_buff      buffer;
    t_complete  comp;

    buffer.buff = ft_strdup("   spaces");
    buffer.index = 13;

    initialize_complete(&comp, &buffer);
    cr_expect_str_eq(comp.to_complete, "spaces");
    cr_expect_eq(comp.to_complen, 6);
    cr_expect_eq(comp.options, EXECUTABLES + BUILTINS, " is %d and must be %d\n", (int)comp.options, EXECUTABLES + BUILTINS);
}
