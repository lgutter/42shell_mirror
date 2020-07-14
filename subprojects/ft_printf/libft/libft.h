/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/10 17:29:34 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/04 19:18:57 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

struct				s_ft_getopt
{
	char			*arg;
	int				index;
	int				group_index;
	char			opt;
	bool			illegal;
};

void				*ft_memset(void *target, int setvalue, size_t len);
void				ft_bzero(void *input, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t len);
void				*ft_memccpy(void *dst, const void *src, int delim,
								size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *source, int character, size_t len);
int					ft_memcmp(const void *source1, const void *source2,
								size_t len);
size_t				ft_strlen(const char *string);
char				*ft_strdup(const char *string);
char				*ft_strcdup(const char *string, char delim);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *string1, const char *string2);
char				*ft_strncat(char *string1, const char *string2, size_t len);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *string, int character);
char				*ft_strrchr(const char *string, int character);
char				*ft_strstr(const char *string, const char *word);
char				*ft_strnstr(const char *string, const char *word,
								size_t len);
int					ft_strcmp(const char *string1, const char *string2);
int					ft_strncmp(const char *string1, const char *string2,
								size_t len);
int					ft_atoi(const char *string);
int					ft_intlen(int n);
int					ft_isalpha(int character);
int					ft_isdigit(int character);
int					ft_isalnum(int character);
int					ft_isascii(int character);
int					ft_isprint(int character);
int					ft_isspace(int character);
int					ft_toupper(int character);
int					ft_tolower(int character);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **pointer);
char				*ft_strnew(size_t size);
void				ft_strdel(char **string);
void				ft_strclr(char *string);
void				ft_striter(char *string, void (*function)(char *));
void				ft_striteri(char *string,
								void (*function)(unsigned int, char *));
char				*ft_strmap(char const *string, char (*function)(char));
char				*ft_strmapi(char const *string,
								char (*function)(unsigned int, char));
int					ft_strequ(char const *string1, char const *string2);
int					ft_strnequ(char const *str1, char const *str2, size_t len);
char				*ft_strsub(char const *string, unsigned int start,
								size_t len);
char				*ft_strjoin(char const *string1, char const *string2);
char				*ft_strtrim(char const *str);
char				**ft_strsplit(char const *string, char delim);
char				**ft_strsplit_t_s(char const *string);
char				*ft_itoa(int integer);
void				ft_putchar(char character);
void				ft_putstr(char const *string);
void				ft_putendl(char const *string);
void				ft_putnbr(int number);
void				ft_putchar_fd(char character, int filedes);
void				ft_putstr_fd(char const *string, int filedes);
void				ft_putendl_fd(char const *string, int filedes);
void				ft_putnbr_fd(int number, int filedes);

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **start, void (*del)(void *, size_t));
void				ft_lstadd(t_list **start, t_list *new);
void				ft_lstiter(t_list *list, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *list, t_list *(*f)(t_list *elem));

long				ft_absneg(long integer);
long				ft_abspos(long integer);
int					ft_iswhitespace(char character);
size_t				ft_strlenc(const char *string, int delim, size_t size);
void				*ft_memrcpy(void *dst, const void *src, size_t len);
void				*ft_memdup(const void *source, size_t len);
void				*ft_memcdup(const void *source, int delim, size_t size);
void				*ft_memjoin(const void *str1, size_t size1,
								const void *str2, size_t size2);
void				ft_memexpand(void **src, size_t *size1, const void *add,
									size_t size2);
void				ft_memdelsize(void *pointer, size_t size);
size_t				ft_nbrlenbase(long long number, int base);
size_t				ft_lstlen(t_list **start);
void				ft_lstaddback(t_list **start, t_list *new);
t_list				*ft_lstaddnext(t_list *current, t_list *new);

void				ft_strexpand(char **source, const char *addition);
void				ft_swap(char *a, char *b);
char				*ft_strrev(char *str, int start);
char				*ft_itoa_base(signed long long nb, const unsigned int base);
char				*ft_ulltoa_base_upp(\
									unsigned long long nb, const unsigned base);
char				*ft_ulltoa_base_low(\
									unsigned long long nb, const unsigned base);
size_t				ft_nbrlenbase_ull(unsigned long long number, int base);
char				*ft_strcharjoin(char *str, char c);
void				ft_strcharexpand(char **source, const char addition);

/*
**	Arguments:
**	char **pointer_array: array of character pointers, NULL delimited.
**	Returns:
**	the amount of character pointers in the array.
*/
size_t				ft_str_arr_len(char **pointer_array);

/*
**	Arguments:
**	char *string: string to be duplicated (partially).
**	size_t len: the amount of characters to be copied.
**	Returns:
**	a fresh copy of the string up until len.
*/
char				*ft_strndup(const char *string, size_t len);

/*
**	Arguments:
**	char **array: the array of strings to be freed.
**	frees every char * in the array, by iterating over it until it finds NULL.
**	Returns:
**	the amount of strings that were found and freed.
*/
size_t				ft_free_str_array(char **array);

/*
**	Arguments:
**	char **array: the array of strings to be printed.
**	prints every string in the array, followed by a newline.
**	Returns:
**	0 on succes.
**	-1 on failure.
*/
int					ft_print_str_array(char **array);

bool				ft_getopt(struct s_ft_getopt *opt, int argc, char **argv,
						const char *optstring);

#endif
