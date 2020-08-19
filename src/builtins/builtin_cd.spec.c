/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.spec.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/07 22:37:17 by devan         #+#    #+#                 */
/*   Updated: 2020/08/04 16:40:02 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <unistd.h>

#include "builtins.h"
#include "environment.h"
#include "error_str.h"

static void redirect_std_err()
{
	cr_redirect_stderr();
}

static void redirect_std_out()
{
	cr_redirect_stdout();
}

Test(builtin_cd_unit, valid_cd_oldpwd, .init = redirect_std_out)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];
	char		*dir = "/tmp";
#ifdef __linux__
	char		*expected_dir = "/tmp";
#else
	char		*expected_dir = "/private/tmp";
#endif

	ret = ft_setenv(shell->env, "OLDPWD", dir, ENV_VAR);
	cr_assert_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = "-";
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	getcwd(buff, 1024);
	cr_expect_str_eq(buff, expected_dir, "did not change to correct dir! expected %s, got %s!", dir, buff);
	fflush(stdout);
	memset(buff, '\0', 1024);
	sprintf(buff, "%s\n", dir);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_cd_unit, valid_cd_normal)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];
#ifdef __linux__
	char		*expected_dir = "/tmp";
	char		*dir = "/tmp";
#else
	char		*expected_dir = "/private/tmp";
	char		*dir = "/private/tmp";
#endif
	char		olddir[1024];

	getcwd(olddir, 1024);
	ft_setenv(shell->env, "OLDPWD", "foo", ENV_VAR);
	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = dir;
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "OLDPWD", VAR_TYPE), olddir);
	getcwd(buff, 1024);
	cr_expect_str_eq(ft_getenv(shell->env, "PWD", VAR_TYPE), expected_dir);
	cr_expect_str_eq(buff, expected_dir, "did not change to correct dir! expected %s, got %s!", expected_dir, buff);
}

Test(builtin_cd_unit, valid_cd_normal_no_read_perm)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];
	char		*dir = "/tmp/builtin_cd_unit_valid_cd_normal_no_read_perm";
#ifdef __linux__
	char		*expected_dir = "/tmp/builtin_cd_unit_valid_cd_normal_no_read_perm";
#else
	char		*expected_dir = "/private/tmp/builtin_cd_unit_valid_cd_normal_no_read_perm";
#endif
	char		olddir[1024];
	getcwd(olddir, 1024);
	mkdir(dir, 0333);
	ft_setenv(shell->env, "OLDPWD", "foo", ENV_VAR);
	argv = (char **)ft_memalloc(sizeof(char *) * 4);
	argv[0] = "cd";
	argv[1] = "-P";
	argv[2] = dir;
	argv[3] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "OLDPWD", VAR_TYPE), olddir);
	getcwd(buff, 1024);
	cr_expect_str_eq(ft_getenv(shell->env, "PWD", VAR_TYPE), buff);
	cr_expect_str_eq(buff, expected_dir, "did not change to correct dir! expected %s, got %s!", expected_dir, buff);
	remove(dir);
	free(argv);
}
Test(builtin_cd_unit, valid_cd_normal_no_write_perm)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];
	char		*dir = "/tmp/builtin_cd_unit_valid_cd_normal_no_write_perm";
#ifdef __linux__
	char		*expected_dir = "/tmp/builtin_cd_unit_valid_cd_normal_no_write_perm";
#else
	char		*expected_dir = "/private/tmp/builtin_cd_unit_valid_cd_normal_no_write_perm";
#endif
	char		olddir[1024];
	getcwd(olddir, 1024);
	mkdir(dir, 0555);
	ft_setenv(shell->env, "OLDPWD", "foo", ENV_VAR);
	argv = (char **)ft_memalloc(sizeof(char *) * 4);
	argv[0] = "cd";
	argv[1] = "-P";
	argv[2] = dir;
	argv[3] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "OLDPWD", VAR_TYPE), olddir);
	getcwd(buff, 1024);
	cr_expect_str_eq(ft_getenv(shell->env, "PWD", VAR_TYPE), buff);
	cr_expect_str_eq(buff, expected_dir, "did not change to correct dir! expected %s, got %s!", expected_dir, buff);
	remove(dir);
	free(argv);
}

Test(builtin_cd_unit, valid_cd_from_removed_dir)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];
#ifdef __linux__
	char		*dir = "/tmp/tempdirtoremove";
	char		*expected_dir = "/tmp";
#else
	char		*dir = "/private/tmp/tempdirtoremove";
	char		*expected_dir = "/private/tmp";
#endif
	char		olddir[1024];

	remove(dir);
	getcwd(olddir, 1024);
	mkdir(dir, 0755);
	ft_setenv(shell->env, "OLDPWD", "foo", ENV_VAR);
	ft_setenv(shell->env, "PWD", olddir, ENV_VAR);
	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = dir;
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "OLDPWD", VAR_TYPE), olddir);
	getcwd(buff, 1024);
	cr_expect_str_eq(ft_getenv(shell->env, "PWD", VAR_TYPE), buff);
	cr_expect_str_eq(buff, dir, "did not change to correct dir! expected %s, got %s!", dir, buff);
	remove(dir);
	cr_expect_neq(access(dir, F_OK), 0, "dir was not removed as expected!");
	argv[0] = "cd";
	argv[1] = "..";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "OLDPWD", VAR_TYPE), buff);
	getcwd(buff, 1024);
	cr_expect_str_eq(ft_getenv(shell->env, "PWD", VAR_TYPE), buff);
	cr_expect_str_eq(buff, expected_dir, "did not change to correct dir! expected %s, got %s!", expected_dir, buff);
}

Test(builtin_cd_unit, invalid_cd_no_home, .init = redirect_std_err)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];


	ret = ft_unsetenv(shell->env, "HOME", VAR_TYPE);
	ft_unsetenv(shell->env, "HOME", VAR_TYPE);
	cr_assert_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	argv = ft_strsplit_t_s("cd");
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "Cetushell: cd: HOME: %s\n", g_error_str[var_not_set]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_cd_unit, invalid_cd_no_such_file, .init = redirect_std_err)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[4096];

	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = "/tmp/builtin_cd_unit_invalid_cd_no_such_file";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "Cetushell: cd: /tmp/builtin_cd_unit_invalid_cd_no_such_file: %s\n", g_error_str[no_such_file_or_dir]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_cd_unit, not_a_dir, .init = redirect_std_err)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		path[1024] = "/tmp/builtin_cd_unit_not_a_dir";
	char		buff[4096];

	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	creat(path, 0777);
	argv[0] = "cd";
	argv[1] = "/tmp/builtin_cd_unit_not_a_dir";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "Cetushell: cd: /tmp/builtin_cd_unit_not_a_dir: %s\n", g_error_str[not_a_dir_error]);
	remove(path);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_cd_unit, not_a_dir_no_perm, .init = redirect_std_err)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		path[1024] = "/tmp/builtin_cd_unit_not_a_dir_no_perm";
	char		buff[4096];

	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	creat(path, 0000);
	argv[0] = "cd";
	argv[1] = "/tmp/builtin_cd_unit_not_a_dir_no_perm";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "Cetushell: cd: /tmp/builtin_cd_unit_not_a_dir_no_perm: %s\n", g_error_str[not_a_dir_error]);
	remove(path);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_cd_unit, acces_denied_no_perm, .init = redirect_std_err)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		path[1024] = "/tmp/builtin_cd_unit_acces_denied_no_perm";
	char		buff[4096];

	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	mkdir(path, 0000);
	argv[0] = "cd";
	argv[1] = "/tmp/builtin_cd_unit_acces_denied_no_perm";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "Cetushell: cd: /tmp/builtin_cd_unit_acces_denied_no_perm: %s\n", g_error_str[access_denied]);
	remove(path);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_cd_unit, acces_denied_no_exec_perm, .init = redirect_std_err)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		path[1024] = "/tmp/builtin_cd_unit_acces_denied_no_exec_perm";
	char		buff[4096];

	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	mkdir(path, 0666);
	argv[0] = "cd";
	argv[1] = "/tmp/builtin_cd_unit_acces_denied_no_exec_perm";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "Cetushell: cd: /tmp/builtin_cd_unit_acces_denied_no_exec_perm: %s\n", g_error_str[access_denied]);
	remove(path);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_cd_unit, invalid_cd_no_oldpwd, .init = redirect_std_err)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];


	ret = ft_unsetenv(shell->env, "OLDPWD", VAR_TYPE);
	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = "-";
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "Cetushell: cd: OLDPWD: %s\n", g_error_str[var_not_set]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_cd_unit, invalid_cd_many_args)
{
	char	**argv;
	t_shell	*shell = init_shell(false);

	argv = ft_strsplit_t_s("cd one two three");

	int ret = 0;
	cr_redirect_stderr();
	ret = builtin_cd(shell, argv);
	fflush(stderr);
	cr_expect_stderr_eq_str("Cetushell: cd: Too many arguments given\n");
	cr_expect_eq(1, ret, "ret is %d but must be %d", ret, 1);
}

Test(builtin_cd_unit, invalid_NULL_argv)
{
	char	**argv;
	t_shell	*shell = init_shell(false);

	argv = NULL;

	int ret = 0;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(1, ret, "ret is %d but must be %d", ret, 1);
}

Test(builtin_cd_unit, valid_cd_single_link)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];
	char		*dir = "/tmp/valid_cd_link/foo";
#ifdef __linux__
	char		*expected_dir = "/tmp/valid_cd_link/bar";
#else
	char		*expected_dir = "/private/tmp/valid_cd_link/bar";
#endif
	char		olddir[1024];

	getcwd(olddir, 1024);
	mkdir("/tmp/valid_cd_link", 0777);
	mkdir(expected_dir, 0777);
	symlink(expected_dir, dir);
	chmod(dir, 0777);
	ft_setenv(shell->env, "OLDPWD", "foo", ENV_VAR);
	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = dir;
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "OLDPWD", VAR_TYPE), olddir);
	cr_expect_str_eq(ft_getenv(shell->env, "PWD", VAR_TYPE), "/tmp/valid_cd_link/foo");
	getcwd(buff, 1024);
	cr_expect_str_eq(expected_dir, buff, "did not change to correct dir! expected %s, got %s!", expected_dir, buff);
	unlink("/tmp/valid_cd_link/foo");
	rmdir("/tmp/valid_cd_link/bar");
}

Test(builtin_cd_unit, valid_cd_multi_link)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];
	char		*dir = "/tmp/cd_multi_link/foo/baz";
#ifdef __linux__
	char		*expected_dir = "/tmp/cd_multi_link/bar";
#else
	char		*expected_dir = "/private/tmp/cd_multi_link/bar";
#endif
	char		olddir[1024];

	getcwd(olddir, 1024);
	mkdir("/tmp/cd_multi_link", 0777);
	mkdir(expected_dir, 0777);
	symlink(expected_dir, "/tmp/cd_multi_link/foo");
	chmod("/tmp/cd_multi_link/foo", 0777);
	symlink(expected_dir, "/tmp/cd_multi_link/bar/baz");
	chmod("/tmp/cd_multi_link/bar/baz", 0777);
	ft_setenv(shell->env, "OLDPWD", "foo", ENV_VAR);
	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = "/tmp/cd_multi_link/foo";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	free(argv);
	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = "baz";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "OLDPWD", VAR_TYPE), "/tmp/cd_multi_link/foo");
	cr_expect_str_eq(ft_getenv(shell->env, "PWD", VAR_TYPE), dir);
	getcwd(buff, 1024);
	cr_expect_str_eq(expected_dir, buff, "did not change to correct dir! expected %s, got %s!", expected_dir, buff);
	unlink("/tmp/cd_multi_link/baz");
	unlink("/tmp/cd_multi_link/foo");
	rmdir("/tmp/cd_multi_link/bar");
}

Test(builtin_cd_unit, valid_cd_multi_link_remove_link)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];
	char		*dir = "/tmp/cd_remove_link/foo/baz";
#ifdef __linux__
	char		*expected_dir = "/tmp/cd_remove_link/bar";
#else
	char		*expected_dir = "/private/tmp/cd_remove_link/bar";
#endif
	char		olddir[1024];

	getcwd(olddir, 1024);
	mkdir("/tmp/cd_remove_link", 0777);
	mkdir(expected_dir, 0777);
	symlink(expected_dir, "/tmp/cd_remove_link/foo");
	chmod("/tmp/cd_remove_link/foo", 0777);
	symlink(expected_dir, "/tmp/cd_remove_link/bar/baz");
	chmod("/tmp/cd_remove_link/bar/baz", 0777);
	ft_setenv(shell->env, "OLDPWD", "foo", ENV_VAR);
	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = "/tmp/cd_remove_link/foo";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	free(argv);
	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = "baz";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "OLDPWD", VAR_TYPE), "/tmp/cd_remove_link/foo");
	cr_expect_str_eq(ft_getenv(shell->env, "PWD", VAR_TYPE), dir);
	free(argv);
	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = "../";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "OLDPWD", VAR_TYPE), "/tmp/cd_remove_link/foo/baz");
	cr_expect_str_eq(ft_getenv(shell->env, "PWD", VAR_TYPE), "/tmp/cd_remove_link/foo");
	getcwd(buff, 1024);
	cr_expect_str_eq(expected_dir, buff, "did not change to correct dir! expected %s, got %s!", expected_dir, buff);
	unlink("/tmp/cd_remove_link/baz");
	unlink("/tmp/cd_remove_link/foo");
	rmdir("/tmp/cd_remove_link/bar");
}

Test(builtin_cd_unit, valid_cd_multi_link_P_option)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];
#ifdef __linux__
	char		*expected_dir = "/tmp/multi_link_P/bar";
#else
	char		*expected_dir = "/private/tmp/multi_link_P/bar";
#endif
	char		olddir[1024];

	getcwd(olddir, 1024);
	mkdir("/tmp/multi_link_P", 0777);
	mkdir(expected_dir, 0777);
	symlink(expected_dir, "/tmp/multi_link_P/foo");
	chmod("/tmp/multi_link_P/foo", 0777);
	symlink(expected_dir, "/tmp/multi_link_P/bar/baz");
	chmod("/tmp/multi_link_P/foo", 0777);
	ft_setenv(shell->env, "OLDPWD", "foo", ENV_VAR);
	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = "/tmp/multi_link_P/foo";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	free(argv);
	argv = (char **)ft_memalloc(sizeof(char *) * 4);
	argv[0] = "cd";
	argv[1] = "-P";
	argv[2] = "baz";
	argv[3] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "OLDPWD", VAR_TYPE), expected_dir);
	cr_expect_str_eq(ft_getenv(shell->env, "PWD", VAR_TYPE), expected_dir);
	getcwd(buff, 1024);
	cr_expect_str_eq(expected_dir, buff, "did not change to correct dir! expected %s, got %s!", expected_dir, buff);
	unlink("/tmp/multi_link_P/bar/baz");
	unlink("/tmp/multi_link_P/foo");
	rmdir("/tmp/multi_link_P/bar");
}

Test(builtin_cd_unit, cd_invalid_option, .init = redirect_std_err)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		*dir = "/tmp";

	ft_setenv(shell->env, "OLDPWD", "foo", ENV_VAR);
	argv = (char **)ft_memalloc(sizeof(char *) * 4);
	argv[0] = "cd";
	argv[1] = "-PLKPLP";
	argv[2] = dir;
	argv[3] = NULL;
	fflush(stderr);
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
}

Test(builtin_cd_unit, valid_cd_multi_link_multi_option)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];
#ifdef __linux__
	char		*expected_dir = "/tmp/multi_option/bar";
#else
	char		*expected_dir = "/private/tmp/multi_option/bar";
#endif
	char		olddir[1024];

	getcwd(olddir, 1024);
	mkdir("/tmp/multi_option", 0777);
	mkdir(expected_dir, 0777);
	symlink(expected_dir, "/tmp/multi_option/foo");
	chmod("/tmp/multi_option/foo", 0777);
	symlink(expected_dir, "/tmp/multi_option/bar/baz");
	chmod("/tmp/multi_option/foo", 0777);
	ft_setenv(shell->env, "OLDPWD", "foo", ENV_VAR);
	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = "/tmp/multi_option/foo";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	free(argv);
	argv = (char **)ft_memalloc(sizeof(char *) * 9);
	argv[0] = "cd";
	argv[1] = "-P";
	argv[2] = "-L";
	argv[3] = "-P";
	argv[4] = "-L";
	argv[5] = "-L";
	argv[6] = "-P";
	argv[7] = "baz";
	argv[8] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "OLDPWD", VAR_TYPE), expected_dir);
	cr_expect_str_eq(ft_getenv(shell->env, "PWD", VAR_TYPE), expected_dir);
	getcwd(buff, 1024);
	cr_expect_str_eq(expected_dir, buff, "did not change to correct dir! expected %s, got %s!", expected_dir, buff);
	unlink("/tmp/multi_option/bar/baz");
	unlink("/tmp/multi_option/foo");
	rmdir("/tmp/multi_option/bar");
}
