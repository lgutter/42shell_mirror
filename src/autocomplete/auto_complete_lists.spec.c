/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_complete_lists.spec.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 05:24:17 by devan         #+#    #+#                 */
/*   Updated: 2020/07/09 15:51:12 by devanando     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"
#include "environment.h"
#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>

Test(auto_complete_lists, null_list)
{
    t_complete  comp;
	size_t		ret;

	memset(&comp, 0, sizeof(t_complete));
    comp.list = NULL;
	ret = add_complete_list(&comp, "FIRST");
	cr_expect_eq(ret, 1);
}

Test(auto_complete_lists, empty_list)
{
    t_complete  comp;
	size_t		ret;

	memset(&comp, 0, sizeof(t_complete));
    comp.list = ft_memalloc(sizeof(t_clist));
	ret = add_complete_list(&comp, "FIRST");
	cr_expect_eq(ret, 0);
	cr_expect_eq(comp.list->length, 5);
    cr_expect_str_eq(comp.list->match, "FIRST");
	ret = add_complete_list(&comp, "SECOND");
	cr_expect_eq(ret, 0);
	cr_expect_eq(comp.list->next->length, 6);
	cr_expect_str_eq(comp.list->next->match, "SECOND");
	cr_expect_null(comp.list->next->next);
}

Test(auto_complete_lists, check_duplicate)
{
    t_complete  comp;
	size_t		ret;

	memset(&comp, 0, sizeof(t_complete));
    comp.list = ft_memalloc(sizeof(t_clist));
	ret = add_complete_list(&comp, "FIRST");
	cr_expect_eq(ret, 0);
	cr_expect_eq(comp.list->length, 5);
    cr_expect_str_eq(comp.list->match, "FIRST");
	ret = add_complete_list(&comp, "IS<THIS>ADDED?");
	cr_expect_eq(ret, 0);
	cr_expect_eq(comp.list->next->length, 14);
	cr_expect_str_eq(comp.list->next->match, "IS<THIS>ADDED?");
	ret = add_complete_list(&comp, "IS<THIS>ADDED?");
    cr_expect_eq(ret, 1);
	cr_expect_null(comp.list->next->next);
}

Test(auto_complete_lists, add_builtin_single)
{
    t_complete  comp;
	size_t		ret;

	memset(&comp, 0, sizeof(t_complete));
    comp.list = ft_memalloc(sizeof(t_clist));
	comp.to_complete = ft_strdup("ex");
	comp.to_complen = 2;
	ret = complete_builtin(&comp);
	cr_expect_eq(ret, 0);
	cr_expect_eq(comp.list->length, 4);
    cr_expect_str_eq(comp.list->match, "exit");
	cr_expect_null(comp.list->next);
}

Test(auto_complete_lists, add_builtin_multi)
{
    t_complete  comp;
	size_t		ret;

	memset(&comp, 0, sizeof(t_complete));
    comp.list = ft_memalloc(sizeof(t_clist));
	comp.options |= BUILTINS | EXECUTABLES;
	comp.to_complete = ft_strdup("unse");
	comp.to_complen = 4;
	ret = complete_builtin(&comp);
	cr_expect_eq(ret, 0);
	cr_expect_eq(comp.list->length, 8);
    cr_expect_str_eq(comp.list->match, "unsetenv");
	cr_expect_eq(comp.list->next->length, 5);
    cr_expect_str_eq(comp.list->next->match, "unset");
	cr_expect_eq(comp.list->next->next->length, 10);
    cr_expect_str_eq(comp.list->next->next->match, "unsetshell");
	cr_expect_eq(comp.max_len, 10);
	cr_expect_null(comp.list->next->next->next);
}

Test(auto_complete_lists, add_dollar_single)
{
    t_complete  comp;
	size_t		ret;
	t_env		*env;


	memset(&comp, 0, sizeof(t_complete));
	env = (t_env *)ft_memalloc(sizeof(t_env));
	comp.list = (t_clist *)ft_memalloc(sizeof(t_clist));
	env->key = ft_strdup("TESTSHELL");
	env->type = VAR_TYPE;
	env->next = (t_env *)ft_memalloc(sizeof(t_env));
	env->next->key = ft_strdup("SHELLTEST");
	env->next->type = VAR_TYPE;
	comp.options = VAR_DOLLAR;
	env->next->next = NULL;
	comp.to_complete = ft_strdup("$SHELL");
	comp.to_complen = 6;
	ret = complete_var(env, &comp);
	cr_expect_eq(ret, 0);
    cr_expect_str_eq(comp.list->match, "SHELLTEST");
	cr_expect_str_eq(comp.list->match, "SHELLTEST");
	cr_expect_null(comp.list->next);
}

Test(auto_complete_lists, add_dollar_multi)
{
    t_complete  comp;
	size_t		ret;
	t_env		*env;


	memset(&comp, 0, sizeof(t_complete));
	env = (t_env *)ft_memalloc(sizeof(t_env));
	comp.list = (t_clist *)ft_memalloc(sizeof(t_clist));
	env->key = ft_strdup("TESTSHELL");
	env->type = VAR_TYPE;
	env->next = (t_env *)ft_memalloc(sizeof(t_env));
	env->next->key = ft_strdup("TESTTHIS");
	env->next->type = VAR_TYPE;
	comp.options = VAR_DOLLAR;
	env->next->next = NULL;
	comp.to_complete = ft_strdup("$TEST");
	comp.to_complen = 6;
	ret = complete_var(env, &comp);
	cr_expect_eq(ret, 0);
    cr_expect_str_eq(comp.list->match, "TESTSHELL");
	cr_expect_str_eq(comp.list->next->match, "TESTTHIS");
	cr_expect_null(comp.list->next->next);
}

Test(auto_complete_lists, add_bdollar_single)
{
    t_complete  comp;
	size_t		ret;
	t_env		*env;


	memset(&comp, 0, sizeof(t_complete));
	env = (t_env *)ft_memalloc(sizeof(t_env));
	comp.list = (t_clist *)ft_memalloc(sizeof(t_clist));
	env->key = ft_strdup("TESTSHELL");
	env->type = VAR_TYPE;
	env->next = (t_env *)ft_memalloc(sizeof(t_env));
	env->next->key = ft_strdup("SHELLTEST");
	env->next->type = VAR_TYPE;
	comp.options = VAR_DBRACK;
	env->next->next = NULL;
	comp.to_complete = ft_strdup("${SHELL");
	comp.to_complen = 7;
	ret = complete_var(env, &comp);
	cr_expect_eq(ret, 0);
    cr_expect_str_eq(comp.list->match, "SHELLTEST}");
	cr_expect_null(comp.list->next);
}

Test(auto_complete_lists, add_bdollar_multi)
{
    t_complete  comp;
	size_t		ret;
	t_env		*env;


	memset(&comp, 0, sizeof(t_complete));
	env = (t_env *)ft_memalloc(sizeof(t_env));
	comp.list = (t_clist *)ft_memalloc(sizeof(t_clist));
	env->key = ft_strdup("TESTSHELL");
	env->type = VAR_TYPE;
	env->next = (t_env *)ft_memalloc(sizeof(t_env));
	env->next->key = ft_strdup("TESTTHIS");
	env->next->type = VAR_TYPE;
	comp.options = VAR_DBRACK;
	env->next->next = NULL;
	comp.to_complete = ft_strdup("${TEST");
	comp.to_complen = 7;
	ret = complete_var(env, &comp);
	cr_expect_eq(ret, 0);
    cr_expect_str_eq(comp.list->match, "TESTSHELL}");
	cr_expect_str_eq(comp.list->next->match, "TESTTHIS}");
	cr_expect_null(comp.list->next->next);
}

Test(auto_complete_lists, add_exec_single)
{
    t_complete  comp;
	size_t		ret;
	t_env		*env;


	memset(&comp, 0, sizeof(t_complete));
	env = (t_env *)ft_memalloc(sizeof(t_env));
	comp.list = (t_clist *)ft_memalloc(sizeof(t_clist));
	env->key = ft_strdup("PATH");
	env->value = ft_strdup("foo:/bin/:/usr/bin:/usr/sbin");
	env->type = VAR_TYPE;
	env->next = NULL;

	comp.options = EXECUTABLES;
	comp.to_complete = ft_strdup("chmo");
	comp.to_complen = 4;

	ret = complete_exec(env, &comp);
	cr_expect_eq(ret, 0);
    cr_expect_str_eq(comp.list->match, "chmod");
	cr_expect_null(comp.list->next);
}

Test(auto_complete_lists, add_exec_multi)
{
    t_complete  comp;
	size_t		ret;
	t_env		*env;


	memset(&comp, 0, sizeof(t_complete));
	env = (t_env *)ft_memalloc(sizeof(t_env));
	comp.list = (t_clist *)ft_memalloc(sizeof(t_clist));
	env->key = ft_strdup("PATH");
	env->value = ft_strdup("foo:/bin/:/usr/bin:/usr/sbin");
	env->type = VAR_TYPE;
	env->next = NULL;

	comp.options = EXECUTABLES;
	comp.to_complete = ft_strdup("chm");
	comp.to_complen = 3;

	ret = complete_exec(env, &comp);
	cr_expect_eq(ret, 0);
    cr_expect_str_eq(comp.list->match, "chmod");
	cr_expect_str_eq(comp.list->next->match, "chmem");
	cr_expect_null(comp.list->next->next);
}

Test(auto_complete_lists, add_dir_multi)
{
    t_complete  comp;
	size_t		ret;
	t_env		*env;

	ret = mkdir("/tmp/add_dir_multi", 0777);
	cr_expect_eq(ret, 0);
	ret = mkdir("/tmp/add_dir_multi/dir1", 0777);
	cr_expect_eq(ret, 0);
	ret = mkdir("/tmp/add_dir_multi/dir2", 0777);
	cr_expect_eq(ret, 0);
	ret = open("/tmp/add_dirfiles_multi/dirfiles1", O_CREAT, O_WRONLY, O_APPEND, 0777);
	ft_dprintf(ret, "test");
	close(ret);

	memset(&comp, 0, sizeof(t_complete));
	env = (t_env *)ft_memalloc(sizeof(t_env));
	comp.list = (t_clist *)ft_memalloc(sizeof(t_clist));
	comp.options |= DIRECTORIES;
	comp.to_complete = ft_strdup("/tmp/add_dir_multi/d");
	comp.to_complen = 20;
	ret = complete_files(env, &comp);
	cr_expect_eq(ret, 0);
	if (comp.list->match != NULL && ft_strcmp(comp.list->match, "dir2/") == 0)
	{
    	cr_expect_str_eq(comp.list->match, "dir2/");
		cr_expect_str_eq(comp.list->next->match, "dir1/");
	}
	else
	{
    	cr_expect_str_eq(comp.list->match, "dir1/");
		cr_expect_str_eq(comp.list->next->match, "dir2/");
	}
	cr_expect_null(comp.list->next->next);
	remove("/tmp/add_dir_multi/dir1");
	remove("/tmp/add_dir_multi/dir2");
	remove("/tmp/add_dir_multi");
}

Test(auto_complete_lists, add_dirfiles_multi)
{
    t_complete  comp;
	size_t		ret;
	t_env		*env;

	ret = mkdir("/tmp/add_dirfiles_multi", 0777);
	cr_expect_eq(ret, 0);
	ret = mkdir("/tmp/add_dirfiles_multi/dir1", 0777);
	cr_expect_eq(ret, 0);
	ret = open("/tmp/add_dirfiles_multi/dirfiles1", O_CREAT, O_WRONLY, O_APPEND, 0777);
	ft_dprintf(ret, "test");
	close(ret);

	memset(&comp, 0, sizeof(t_complete));
	env = (t_env *)ft_memalloc(sizeof(t_env));
	comp.list = (t_clist *)ft_memalloc(sizeof(t_clist));
	comp.options |= (DIRECTORIES | FILES);
	comp.to_complete = ft_strdup("/tmp/add_dirfiles_multi/d");
	comp.to_complen = 25;
	ret = complete_files(env, &comp);
	cr_expect_eq(ret, 0);
	if (comp.list->match != NULL && ft_strcmp(comp.list->match, "dirfiles1") == 0)
	{
		cr_expect_str_eq(comp.list->match, "dirfiles1");
		cr_expect_str_eq(comp.list->next->match, "dir1/");
	}
	else
	{
		cr_expect_str_eq(comp.list->match, "dir1/");
		cr_expect_str_eq(comp.list->next->match, "dirfiles1");

	}
	cr_expect_null(comp.list->next->next);
	remove("/tmp/add_dirfiles_multi/dirfiles1");
	remove("/tmp/add_dirfiles_multi/dir1");
	remove("/tmp/add_dirfiles_multi");
}
