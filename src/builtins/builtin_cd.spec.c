/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.spec.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/07 22:37:17 by devan         #+#    #+#                 */
/*   Updated: 2020/05/08 01:27:21 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

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
	char		*dir = "/tmp";
#ifdef __linux__
	char		*expected_dir = "/tmp";
#else
	char		*expected_dir = "/private/tmp";
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
	cr_expect_str_eq(ft_getenv(shell->env, "PWD", VAR_TYPE), buff);
	cr_expect_str_eq(buff, expected_dir, "did not change to correct dir! expected %s, got %s!", dir, buff);
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
	char		buff[1024];


	argv = (char **)ft_memalloc(sizeof(char *) * 3);
	argv[0] = "cd";
	argv[1] = "foobar";
	argv[2] = NULL;
	ret = builtin_cd(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "Cetushell: cd: foobar: %s\n", g_error_str[no_such_file_or_dir]);
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

