/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifiers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_string	*pointer_to_hex(va_list args)
{
	void		*ptr;
	char		*str;
	t_string	*string;

	ptr = va_arg(args, void *);
	str = ulonglong_to_base((unsigned long long)ptr, 16, HEXADECIMALS);
	if (!str)
		return (NULL);
	string = join_string(new_string(2, ft_strndup("0x", 2)),
			new_string(ft_strlen(str), str));
	if (!string)
		return (NULL);
	string->specifier = 'p';
	return (string);
}

t_string	*to_decimal(va_list args)
{
	int			value;
	char		*str;
	t_string	*string;

	value = va_arg(args, int);
	str = ft_itoa(value);
	if (!str)
		return (NULL);
	string = new_string(ft_strlen(str), str);
	if (!string)
		return (NULL);
	string->is_neg = value < 0;
	string->is_zero = value == 0;
	string->specifier = 'd';
	return (string);
}

t_string	*to_unsigned_int(va_list args)
{
	char			*str;
	unsigned int	val;
	t_string		*string;

	val = va_arg(args, unsigned int);
	str = uint_to_base(val, 10, HEXADECIMALS);
	if (!str)
		return (NULL);
	string = new_string(ft_strlen(str), str);
	if (!string)
		return (NULL);
	string->is_zero = val == 0;
	string->specifier = 'u';
	return (string);
}

t_string	*to_hexadecimal(va_list args)
{
	char			*str;
	unsigned int	val;
	t_string		*string;

	val = va_arg(args, unsigned int);
	str = uint_to_base(val, 16, HEXADECIMALS);
	if (!str)
		return (NULL);
	string = new_string(ft_strlen(str), str);
	if (!string)
		return (NULL);
	string->is_zero = val == 0;
	string->specifier = 'x';
	return (string);
}

t_string	*apply_specifier(char specifier, va_list args)
{
	if (specifier == 's')
		return (to_chars(args));
	else if (specifier == 'c')
		return (to_char(args));
	else if (specifier == 'd')
		return (to_decimal(args));
	else if (specifier == 'i')
		return (to_decimal(args));
	else if (specifier == 'p')
		return (pointer_to_hex(args));
	else if (specifier == 'u')
		return (to_unsigned_int(args));
	else if (specifier == 'x')
		return (to_hexadecimal(args));
	else if (specifier == '%')
		return (to_percentage(args));
	else if (specifier == 'X')
		return (to_upper(to_hexadecimal(args), specifier));
	return (NULL);
}
