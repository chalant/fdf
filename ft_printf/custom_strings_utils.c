/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_strings_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strndup(const char *input, size_t size)
{
	size_t	i;
	char	*res;

	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = input[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_string	*prepend(t_string *string, size_t size)
{
	char	*str;

	if (!size)
		return (string);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (delete_string(string));
	str[size] = '\0';
	return (join_string(new_string(size, (char *)ft_memset((void *)str, '0',
					size)), string));
}
