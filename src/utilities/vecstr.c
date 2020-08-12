/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vecstr.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nloomans <nloomans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 0000/00/00 00:00:00 by nloomans      #+#    #+#                 */
/*   Updated: 9999/99/99 99:99:99 by nloomans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "handle_error.h"
#include "vecstr.h"

static size_t	cap_for_len(size_t len)
{
	size_t cap;

	cap = 64;
	while (cap < len + 1)
		cap *= 2;
	return (cap);
}

static int		grow_string(char **str, size_t old_len, size_t new_len)
{
	char *out;

	out = ft_strnew(new_len);
	if (out == NULL)
		return (-1);
	ft_memcpy(out, *str, old_len);
	free(*str);
	*str = out;
	return (0);
}

t_vecstr		new_vecstr(const char *string)
{
	t_vecstr	new;

	if (string == NULL)
		return ((t_vecstr){NULL, 0, 0});
	new.len = ft_strlen(string);
	new.cap = cap_for_len(new.len);
	new.string = ft_memalloc(new.cap);
	if (new.string == NULL)
		return ((t_vecstr){NULL, 0, 0});
	ft_strncpy(new.string, string, new.cap);
	return (new);
}

void			clear_vecstr(t_vecstr *vecstr)
{
	if (vecstr != NULL)
	{
		free(vecstr->string);
		ft_memset(vecstr, '\0', sizeof(*vecstr));
	}
}

int				vecstr_add(t_vecstr *vecstr, const char *append, size_t len)
{
	size_t	new_cap;

	if (vecstr == NULL)
		return (var_not_set);
	if (append == NULL || len == 0)
		return (no_error);
	if (vecstr->len + len + 1 > vecstr->cap)
	{
		new_cap = cap_for_len(vecstr->len + len);
		if (grow_string(&vecstr->string, vecstr->len, new_cap - 1) == -1)
			return (malloc_error);
		vecstr->cap = new_cap;
	}
	ft_memcpy(vecstr->string + vecstr->len, append, len);
	vecstr->len += len;
	return (no_error);
}
