/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_list.spec.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/22 16:45:24 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/22 16:45:24 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "history.h"

static void check_list_item(t_hist_list *item, char *buff, size_t index, t_hist_list *next, t_hist_list *prev, char *testname)
{
	cr_assert_neq(item, NULL, "in %s: list item is NULL!", testname);
	cr_expect_eq(item->prev, prev, "in %s: expected prev to be %p, but is %p!", testname, prev, item->prev);
	cr_expect_eq(item->next, next, "in %s: expected next to be %p, but is %p!", testname, next, item->next);
	cr_expect_eq(item->index, index, "in %s: expected index to be %zu, but is %zu!", testname, index, item->index);
	cr_assert_neq(item->hist_buff, NULL, "in %s: hist_buff is NULL!", testname);
	cr_expect_str_eq(item->hist_buff, buff, "in %s: expected hist_buff to be |%s|, but is |%s|", testname, buff, item->hist_buff);
}

static t_hist_list	*init_list_item(char *buff, size_t index, t_hist_list *next)
{
	t_hist_list	*temp = (t_hist_list *)malloc(sizeof(t_hist_list) * 1);
	if (temp != NULL)
	{
		temp->hist_buff = strdup(buff);
		if (temp->hist_buff == NULL)
		{
			free(temp);
			return (NULL);
		}
		temp->index = index;
		temp->next = next;
		temp->prev = NULL;
	}
	return (temp);
}


Test(remove_first_element_unit, valid_2_elements)
{
	t_hist_list	*list2;
	t_hist_list	*list;
	char		*str1 = "one";
	char		*str2 = "two";
	list2 = init_list_item(str2, 1, NULL);
	cr_assert_neq(NULL, list2, "malloc failed!");
	list = init_list_item(str1, 0, list2);
	cr_assert_neq(NULL, list, "malloc failed!");
	list2->prev = list;

	remove_first_element(&list);
	cr_assert_neq(list, NULL);
	cr_expect_eq(list->index, 0, "expected index %zu but got %zu!", 0, list->index);
	cr_expect_eq(list->next, NULL);
	cr_expect_eq(list->prev, NULL);
	cr_assert_neq(list->hist_buff, NULL);
	cr_expect_str_eq(list->hist_buff, str2);
}

Test(remove_first_element_unit, valid_3_elements)
{
	t_hist_list	*list3;
	t_hist_list	*list2;
	t_hist_list	*list;
	t_hist_list	*temp;
	char		*str1 = "one";
	char		*str2 = "two";
	char		*str3 = "three";
	list3 = init_list_item(str3, 2, NULL);
	cr_assert_neq(NULL, list3, "malloc failed!");
	list2 = init_list_item(str2, 1, list3);
	cr_assert_neq(NULL, list2, "malloc failed!");
	list = init_list_item(str1, 0, list2);
	cr_assert_neq(NULL, list, "malloc failed!");
	list2->prev = list;
	list3->prev = list2;

	remove_first_element(&list);
	cr_assert_neq(list, NULL);
	cr_expect_eq(list->index, 0, "expected index %zu but got %zu!", 0, list->index);
	cr_expect_eq(list->prev, NULL);
	cr_assert_neq(list->hist_buff, NULL);
	cr_expect_str_eq(list->hist_buff, str2);
	cr_assert_eq(list->next, list3);
	temp = list;
	list = list->next;
	cr_expect_eq(list->index, 1, "expected index %zu but got %zu!", 1, list->index);
	cr_expect_eq(list->prev, temp);
	cr_expect_eq(list->next, NULL);
	cr_assert_neq(list->hist_buff, NULL);
	cr_expect_str_eq(list->hist_buff, str3);
}

Test(add_history_element_unit, valid_init_empty_list)
{
	t_hist_list	*list = NULL;
	char		*str1 = "one";
	size_t		i = 1;

	add_history_element(&list, str1, i);
	cr_assert_neq(list, NULL);
	cr_expect_eq(list->index, i, "expected index %zu but got %zu!", i, list->index);
	cr_expect_eq(list->prev, NULL);
	cr_assert_neq(list->hist_buff, NULL);
	cr_expect_str_eq(list->hist_buff, str1);
	cr_expect_eq(list->next, NULL);
}

Test(add_history_element_unit, valid_2_elements)
{
	t_hist_list	*list2;
	t_hist_list	*list;
	char		*str1 = "one";
	char		*str2 = "two";
	char		*str3 = "foo";
	size_t		i = 25;
	list2 = init_list_item(str2, 1, NULL);
	cr_assert_neq(NULL, list2, "malloc failed!");
	list = init_list_item(str1, 0, list2);
	cr_assert_neq(NULL, list, "malloc failed!");
	list2->prev = list;

	add_history_element(&list, str3, i);
	list = list2->next;
	cr_assert_neq(list, NULL);
	cr_expect_eq(list->index, i, "expected index %zu but got %zu!", i, list->index);
	cr_expect_eq(list->next, NULL);
	cr_expect_eq(list->prev, list2);
	cr_assert_neq(list->hist_buff, NULL);
	cr_expect_str_eq(list->hist_buff, "foo");
}

