/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifiers_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_specifier(char c)
{
	int	i;

	i = 0;
	while (SPECIFIERS[i])
	{
		if (c == SPECIFIERS[i])
			return (1);
		i++;
	}
	return (0);
}

t_string	*to_chars(va_list args)
{
	char		*str;
	t_string	*string;
	size_t		len;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	string = new_string(len, ft_strndup(str, len));
	if (!string)
		return (NULL);
	string->specifier = 's';
	return (string);
}

t_string	*to_char(va_list args)
{
	char		*str;
	t_string	*string;

	str = malloc(sizeof(char) + 1);
	if (!str)
		return (NULL);
	str[0] = (char)va_arg(args, int);
	str[1] = '\0';
	string = new_string(1, str);
	if (!string)
		return (NULL);
	string->specifier = 'c';
	return (string);
}

t_string	*to_percentage(va_list args)
{
	t_string	*string;

	(void)args;
	string = new_string(1, ft_strndup("%", 1));
	if (!string)
		return (NULL);
	string->specifier = '%';
	return (string);
}

t_string	*to_upper(t_string *string, char specifier)
{
	size_t	i;

	if (!string)
		return (NULL);
	i = 0;
	while (i < string->length)
	{
		string->chars[i] = ft_toupper(string->chars[i]);
		i++;
	}
	string->specifier = specifier;
	return (string);
}
