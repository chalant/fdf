/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standalone_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 14:20:57 by ychalant          #+#    #+#             */
/*   Updated: 2023/07/09 14:20:57 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_string	*precede_hex(t_flag flag, t_string *string)
{
	(void)flag;
	if (string->specifier == 'x' && !string->is_zero)
		return (join_string(new_string(2, ft_strndup("0x", 2)), string));
	else if (string->specifier == 'X' && !string->is_zero)
		return (join_string(new_string(2, ft_strndup("0X", 2)), string));
	return (string);
}

t_string	*insert_sign(t_flag flag, t_string *string)
{
	(void)flag;
	if (!string->is_neg)
		return (join_string(new_string(1, ft_strndup("+", 1)), string));
	return (string);
}

t_string	*insert_space(t_flag flag, t_flag *flags, t_string *string,
		int num_flags)
{
	(void)flag;
	(void)flags;
	(void)num_flags;
	if (string->specifier == 'd' && !string->is_neg)
		return (join_string(new_string(1, ft_strndup(" ", 1)), string));
	return (string);
}
