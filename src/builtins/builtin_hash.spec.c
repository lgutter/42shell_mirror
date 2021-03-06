/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_hash.spec.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/26 23:41:44 by devan         #+#    #+#                 */
/*   Updated: 2020/08/07 16:53:21 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "builtins.h"
#include "hashtable.h"
#include <unistd.h>


static void redirect_std_out()
{
	cr_redirect_stdout();
}

// static void redirect_std_err()
// {
// 	cr_redirect_stderr();
// }

static void redirect_std_errout()
{
	redirect_std_out();
	cr_redirect_stderr();
}

Test(unit_builtin_hash, NULL_creat_hash)
{
	unsigned long	hashindex;
	char			*exec = NULL;
	
	hashindex = create_hash(exec, HT_SIZE);
	cr_expect_eq(hashindex, 0);
	hashindex = create_hash("ls", 0);
	cr_expect_eq(hashindex, 0);
}

Test(unit_builtin_hash, add_to_hash_empty_table_single)
{
	t_shell		*shell;
	char		*path = "/tmp/add_to_hash_empty_table_single/ls";
	char		*exec = "ls";
	size_t		ret = 0;

	mkdir("/tmp/add_to_hash_empty_table_single", 0777);
	creat(path, 07777);
	shell = init_shell(false);
	ft_setenv(shell->env, "PATH", "/tmp/add_to_hash_empty_table_single", VAR_TYPE);
	ret = add_to_hash(shell, path, exec);
	cr_assert_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, exec);
	cr_expect_str_eq(shell->hash->hl->value, path);
	unsigned long hashindex = create_hash(exec, HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, exec);
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, path);
	free_hashtable(shell);
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, add_to_hash_empty_table_double)
{
	t_shell		*shell;
	char		*path1 = "/tmp/add_to_hash_empty_table_double/ls";
	char		*exec1 = "ls";
	char		*path2 = "/tmp/add_to_hash_empty_table_double/cat";
	char		*exec2 = "cat";
	size_t		ret = 0;

	mkdir("/tmp/add_to_hash_empty_table_double/", 0777);
	creat(path1, 07777);
	creat(path2, 07777);
	shell = init_shell(false);
	ft_setenv(shell->env, "PATH", "/tmp/add_to_hash_empty_table_double", VAR_TYPE);
	ret = add_to_hash(shell, path1, exec1);
	cr_assert_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, exec1);
	cr_expect_str_eq(shell->hash->hl->value, path1);
	unsigned long hashindex = create_hash(exec1, HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, exec1);
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, path1);
	ret = add_to_hash(shell, path2, exec2);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->next->key, exec2);
	cr_expect_str_eq(shell->hash->hl->next->value, path2);
	hashindex = create_hash(exec2, HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, exec2);
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, path2);
	free_hashtable(shell);
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, add_to_hash_null_check)
{
	t_shell		*shell;
	char		*path = "/usr/bin/ls";
	char		*exec = "ls";
	size_t		ret = 0;

	shell = init_shell(false);
	ret = add_to_hash(NULL, path, exec);
	cr_expect_eq(ret, 1);
	ret = add_to_hash(shell, NULL, exec);
	cr_expect_eq(ret, 1);
	ret = add_to_hash(shell, path, NULL);
	cr_expect_eq(ret, 1);
	free_hashtable(shell);
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, add_to_hash_empty_table_duplicate)
{
	t_shell		*shell;
	char		*path1 = "/tmp/add_to_hash_empty_table_dupliate/ls";
	char		*exec1 = "ls";
	char		*path2 = "/tmp/add_to_hash_empty_table_dupliate/ls";
	char		*exec2 = "ls";
	size_t		ret = 0;


	shell = init_shell(false);
	mkdir("/tmp/add_to_hash_empty_table_dupliate", 0777);
	creat(path1, 0777);
	ft_setenv(shell->env, "Path", "/tmp/add_to_hash_empty_table_dupliate", VAR_TYPE);
	ret = add_to_hash(shell, path1, exec1);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, exec1);
	cr_expect_str_eq(shell->hash->hl->value, path1);
	unsigned long hashindex = create_hash(exec1, HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, exec1);
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, path1);
	ret = add_to_hash(shell, path2, exec2);
	cr_expect_eq(ret, 0);
	cr_expect_eq(shell->hash->hl->next, NULL);
	free_hashtable(shell);
	remove(path1);
	remove("/tmp/add_to_hash_empty_table_dupliate");
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, add_to_hash_empty_table_duplicate_other_value)
{
	t_shell		*shell;
	char		*path1 = "/usr/bin/ls";
	char		*exec1 = "ls";
	char		*path2 = "/bin/ls";
	char		*exec2 = "ls";
	size_t		ret = 0;


	shell = init_shell(false);
	ret = add_to_hash(shell, path1, exec1);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, exec1);
	cr_expect_str_eq(shell->hash->hl->value, path1);
	unsigned long hashindex = create_hash(exec1, HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, exec1);
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, path1);
	ret = add_to_hash(shell, path2, exec2);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->value, path2);
	cr_expect_eq(shell->hash->hl->next, NULL);
	free_hashtable(shell);
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, test_find_hashexec)
{
	t_shell		*shell;
	char		*path1 = "/usr/bin/ls";
	char		*exec1 = "ls";
	char		*path2 = "/bin/stat";
	char		*exec2 = "stat";
	char		*retpath = NULL;
	size_t		ret = 0;


	shell = init_shell(false);
	ret = add_to_hash(shell, path1, exec1);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, exec1);
	cr_expect_str_eq(shell->hash->hl->value, path1);
	unsigned long hashindex = create_hash(exec1, HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, exec1);
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, path1);
	ret = add_to_hash(shell, path2, exec2);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->next->key, exec2);
	cr_expect_str_eq(shell->hash->hl->next->value, path2);
	find_hash_exec(shell->hash, &retpath, exec2);
	cr_expect_str_eq(retpath, path2);
	free(retpath);
	retpath = NULL;
	find_hash_exec(shell->hash, &retpath, exec1);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(retpath, path1);
	free(retpath);
	retpath = NULL;
	find_hash_exec(shell->hash, &retpath, "noexec");
	cr_expect_null(retpath);
	free_hashtable(shell);
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, hash_insert_empty_list_find_path)
{
	t_shell		*shell;
	char		*argv[3] = {"hash", "ls", NULL};
	char		*path1 = "/tmp/hash_insert_empty_list_find_path/ls";
	char		*exec1 = "ls";
	size_t		ret = 0;


	shell = init_shell(false);
	mkdir("/tmp/hash_insert_empty_list_find_path/", 0777);
	creat(path1, 07777);
	ft_setenv(shell->env, "PATH", "/tmp/hash_insert_empty_list_find_path", VAR_TYPE);
	ret = builtin_hash(shell,argv);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, exec1);
	cr_expect_str_eq(shell->hash->hl->value, path1);
	unsigned long hashindex = create_hash("ls", HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, exec1);
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, path1);
	remove(path1);
	remove("/tmp/hash_insert_empty_list_find_path/");
	free_hashtable(shell);
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, hash_insert_empty_list_change_path)
{
	t_shell		*shell;
	char		*argv[3] = {"hash", "ls=/tmp/hash_insert_empty_list_change_path/ls", NULL};
	size_t		ret = 0;

	shell = init_shell(false);
	mkdir("/tmp/hash_insert_empty_list_change_path/", 0777);
	creat("/tmp/hash_insert_empty_list_change_path/ls", 07777);
	ft_setenv(shell->env, "PATH", "/tmp/hash_insert_empty_list_change_path", VAR_TYPE);
	ret = builtin_hash(shell,argv);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, "ls");
	cr_expect_str_eq(shell->hash->hl->value, "/tmp/hash_insert_empty_list_change_path/ls");
	unsigned long hashindex = create_hash("ls", HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, "ls");
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, "/tmp/hash_insert_empty_list_change_path/ls");
	free_hashtable(shell);
	remove("/tmp/hash_insert_empty_list_change_path/ls");
	remove("/tmp/hash_insert_empty_list_change_path");
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, hash_insert_clear_list_find_path)
{
	t_shell		*shell;
	char		*argv[3] = {"hash", "ls", NULL};
	char		*argv2[4] = {"hash", "-r", "stat", NULL};
	size_t		ret = 0;

	shell = init_shell(false);
	mkdir("/tmp/hash_insert_clear_list_find_path/", 0777);
	creat("/tmp/hash_insert_clear_list_find_path/ls", 07777);
	creat("/tmp/hash_insert_clear_list_find_path/stat", 07777);
	ft_setenv(shell->env, "PATH", "/tmp/hash_insert_clear_list_find_path", VAR_TYPE);
	ret = builtin_hash(shell,argv);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, "ls");
	cr_expect_str_eq(shell->hash->hl->value, "/tmp/hash_insert_clear_list_find_path/ls");
	unsigned long hashindex = create_hash("ls", HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, "ls");
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, "/tmp/hash_insert_clear_list_find_path/ls");
	ret = builtin_hash(shell,argv2);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, "stat");
	cr_expect_str_eq(shell->hash->hl->value, "/tmp/hash_insert_clear_list_find_path/stat");
	hashindex = create_hash("stat", HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, "stat");
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, "/tmp/hash_insert_clear_list_find_path/stat");
	cr_expect_null(shell->hash->hl->next);
	free_hashtable(shell);
	remove("/tmp/hash_insert_clear_list_find_path/ls");
	remove("/tmp/hash_insert_clear_list_find_path/stat");
	remove("/tmp/hash_insert_clear_list_find_path");
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, add_to_hash_empty_table_coll)
{
	t_shell		*shell;
	char		*path1 = "/tmp/add_to_hash_empty_table_coll/more";
	char		*exec1 = "more";
	char		*path2 = "/tmp/add_to_hash_empty_table_coll/gcc-9";
	char		*exec2 = "gcc-9";
	size_t		ret = 0;

	if (HT_SIZE != 512)
		cr_assert_fail("Warning: HT_SIZE is not 512 and will cause create_hash to be different");
	mkdir("/tmp/add_to_hash_empty_table_coll/", 0777);
	creat("/tmp/add_to_hash_empty_table_coll/more", 0777);
	creat("/tmp/add_to_hash_empty_table_coll/gcc-9", 0777);
	shell = init_shell(false);
	ft_setenv(shell->env, "PATH", "/tmp/add_to_hash_empty_table_coll", VAR_TYPE);
	ret = add_to_hash(shell, path1, exec1);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, exec1);
	cr_expect_str_eq(shell->hash->hl->value, path1);
	unsigned long hashindex = create_hash(exec1, HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, exec1);
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, path1);
	ret = add_to_hash(shell, path2, exec2);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->next->key, exec2);
	cr_expect_str_eq(shell->hash->hl->next->value, path2);
	hashindex = create_hash(exec2, HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->next_col->key, exec2);
	cr_expect_str_eq(shell->hash->ht[hashindex]->next_col->value, path2);
	free_hashtable(shell);
	remove(path1);
	remove(path2);
	remove("/tmp/add_to_hash_empty_table_coll");
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, hash_hit_coll_check)
{
	t_shell		*shell;

	if (HT_SIZE != 512)
		cr_assert_fail("Warning: HT_SIZE is not 512 and will cause create_hash to be different");
	mkdir("/tmp/hash_hit_coll_check/", 0777);
	creat("/tmp/hash_hit_coll_check/more", 0777);
	creat("/tmp/hash_hit_coll_check/gcc-9", 0777);
	creat("/tmp/hash_hit_coll_check/ls", 0777);
	shell = init_shell(false);
	ft_setenv(shell->env, "PATH", "/tmp/hash_hit_coll_check", VAR_TYPE);
	set_hash(shell, "ls");
	set_hash(shell, "ls");
	unsigned long hash = create_hash("ls", 512);
	t_hentry *coll = shell->hash->ht[hash];
	while (coll != NULL && ft_strcmp(coll->key, "ls") != 0)
		coll = coll->next_col;
	cr_expect_eq(coll->hit, 2);
	set_hash(shell, "more");
	hash = create_hash("more", 512);
	coll = shell->hash->ht[hash];
	while (coll != NULL && ft_strcmp(coll->key, "more") != 0)
		coll = coll->next_col;
	cr_expect_eq(coll->hit, 1);
	set_hash(shell, "gcc-9");
	hash = create_hash("gcc-9", 512);
	coll = shell->hash->ht[hash];
	while (coll != NULL && ft_strcmp(coll->key, "gcc-9") != 0)
		coll = coll->next_col;
	cr_assert_not_null(coll);
	cr_expect_eq(coll->hit, 1);
	free_hashtable(shell);
	remove("/tmp/hash_hit_coll_check/more");
	remove("/tmp/hash_hit_coll_check/ls");
	remove("/tmp/hash_hit_coll_check/gcc-9");
	remove("/tmp/hash_hit_coll_check");
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, hash_find_exec_check)
{
	t_shell		*shell;
	char		*argv[3] = {"hash", "-i", NULL};
	char		*path;
	size_t		ret = 0;

	if (HT_SIZE != 512)
		cr_assert_fail("Warning: HT_SIZE is not 512 and will cause create_hash to be different");
	mkdir("/tmp/hash_find_exec_check/", 0777);
	creat("/tmp/hash_find_exec_check/ls", 0777);
	creat("/tmp/hash_find_exec_check/gcc-9", 0777);
	shell = init_shell(false);
	ft_setenv(shell->env, "PATH", "/tmp/hash_find_exec_check", VAR_TYPE);
	ret = builtin_hash(shell,argv);
	cr_expect_eq(ret, 0);
	find_hash_exec(shell->hash, &path, "ls");
	cr_expect_str_eq(path, "/tmp/hash_find_exec_check/ls");
	find_hash_exec(shell->hash, &path, "gcc-9");
	cr_expect_str_eq(path, "/tmp/hash_find_exec_check/gcc-9");
	free_hashtable(shell);
	remove("/tmp/hash_find_exec_check/ls");
	remove("/tmp/hash_find_exec_check/gcc-9");
	remove("/tmp/hash_find_exec_check");
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, hash_print, .init = redirect_std_errout)
{
	t_shell		*shell;
	char		*argv[3] = {"hash", "ls", NULL};
	char		*argv1[2] = {"hash", NULL};
	char		*path;
	size_t		ret = 0;

	if (HT_SIZE != 512)
		cr_assert_fail("Warning: HT_SIZE is not 512 and will cause create_hash to be different");
	mkdir("/tmp/hash_print/", 0777);
	creat("/tmp/hash_print/ls", 0777);
	shell = init_shell(false);
	ft_setenv(shell->env, "PATH", "/tmp/hash_print/", VAR_TYPE);
	fflush(stderr);
	ret = builtin_hash(shell, argv1);
	char buf[1024];
	sprintf(buf, "Cetushell: hash: Hashtable is empty\n");
	cr_expect_stderr_eq_str(buf);
	ret = builtin_hash(shell,argv);
	cr_expect_eq(ret, 0);
	set_hash(NULL, "ls");
	set_hash(shell, "ls");
	find_hash_exec(shell->hash, &path, "ls");
	cr_expect_str_eq(path, "/tmp/hash_print/ls");
	ret = builtin_hash(shell, argv1);
	ft_bzero(buf, 1024);
	sprintf(buf, "Hit:\t%-*sPath:\n 1\t%-*s/tmp/hash_print/ls\n", (int)shell->hash->exec_len, "Command:", (int)shell->hash->exec_len, "ls");
	cr_expect_stdout_eq_str(buf);
	free_hashtable(shell);
	remove("/tmp/hash_print/ls");
	remove("/tmp/hash_print");
	cr_expect_null(shell->hash);
}
