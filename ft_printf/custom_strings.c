/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_strings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_string	*free_strings(t_string *s1, t_string *s2)
{
	if (!s1 && s2)
		delete_string(s2);
	else if (s1 && !s2)
		delete_string(s1);
	else if (s1 && s2)
	{
		delete_string(s1);
		delete_string(s2);
	}
	return (NULL);
}

t_string	*slice_string(t_string *string, size_t from, size_t to)
{
	size_t		size;
	t_string	*out;
	char		*str;

	if (!string)
		return (NULL);
	size = to - from;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (delete_string(string));
	str[size] = '\0';
	copy(str, string->chars, from, to);
	out = new_string(size, str);
	if (!out)
		return (delete_string(string));
	out->is_neg = string->is_neg;
	out->specifier = string->specifier;
	delete_string(string);
	return (out);
}

t_string	*join_string(t_string *s1, t_string *s2)
{
	t_string	*out;

	if (!s1 || !s2)
		return (free_strings(s1, s2));
	out = new_string(s1->length + s2->length, malloc(sizeof(char) * (s1->length
					+ s2->length)));
	if (!out)
		return (free_strings(s1, s2));
	fill(out->chars, s2->chars, fill(out->chars, s1->chars, 0, s1->length),
		(s1->length + s2->length));
	free_strings(s1, s2);
	return (out);
}

t_string	*new_string(size_t size, char *s)
{
	t_string	*out;

	if (!s)
		return (NULL);
	out = (t_string *)malloc(sizeof(t_string));
	if (!out)
	{
		free(s);
		return (NULL);
	}
	out->chars = s;
	out->length = size;
	out->is_neg = 0;
	out->is_zero = 0;
	out->sign = 0;
	return (out);
}

t_string	*delete_string(t_string *string)
{
	if (!string)
		return (NULL);
	free(string->chars);
	free(string);
	return (NULL);
}
