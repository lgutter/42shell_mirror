/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 14:10:30 by ivan-tey      #+#    #+#                 */
/*   Updated: 2019/12/13 11:13:31 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

typedef void			(*t_writer)\
						(void *target, unsigned long long *totallen, \
						const char *string, size_t len);

/*
**	enumerations for the flags and modifiers stored in lenmod and flags.
**	these are written down here as bitshifts, but in essence the exact number
**	linked to an enum is not relevant, just that we can uniquely store and
**	fetch any option (flag or modifier)
*/
enum					e_lenmod
{
	e_L = 1 << 0,
	e_l = 1 << 1,
	e_h = 1 << 2,
	e_ll = 1 << 3,
	e_hh = 1 << 4
};

enum					e_flags
{
	e_hash = 1 << 0,
	e_zero = 1 << 1,
	e_space = 1 << 2,
	e_minus = 1 << 3,
	e_plus = 1 << 4,
	e_middle = 1 << 5
};

typedef struct			s_string_n_info
{
	char				*target;
	size_t				len;
	size_t				*index;
}						t_string_n_info;

/*
**	the info struct! this contains anything that we might need.
**	A short explanation of every variable in the struct:
**	flags & lenmod:	Uses the above mentioned enums to store flags / lenmods.
**	conv:			Contains the char representing the conversion specifier.
**	precfound:		positive if a precision was found, negative if it was not.
**	sign:			Used to specify if a number is positive or negative.
**	arguments:		Va_list with all the arguments that printf received.
**	width:			Simple value representing the width provided.
**	precision:		Simple value representing the precision provided.
**	writer:			A function pointer to the writer function.
**	target:			Where to write to. * to FILE *, filedescriptor, or char *.
**	totallen:		Adds up the total amount of characters printed as a
**					return value.
*/

typedef struct			s_info
{
	unsigned char		flags;
	unsigned char		lenmod;
	unsigned char		conv;
	char				precfound;
	int					sign;
	size_t				len;
	va_list				arguments;
	size_t				width;
	size_t				precision;
	t_writer			writer;
	void				*target;
	unsigned long long	totallen;
}						t_info;

/*
**	Used to check the sign bit of a float
**	flnb:			long double representation of a float.
**	shnb:			float devided in five pieces of two bytes.
*/

typedef union			u_floatunion
{
	long double			flnb;
	short				shnb[5];
}						t_floatunion;

typedef int				(*t_formatter)(t_info *info);

int						ft_printf(const char *restrict format, ...);
int						ft_dprintf(int fd, const char *restrict format, ...);
int						ft_snprintf(char *target, size_t len,
											const char *restrict format, ...);
int						ft_process_conversion(const char *format, t_info *info);
int						ft_init_info(const char *format, t_info *info);
t_formatter				ft_dispatcher(char conv_flag);

/*
**	Find functions for finding and storing all flags, width,
**	precision and lenghtmodifiers
*/

int						ft_find_flags(const char *format, t_info *info, int i);
int						ft_find_width(const char *format, t_info *info, int i);
int						ft_find_lenmod(const char *format, t_info *info, int i);
int						ft_find_precision\
						(const char *format, t_info *info, int i);

/*
**	Format functions for handling the converison of
**	csp + diouxX + f and unknown conversion specifiers
*/

int						ft_formatunknown(t_info *info, char c);

int						ft_formatchar(t_info *info);
int						ft_formatstring(t_info *info);
int						ft_formatpointer(t_info *info);
size_t					ft_precision_string(t_info *info, char **string);

int						ft_format_unsigneddecimal(t_info *info);
int						ft_formatdecimal(t_info *info);
int						ft_formatlonglong(long long n, t_info *info);
int						ft_formatlonglongunsigned(\
						unsigned long long n, t_info *info);
char					*ft_precision_int(t_info *info, char *number);

int						ft_format_octal(t_info *info);
int						ft_formatulloctal(unsigned long long n, t_info *info);

int						ft_format_upphex(t_info *info);
int						ft_formatullupphex(unsigned long long n, t_info *info);
int						ft_format_lowhex(t_info *info);
int						ft_formatulllowhex(unsigned long long n, t_info *info);

int						ft_format_floats(t_info *info);
int						ft_formatunsignedfloat(t_info *info, long double f);
char					*ft_float_precision(t_info *info, char *nb);
int						ft_check_sign(long double f);
size_t					ft_correctlen(t_info *info);

/*
**	Write functions for outputing the conversions and
**	adding the correct width and flags
*/

void					ft_write_middle_width(t_info *info, char *str);
void					ft_write_width(t_info *info, size_t len);
void					ft_write_flags(t_info *info);
int						ft_write_order(t_info *info, char *str, char *order);
void					ft_writer_fd\
						(void *target, unsigned long long *totallen, \
						const char *string, size_t len);
void					ft_writer_string_n
						(void *target, unsigned long long *totallen,\
						const char *string, size_t len);

#endif
