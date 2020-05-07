/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.spec.c                                    :+:    :+:            */
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

Test(builtins, env_null)
{
    t_command comm;

    ft_bzero(&comm, sizeof(t_command));
    int ret = builtin_env(&comm, NULL);
    cr_assert_eq(ret, 0);
}

Test(builtins, shellenv_null)
{
    t_command comm;

    ft_bzero(&comm, sizeof(t_command));
    int ret = builtin_shellenv(&comm, NULL);
    cr_assert_eq(ret, 0);
}

Test(builtins, set_env_bad_format)
{
    t_command comm;
    t_env *env = dup_sys_env();
    int     ret = 0;

    comm.argc = 2;
    comm.argv[0] = ft_strdup("set");
    comm.argv[1] = ft_strdup("0test=dit");
    ret = builtin_set(&comm, &env);
    cr_assert_eq(ret, error_inv_format, "ret is %d but must be %d", ret, 0);   
}

Test(builtins, cd_no_home)
{
    t_command comm;
    t_env *env = dup_sys_env();
    int     ret = 0;

    
    ret = ft_unsetenv(env, "HOME", RW_SHELL);
    cr_assert_eq(ret, 0, "ret is %d but must be %d", ret, 0);
    comm.argc = 1;
    ret = builtin_cd(&comm, &env);
    cr_assert_eq(ret, 1, "ret is %d but must be %d", ret, 1);
}

Test(builtins, cd_many_args)
{
    t_command comm;
    t_env *env = dup_sys_env();

    comm.argc = 4;
    
    int ret = 0;
	cr_redirect_stderr();
	ret = builtin_cd(&comm, &env);
	fflush(stderr);
	cr_expect_stderr_eq_str("cd: argc: To many arguments given\n");
	cr_expect_eq(to_many_arguments, ret);
}
