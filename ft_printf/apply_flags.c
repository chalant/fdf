/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	has_flag(char symbol, t_flag *flags, int num_flags)
{
	int	i;

	i = 0;
	while (i < num_flags)
	{
		if (symbol == flags[i].symbol)
			return (1);
		i++;
	}
	return (0);
}

static t_string	*apply_flag(t_flag flag, t_flag *flags, t_string *string,
		int num_flags)
{
	if (flag.symbol == '-')
		return (left_justify(flags, flag, string, num_flags));
	else if (flag.symbol == 'r')
		return (right_justify(flags, flag, string, num_flags));
	else if (flag.symbol == '0')
		return (pad_zeroes(flags, flag, string, num_flags));
	else if (flag.symbol == '.')
		return (apply_precision(flags, flag, string, num_flags));
	else if (flag.symbol == '#')
		return (precede_hex(flag, string));
	else if (flag.symbol == ' ')
		return (insert_space(flag, flags, string, num_flags));
	else if (flag.symbol == '+')
		return (insert_sign(flag, string));
	return (string);
}

t_string	*set_fields(t_string *new, t_string *prev)
{
	if (new)
	{
		new->is_neg = prev->is_neg;
		new->specifier = prev->specifier;
		new->is_zero = prev->is_zero;
		new->sign = prev->sign;
	}
	return (new);
}

void	sort_flags(t_flag *flags, int num_flags)
{
	int		i;
	int		j;
	t_flag	temp;

	i = 0;
	j = 0;
	while (i < num_flags - 1)
	{
		j = 0;
		while (j < num_flags - i - 1)
		{
			if (get_index(ALL_FLAGS, flags[j].symbol, 7) < get_index(
					ALL_FLAGS, flags[j + 1].symbol, 7))
			{
				temp = flags[j];
				flags[j] = flags[j + 1];
				flags[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

t_string	*apply_flags(t_string *string, t_flag *flags, int max)
{
	int			i;
	t_string	*output;
	t_string	str;

	if (!string)
		return (NULL);
	if (!max)
		return (string);
	sort_flags(flags, max);
	str.is_neg = string->is_neg;
	str.is_zero = string->is_zero;
	str.specifier = string->specifier;
	output = apply_flag(flags[max - 1], flags, string, max);
	if (!output)
		return (NULL);
	i = max - 2;
	while (i > -1)
	{
		output = apply_flag(flags[i], flags, set_fields(output, &str), max);
		if (!output)
			return (NULL);
		i--;
	}
	return (output);
}
