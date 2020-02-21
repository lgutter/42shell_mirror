/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   foo_test.spec.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 17:53:23 by lgutter        #+#    #+#                */
/*   Updated: 2020/02/12 17:53:23 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>

int		foo_test(void);

Test(test_suit_one, always_true)
{
	cr_assert_eq(foo_test(), 1);
}
