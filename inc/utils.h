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
**	will re-allocate and expand the char * pointed to by source with both
**	additions in order.
**	if *source is NULL, it will allocate a new string for the additions.
*/
void		str_expand_triple(char **source, char *add1, char *add2);

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

/*
**	checks if the given string contains invalid single or double quoted strings.
**	check_quote assumes the word is a result of the tokenizer, and only contains
**	one single or double quote. otherwise it will return the type of the last
**	quote in the word.
**	returns:
**	-2:	if the string contains an unterminated double quote.
**	-1:	if the string contains an unterminated single quote.
**	 0:	if the string does not contain quotes.
**	 1:	if the string contains an valid single quote.
**	 2:	if the string contains an valid double quote.
*/
int			check_quote(char *word);

/*
**	removes the quote symbols from the beginning and end of quotes in word.
**	it only removes quote symbols if the string only contains valid quotes.
**	returns:
**	-1:	on failure.
**	 0:	on succes.
*/
int			remove_quotes(char **word);

/*
**	completes an unterminated quote in word with character delim.
**	returns:
**	-1: on failure.
**	 0:	on succes.
*/
int			complete_quote(t_shell *shell, char **word);

/*
**	counts the number of quote symbols (["], ['], [\]) in str.
**	returns:
**	number of quote characters in the string passed as argument.
*/
size_t		count_quote_chars(char *str);

/*
**	makes a copy of str with a backslash ([\]) in front of every
**	quote character (["], ['], [\]) in the string, and returns it.
**	returns:
**	NULL: on error.
**	copy of str with quote characters escaped on succes.
*/
char		*backslash_quotes(char *str);

#endif
