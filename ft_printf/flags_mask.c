/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_mask.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	disable_targets(const char *format, int *mask, char t1, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (format[i] == t1 && mask[i])
			mask[i] = 0;
		i++;
	}
}

void	disable_duplicates(const char *format, int *mask, char t1, int max)
{
	int	i;
	int	skip;

	i = 0;
	skip = get_index(format, t1, max);
	while (i < max)
	{
		if (format[i] == t1 && i != skip && mask[i])
			mask[i] = 0;
		i++;
	}
}

int	mask_length(int *arr, int size)
{
	int		i;
	size_t	total;

	if (!arr)
		return (0);
	i = 0;
	total = 0;
	while (i < size)
	{
		total += arr[i];
		i++;
	}
	return (total);
}

int	*create_mask(const char *format, int max)
{
	int	i;
	int	*mask;

	i = 0;
	mask = malloc(max * sizeof(int));
	if (!mask)
		return (NULL);
	while (i < max)
	{
		mask[i] = 1;
		i++;
	}
	i = 0;
	while (ALL_FLAGS[i])
	{
		disable_duplicates(format, mask, ALL_FLAGS[i], max);
		i++;
	}
	if (ncontains(format, '-', max) || ncontains(format, '.', max))
		disable_targets(format, mask, '0', max);
	if (ncontains(format, '+', max))
		disable_targets(format, mask, ' ', max);
	return (mask);
}

int	*initialize_mask(const char *format, int *mask, int max)
{
	int	i;
	int	j;

	if (!mask)
		return (NULL);
	i = 0;
	j = 0;
	while (i < max)
	{
		if (mask[i] && (ft_isdigit(format[i]) || contains(WIDTH_FLAGS,
					format[i])))
		{
			j = i + 1;
			while (j < max && !ft_isdigit(format[j]))
				j++;
			while (format[j] && ft_isdigit(format[j]))
			{
				mask[j] = 0;
				j++;
			}
		}
		i++;
	}
	return (mask);
}
