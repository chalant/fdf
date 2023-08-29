/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_string	*apply_precision(t_flag *flags, t_flag flag, t_string *string,
		int num_flags)
{
	int	size;

	(void)flags;
	size = flag.width - ((string->length - (string->is_neg || has_flag('+',
						flags, num_flags) || has_flag(' ', flags, num_flags)))
			- (2 * has_flag('#', flags, num_flags) * !string->is_zero));
	if (size < 0 && string->specifier == 's')
		return (slice_string(string, 0, flag.width));
	else if (size < 0 && string->is_zero)
	{
		if ((has_flag('+', flags, num_flags) || has_flag(' ', flags, num_flags))
			&& string->specifier == 'd')
			return (slice_string(string, 0, string->length - 1));
		delete_string(string);
		return (new_string(0, ft_strndup("", 0)));
	}
	else if (size > 0 && string->specifier != 's')
	{
		flag.width += (string->is_neg || has_flag('+', flags, num_flags)
				|| has_flag(' ', flags, num_flags));
		flag.width += 2 * has_flag('#', flags, num_flags) * !string->is_zero;
		return (pad_zeroes(flags, flag, string, num_flags));
	}
	return (string);
}

t_string	*left_justify(t_flag *flags, t_flag flag, t_string *string,
		int num_flags)
{
	char	*str;
	size_t	size;

	(void)flags;
	(void)num_flags;
	size = (size_t)ft_floor(flag.width - string->length);
	if (size)
	{
		str = malloc(sizeof(char) * (size + 1));
		if (!str)
			return (delete_string(string));
		str[size] = '\0';
		return (join_string(string, new_string(size,
					(char *)ft_memset((void *)str, ' ', size))));
	}
	return (string);
}

t_string	*right_justify(t_flag *flags, t_flag flag, t_string *string,
		int num_flags)
{
	char	*str;
	size_t	size;

	(void)flags;
	(void)num_flags;
	size = (size_t)ft_floor(flag.width - string->length);
	if (size)
	{
		str = malloc(sizeof(char) * (size + 1));
		if (!str)
			return (delete_string(string));
		str[size] = '\0';
		return (join_string(new_string(size, (char *)ft_memset((void *)str, ' ',
						size)), string));
	}
	return (string);
}

t_string	*apply_padding(t_flag *flags, t_string *string, int num_flags,
		int size)
{
	t_string	str;
	char		spec;
	int			n;

	n = has_flag('#', flags, num_flags) * !string->is_zero + 1;
	spec = string->specifier;
	str.is_neg = string->is_neg;
	str.is_zero = string->is_zero;
	string = prepend(slice_string(string, n, string->length), size
			- (str.is_zero * has_flag('#', flags, num_flags)));
	if (str.is_neg)
		string = join_string(new_string(1, ft_strndup("-", 1)), string);
	else if (has_flag('+', flags, num_flags))
		string = join_string(new_string(1, ft_strndup("+", 1)), string);
	else if (has_flag(' ', flags, num_flags))
		string = join_string(new_string(1, ft_strndup(" ", 1)), string);
	else if (has_flag('#', flags, num_flags) && (spec == 'x' || spec == 'X')
		&& str.is_zero && n)
		string = join_string(new_string(2, ft_strndup("00", 2)), string);
	else if (has_flag('#', flags, num_flags) && spec == 'x' && n)
		string = join_string(new_string(2, ft_strndup("0x", 2)), string);
	else if (has_flag('#', flags, num_flags) && spec == 'X' && n)
		string = join_string(new_string(2, ft_strndup("0X", 2)), string);
	return (string);
}

t_string	*pad_zeroes(t_flag *flags, t_flag flag, t_string *string,
		int num_flags)
{
	int	size;

	size = ft_floor(flag.width - string->length);
	if (size <= 0)
		return (string);
	if (((string->is_neg || has_flag('+', flags, num_flags) || has_flag(' ',
					flags, num_flags)) && string->specifier == 'd')
		|| has_flag('#', flags, num_flags))
		return (apply_padding(flags, string, num_flags, size));
	return (prepend(string, size));
}
