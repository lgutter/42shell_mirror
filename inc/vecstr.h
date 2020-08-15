/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vecstr.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nloomans <nloomans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 0000/00/00 00:00:00 by nloomans      #+#    #+#                 */
/*   Updated: 9999/99/99 99:99:99 by nloomans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECSTR_H
# define VECSTR_H

#include <stdio.h>

/*
** t_vecstr is a simple vector string implementation. It allows you to
** efficiently keep appending data to the end of the string without needing to
** re-allocate every time.
**
** string a C-style null terminated string.
** len is the length of the string, excluding the terminating null byte.
**   It should be equal to ft_strlen(string).
** cap is the amount of bytes malloced for string, including the terminating
**   null byte.
*/
typedef struct		s_vecstr
{
	char	*string;
	size_t	cap;
	size_t	len;
}					t_vecstr;

/*
** new_vector returns a t_vecstr with string dublicated into it. If string is
** NULL an empty t_vecstr is returned instead.
*/
t_vecstr			new_vecstr(const char *string);

/*
** clear_vecstr frees the string in t_vecstr and resets all the meta data.
*/
void				clear_vecstr(t_vecstr *vecstr);

/*
** vecstr_add adds a number of bytes to the vecstr, recallocating if necessary.
** append does not need to be null-terminated as len bytes will always be added.
** note that this also means it's undefined behavior if len is larger then append.
*/
int					vecstr_add(t_vecstr *vecstr,
						const char *append, size_t len);

#endif
