/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_controls.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:54:53 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/29 15:54:53 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_CONTROLS_H
# define FDF_CONTROLS_H

typedef struct s_fdf_key
{
	int		pressed;
	int		id;
}			t_fdf_key;

t_fdf_key	*create_key(void);

#endif
