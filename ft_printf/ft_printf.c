/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_string	*free_mask(t_mask *mask)
{
	if (mask->values)
		free(mask->values);
	free(mask);
	return (NULL);
}

int	write_and_free(t_string *string, va_list args)
{
	int	bytes_written;

	va_end(args);
	if (!string)
		return (-1);
	bytes_written = write(1, string->chars, string->length);
	delete_string(string);
	return (bytes_written);
}

int	next_specifier(const char *format, int i)
{
	while (format[i] && format[i] != '%')
		i++;
	return (i);
}

t_string	*to_string(const char *format, va_list args, char spec, int max)
{
	t_flag		*flags;
	t_string	*output;
	t_mask		*mask;

	mask = malloc(sizeof(t_mask));
	if (!mask)
		return (NULL);
	mask->values = initialize_mask(format, create_mask(format, max), max);
	mask->num_active = mask_length(mask->values, max);
	if (!mask->values)
		return (free_mask(mask));
	flags = load_flags(format, args, mask, max);
	if (!flags)
		return (free_mask(mask));
	output = apply_flags(apply_specifier(spec, args), flags, mask->num_active);
	free(flags);
	free_mask(mask);
	return (output);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	t_string	*output;
	int			i;
	int			j;

	va_start(args, format);
	i = next_specifier(format, 0);
	output = new_string(i, ft_strndup(format, i));
	while (format[i])
	{
		j = i + 1;
		while (format[j] && !is_specifier(format[j]))
			j++;
		output = join_string(output, to_string(&format[i + 1], args, format[j],
					j - (i + 1)));
		if (!output)
			break ;
		i = next_specifier(format, j + 1);
		output = join_string(output, new_string(i - (j + 1), ft_strndup(format
						+ j + 1, i - (j + 1))));
		if (!output)
			break ;
	}
	return (write_and_free(output, args));
}
