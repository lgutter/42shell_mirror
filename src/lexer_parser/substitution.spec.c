/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   substitution.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nloomans <nloomans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 0000/00/00 00:00:00 by nloomans      #+#    #+#                 */
/*   Updated: 9999/99/99 99:99:99 by nloomans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <criterion/criterion.h>
#include "substitution.h"

Test(subst_length, flat) {
   cr_expect_eq(subst_length("(ls -al)"), 8);
   cr_expect_eq(subst_length("(ls -al)foo"), 8);
}

Test(subst_length, nested) {
   cr_expect_eq(subst_length("(ls -al $(ls -al) foo)"), 22);
   cr_expect_eq(subst_length("(ls -al $(ls -al) foo)foo"), 22);
}

Test(subst_length, not_finished) {
   cr_expect_eq(subst_length("(ls -al"), -1);
   cr_expect_eq(subst_length("(ls -al $(ls -al)"), -1);
   cr_expect_eq(subst_length("(ls -al $(ls -al) foo"), -1);
}

Test(subst_length, dollarless_open) {
   cr_expect_eq(subst_length("(foo (  )"), 9);
   cr_expect_eq(subst_length("(((()"), 5);
}

Test(subst_length, squote) {
   cr_expect_eq(subst_length("( 'foo )' )"), 11);
   cr_expect_eq(subst_length("( 'foo $(' )"), 12);
}

Test(subst_length, dquote) {
   cr_expect_eq(subst_length("( \"foo )\" )"), 11);
   cr_expect_eq(subst_length("( \"foo $(bar)\" )"), 16);
   cr_expect_eq(subst_length("( \"foo '$(bar)'\" )"), 18);
}

Test(subst_length, backslash) {
   cr_expect_eq(subst_length("( \\'foo )"), 9);
   cr_expect_eq(subst_length("( \\) )"), 6);
   cr_expect_eq(subst_length("( \\$( )"), 7);
   cr_expect_eq(subst_length("( $\\( )"), 7);
}
