/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_index(const char *str, char c, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	get_last_index(const char *str, char c, int max)
{
	int	i;

	i = max - 1;
	while (i > -1)
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (-1);
}

int	contains(const char *flags, char c)
{
	int	i;

	i = 0;
	while (flags[i])
	{
		if (c == flags[i])
			return (1);
		i++;
	}
	return (0);
}

int	ncontains(const char *flags, char c, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (c == flags[i])
			return (1);
		i++;
	}
	return (0);
}
