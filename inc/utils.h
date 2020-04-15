/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 16:43:48 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/14 16:43:48 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cetushell.h"

/*
** ft_swap_rv requires as input a pointer to a t_buff struct and a string seq.
** This function will swap the highlighted text start and end position to always
** match rv_end < rv_start. The function will take the cursor into account which
** makes it different then normal ft_swap.
**
** arg: *buffer: pointer to struct t_buff defined in cetushell.h
*/
void		ft_swap_rv(t_buff *buffer);

/*
**	will re-allocate and expand the char * pointed to by source with addition.
**	if *source is NULL, it will allocate a new string for addition.
*/
void		ft_strexpand(char **source, const char *addition);

/*
**	will allocate a duplicate of the given string, up to length len.
*/
char		*ft_strndup(const char *string, size_t len);

/*
**	will allocate a duplicate of the given string, up to charachter delim.
*/
char		*ft_strcdup(const char *string, char delim);

/*
**	returns the length of string up to charachter delim, or length size,
**	whichever comes first.
*/
size_t		ft_strlenc(const char *string, int delim, size_t size);

#endif
