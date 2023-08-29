/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_to_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_intlen(unsigned int nb, int base)
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

static char	*create_string(int len)
{
	char	*str;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*uint_to_base(unsigned int nb, int base, const char *radix)
{
	int		i;
	int		len;
	char	*str;

	len = ft_intlen(nb, base);
	str = create_string(len);
	if (!str)
		return (NULL);
	i = len - 1;
	while (i > -1)
	{
		str[i] = radix[nb % base];
		nb /= base;
		i--;
	}
	str[len] = '\0';
	return (str);
}
