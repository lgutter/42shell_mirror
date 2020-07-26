/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_hash.spec.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/26 23:41:44 by devan         #+#    #+#                 */
/*   Updated: 2020/07/26 23:41:44 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "builtins.h"
#include "hashtable.h"
#include <unistd.h>

static void redirect_std_err()
{
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
	char		*path = "/usr/bin/ls";
	char		*exec = "ls";
	size_t		ret = 0;

	shell = init_shell(false);
	ret = add_to_hash(shell, path, exec);
	cr_expect_eq(ret, 0);
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
	char		*path1 = "/usr/bin/ls";
	char		*exec1 = "ls";
	char		*path2 = "/usr/bin/cat";
	char		*exec2 = "cat";
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

Test(unit_builtin_hash, add_to_hash_invalid_path)
{
	t_shell		*shell;
	char		*path = "/usr/bin/blabla";
	char		*exec = "ls";
	size_t		ret = 0;
	char		buff[2048];

	redirect_std_err();
	shell = init_shell(false);
	ret = add_to_hash(shell, path, exec);
	cr_expect_eq(ret, 14);
	fflush(stderr);
	sprintf(buff, "Cetushell: hash: %s: Command not found\n", path);
	cr_expect_stderr_eq_str(buff);
	free_hashtable(shell);
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, add_to_hash_invalid_exec)
{
	t_shell		*shell;
	char		*path = "/usr/bin/ls";
	char		*exec = "lkaasdkads";
	size_t		ret = 0;
	char		buff[2048];

	redirect_std_err();
	shell = init_shell(false);
	ret = add_to_hash(shell, path, exec);
	cr_expect_eq(ret, 14);
	fflush(stderr);
	sprintf(buff, "Cetushell: hash: %s: Command not found\n", exec);
	cr_expect_stderr_eq_str(buff);
	free_hashtable(shell);
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, add_to_hash_empty_table_duplicate)
{
	t_shell		*shell;
	char		*path1 = "/usr/bin/ls";
	char		*exec1 = "ls";
	char		*path2 = "/usr/bin/ls";
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
	cr_expect_eq(shell->hash->hl->next, NULL);
	free_hashtable(shell);
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
	ret = find_hashexec(shell->hash, &retpath, exec2);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(retpath, path2);
	free(retpath);
	retpath = NULL;
	ret = find_hashexec(shell->hash, &retpath, exec1);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(retpath, path1);
	free(retpath);
	retpath = NULL;
	ret = find_hashexec(shell->hash, &retpath, "noexec");
	cr_expect_eq(ret, 1);
	cr_expect_null(retpath);
	free_hashtable(shell);
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, hash_insert_empty_list_find_path)
{
	t_shell		*shell;
	char		*argv[3] = {"hash", "ls", NULL};
	size_t		ret = 0;

	shell = init_shell(false);
	ret = builtin_hash(shell,argv);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, "ls");
	cr_expect_str_eq(shell->hash->hl->value, "/usr/bin/ls");
	unsigned long hashindex = create_hash("ls", HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, "ls");
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, "/usr/bin/ls");
	free_hashtable(shell);
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, hash_insert_empty_list_change_path)
{
	t_shell		*shell;
	char		*argv[3] = {"hash", "ls=/bin/ls", NULL};
	size_t		ret = 0;

	shell = init_shell(false);
	ret = builtin_hash(shell,argv);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, "ls");
	cr_expect_str_eq(shell->hash->hl->value, "/bin/ls");
	unsigned long hashindex = create_hash("ls", HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, "ls");
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, "/bin/ls");
	free_hashtable(shell);
	cr_expect_null(shell->hash);
}

Test(unit_builtin_hash, hash_insert_clear_list_find_path)
{
	t_shell		*shell;
	char		*argv[3] = {"hash", "ls", NULL};
	char		*argv2[4] = {"hash", "-r", "stat", NULL};
	size_t		ret = 0;

	shell = init_shell(false);
	ret = builtin_hash(shell,argv);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, "ls");
	cr_expect_str_eq(shell->hash->hl->value, "/usr/bin/ls");
	unsigned long hashindex = create_hash("ls", HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, "ls");
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, "/usr/bin/ls");
	ret = builtin_hash(shell,argv2);
	cr_expect_eq(ret, 0);
	cr_expect_str_eq(shell->hash->hl->key, "stat");
	cr_expect_str_eq(shell->hash->hl->value, "/usr/bin/stat");
	hashindex = create_hash("stat", HT_SIZE);
	cr_expect_str_eq(shell->hash->ht[hashindex]->key, "stat");
	cr_expect_str_eq(shell->hash->ht[hashindex]->value, "/usr/bin/stat");
	cr_expect_null(shell->hash->hl->next);
	free_hashtable(shell);
	cr_expect_null(shell->hash);
}
