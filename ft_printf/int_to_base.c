/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_intlen(int nb, int base)
{
	int	i;

	i = (nb == 0);
	while (nb != 0)
	{
		nb /= base;
		i++;
	}
	return (i);
}

char	*create_string(int nb, int len)
{
	char	*str;

	str = malloc(sizeof(char) * (len + 1 + (nb < 0)));
	if (!str)
		return (NULL);
	return (str);
}

char	*int_to_base(int nb, int base, const char *radix)
{
	int		i;
	int		len;
	int		stop;
	char	*str;

	nb = (long long)nb;
	stop = -(nb >= 0);
	len = ft_intlen(nb, base) + (nb < 0);
	str = create_string(nb, len);
	if (!str)
		return (0);
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	i = len - 1;
	while (i > stop)
	{
		str[i] = radix[nb % base];
		nb /= base;
		i--;
	}
	str[len] = '\0';
	return (str);
}
