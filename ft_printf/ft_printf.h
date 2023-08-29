/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define HEXADECIMALS "0123456789abcdef"
# define SPECIFIERS "cspdiuxX%"
# define WIDTH_FLAGS "-0."
# define FLAGS "+ #"
# define ALL_FLAGS "+# .-0r"

typedef struct s_string
{
	size_t	length;
	char	*chars;
	char	specifier;
	int		is_neg;
	int		is_zero;
	int		max_width;
	int		sign;
}			t_string;

typedef struct s_flag
{
	char	symbol;
	int		width;
	int		position;
	int		priority;
}			t_flag;

typedef struct s_mask
{
	int		*values;
	int		num_active;
}			t_mask;

int			ft_floor(int x);
int			ft_printf(const char *format, ...);
int			is_specifier(char c);
int			get_index(const char *str, char c, int max);
int			get_last_index(const char *str, char c, int max);
int			contains(const char *flags, char c);
int			ncontains(const char *flags, char c, int max);
int			mask_length(int *arr, int size);
int			has_flag(char symbol, t_flag *flags, int num_flags);
int			*initialize_mask(const char *format, int *mask, int max);
int			*create_mask(const char *format, int max);

char		*ft_strndup(const char *input, size_t size);
char		*int_to_base(int nb, int radix, const char *base);
char		*uint_to_base(unsigned int nb, int base, const char *radix);
char		*ulonglong_to_base(unsigned long long nb, int base,
				const char *radix);

size_t		fill(char *dest, char *with, size_t from, size_t to);
size_t		copy(char *dest, char *with, size_t from, size_t to);

t_flag		*load_flags(const char *format, va_list args, t_mask *mask,
				int max);

t_string	*new_string(size_t size, char *s);
t_string	*slice_string(t_string *string, size_t from, size_t to);
t_string	*join_string(t_string *s1, t_string *s2);
t_string	*prepend(t_string *string, size_t size);
t_string	*delete_string(t_string *string);

t_string	*apply_specifier(char specifier, va_list args);
t_string	*to_percentage(va_list args);
t_string	*to_upper(t_string *string, char specifier);
t_string	*to_chars(va_list args);
t_string	*to_char(va_list args);

t_string	*apply_flags(t_string *string, t_flag *flags, int max);
t_string	*apply_precision(t_flag *flags, t_flag flag, t_string *string,
				int num_flags);
t_string	*left_justify(t_flag *flags, t_flag flag, t_string *string,
				int num_flags);
t_string	*right_justify(t_flag *flags, t_flag flag, t_string *string,
				int num_flags);
t_string	*pad_zeroes(t_flag *flags, t_flag flag, t_string *string,
				int num_flags);
t_string	*precede_hex(t_flag flag, t_string *string);
t_string	*insert_sign(t_flag flag, t_string *string);
t_string	*insert_space(t_flag flag, t_flag *flags, t_string *string,
				int num_flags);

#endif
