/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	fill(char *dest, char *with, size_t from, size_t to)
{
	size_t	i;

	i = 0;
	while (from + i < to)
	{
		dest[from + i] = with[i];
		i++;
	}
	return (i);
}

size_t	copy(char *dest, char *with, size_t from, size_t to)
{
	size_t	i;

	i = 0;
	while (from + i < to)
	{
		dest[i] = with[from + i];
		i++;
	}
	return (i);
}
