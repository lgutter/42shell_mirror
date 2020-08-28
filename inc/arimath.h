/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arimath.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 10:58:15 by aholster      #+#    #+#                 */
/*   Updated: 2020/04/20 10:58:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARIMATH_H
# define ARIMATH_H

# include "environment.h"

enum			e_operator{
	none,
	penta_increment,
	penta_decrement,
	tri_increment,
	tri_decrement,
	increment,
	decrement,
	addition,
	subtraction,
	multiply,
	divide,
	modulo,
	equal_or_less,
	equal_or_greater,
	lessthan,
	greaterthan,
	equal,
	unequal,
	and,
	or,
	end_terminator,
};

typedef long int	(*t_math_action)(long int, long int);

struct			s_action_kvp{
	enum e_operator	operator;
	t_math_action	action;
};

struct			s_ari_node{
	char				*original_key;
	long int			value;
	enum e_operator		operator;
	struct s_ari_node	*next;
	struct s_ari_node	*prev;
};

int				arithmatic_expansion(t_shell *const shell,
					char **const astring,
					size_t *const aread_index,
					size_t *const awrite_index);

int				arithmatic_run_math_operations(char **tape,
					t_env *const env,
					struct s_ari_node **const node_list);
int				run_crementers(t_env *const env,
					struct s_ari_node **const node_list);

int				create_token_list(t_env *const env,
					const char *tape,
					struct s_ari_node **const node_list);

int				arithmatic_add_token(struct s_ari_node **const node_list,
					char *const original_key,
					const long int value,
					const enum e_operator operator);

int				arithmatic_getint_from_env(long int *const alint,
					t_env *const env,
					const char *const key);
long int		arithmatic_atol_base(size_t	*const len, const char *str);

void			arithmatic_remove_token(struct s_ari_node *anode);
void			arithmatic_delete_tokens(struct s_ari_node **const node_list);

long int		arithmath_addition(long int num1, long int num2);
long int		arithmath_subtraction(long int num1, long int num2);
long int		arithmath_multiply(long int num1, long int num2);
long int		arithmath_divide(long int num1, long int num2);
long int		arithmath_modulo(long int num1, long int num2);

long int		arithmath_equal(long int num1, long int num2);
long int		arithmath_unequal(long int num1, long int num2);
long int		arithmath_equal_or_less(long int num1, long int num2);
long int		arithmath_equal_or_greater(long int num1, long int num2);

long int		arithmath_lessthan(long int num1, long int num2);
long int		arithmath_greaterthan(long int num1, long int num2);

long int		arithmath_and(long int num1, long int num2);
long int		arithmath_or(long int num1, long int num2);

#endif