Test(create_history_list_unit, valid_single_element)
{
	char **inputs = (char **)malloc(sizeof(char *) * 2);
	inputs[0] = "foobar";
	inputs[1] = NULL;

	t_hist_list	*list = NULL;
	int ret;

	ret = create_history_list(&list, inputs);
	cr_expect_eq(ret, 1, "expected return %i, got %i!", 1, ret);
	check_list_item(list, "foobar", 0, NULL, NULL, "create_history_list_unit, valid_single_element");
}

Test(create_history_list_unit, invalid_no_element)
{
	char **inputs = (char **)malloc(sizeof(char *) * 1);
	inputs[0] = NULL;

	t_hist_list	*list = NULL;
	int ret;

	ret = create_history_list(&list, inputs);
	cr_expect_eq(ret, 0, "expected return %i, got %i!", 0, ret);
}

Test(create_history_list_unit, valid_five_elements)
{
	char **inputs = (char **)malloc(sizeof(char *) * 6);
	inputs[0] = "foobar";
	inputs[1] = "one";
	inputs[2] = "twoo";
	inputs[3] = "threee";
	inputs[4] = "foouur";
	inputs[5] = NULL;

	t_hist_list	*list = NULL;
	t_hist_list	*prev = NULL;
	int ret;

	ret = create_history_list(&list, inputs);
	cr_expect_eq(ret, 5, "expected return %i, got %i!", 5, ret);
	check_list_item(list, "foobar", 0, list->next, prev, "create_history_list_unit, valid_single_element");
	prev = list;
	list = list->next;
	check_list_item(list, "one", 1, list->next, prev, "create_history_list_unit, valid_single_element");
	prev = list;
	list = list->next;
	check_list_item(list, "twoo", 2, list->next, prev, "create_history_list_unit, valid_single_element");
	prev = list;
	list = list->next;
	check_list_item(list, "threee", 3, list->next, prev, "create_history_list_unit, valid_single_element");
	prev = list;
	list = list->next;
	check_list_item(list, "foouur", 4, NULL, prev, "create_history_list_unit, valid_single_element");
}

Test(get_hist_str_unit, valid_last_of_3_elements)
{
	t_hist_list	*list3;
	t_hist_list	*list2;
	t_hist_list	*list;
	char		*str1 = "one";
	char		*str2 = "twoo";
	char		*str3 = ":2:threee";
	char 		*ret;
	list3 = init_list_item(str3, 2, NULL);
	cr_assert_neq(NULL, list3, "malloc failed!");
	list2 = init_list_item(str2, 1, list3);
	cr_assert_neq(NULL, list2, "malloc failed!");
	list = init_list_item(str1, 0, list2);
	cr_assert_neq(NULL, list, "malloc failed!");
	list2->prev = list;
	list3->prev = list2;

	ret = get_hist_str(&list, 2);
	cr_assert_neq(ret, NULL);
	cr_expect_str_eq(ret, "threee");
	free(ret);
}

Test(get_hist_str_unit, valid_only_element)
{
	t_hist_list	*list;
	char		*str1 = ":0:one";
	char 		*ret;
	list = init_list_item(str1, 0, NULL);
	cr_assert_neq(NULL, list, "malloc failed!");

	ret = get_hist_str(&list, 0);
	cr_assert_neq(ret, NULL);
	cr_expect_str_eq(ret, "one");
	free(ret);
}

Test(get_hist_str_unit, invalid_element_with_NULL_hist_buff)
{
	t_hist_list	*list;
	char 		*ret;
	list = init_list_item("foo", 0, NULL);
	free(list->hist_buff);
	list->hist_buff = NULL;
	cr_assert_neq(NULL, list, "malloc failed!");

	ret = get_hist_str(&list, 0);
	cr_assert_eq(ret, NULL);
}

Test(get_hist_str_unit, invalid_no_element)
{
	t_hist_list	*list = NULL;
	char 		*ret;

	ret = get_hist_str(&list, 0);
	cr_assert_eq(ret, NULL);
}


Test(free_hist_list_unit, valid_last_of_3_elements)
{
	t_hist_list	*list3;
	t_hist_list	*list2;
	t_hist_list	*list;
	char		*str1 = "one";
	char		*str2 = "twoo";
	char		*str3 = "threee";
	list3 = init_list_item(str3, 2, NULL);
	cr_assert_neq(NULL, list3, "malloc failed!");
	list2 = init_list_item(str2, 1, list3);
	cr_assert_neq(NULL, list2, "malloc failed!");
	list = init_list_item(str1, 0, list2);
	cr_assert_neq(NULL, list, "malloc failed!");
	list2->prev = list;
	list3->prev = list2;

	free_hist_list(&list);
}
