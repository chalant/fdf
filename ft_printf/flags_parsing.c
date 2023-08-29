/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	set_width(const char *format, int max, t_flag *flag, int *mask)
{
	int	i;

	i = 0;
	while (i < max && ((!mask[i] && !ft_isdigit(format[i])) || contains(FLAGS,
				format[i])))
		i++;
	while (i < max && ft_isdigit(format[i]))
	{
		flag->width = flag->width * 10 + (format[i] - '0');
		i++;
	}
	return (i);
}

int	set_flag(const char *format, t_flag *flag, int max, int *mask)
{
	int	i;

	i = 0;
	flag->symbol = format[i];
	flag->width = 0;
	if (ft_isdigit(format[i]) && format[i] != '0')
	{
		flag->symbol = 'r';
		return (set_width(format, max, flag, mask));
	}
	else if (contains(WIDTH_FLAGS, flag->symbol))
	{
		if (format[i + 1])
			return (set_width(&format[i + 1], max - 1, flag, &mask[i + 1]));
		else
			return (0);
	}
	return (1);
}

t_flag	*load_flags(const char *format, va_list args, t_mask *mask, int max)
{
	int		i;
	int		j;
	t_flag	*flags;

	(void)args;
	i = 0;
	j = 0;
	flags = malloc(sizeof(t_flag) * mask->num_active);
	if (!flags)
		return (NULL);
	while (i < max)
	{
		if (mask->values[i])
		{
			set_flag(&format[i], &flags[j], max - i, &mask->values[i]);
			flags[j].position = j;
			j++;
		}
		i++;
	}
	return (flags);
}
