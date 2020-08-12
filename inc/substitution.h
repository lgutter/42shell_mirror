/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   substitution.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nloomans <nloomans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 0000/00/00 00:00:00 by nloomans      #+#    #+#                 */
/*   Updated: 9999/99/99 99:99:99 by nloomans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSTITUTION_H
# define SUBSTITUTION_H

# include <sys/types.h>

/*
** subst_length_tail is an internal function which cannot be static because of
** norm requirements. Use subst_length instead.
*/
ssize_t		subst_length_tail(const char *input, ssize_t acc);

/*
** subst_length takes a command or arithmetic substitution as input, excluding
** the `$(` prefix, and returns how many characters are in the substitution,
** including the `)` suffix.
**
** Returns -1 if no end was found.
**
** Example: "echo hi) test" returns 8. "echo hi" returns -1.
*/
ssize_t		subst_length(const char *input);

#endif
