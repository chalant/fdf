/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_object_rendering.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/30 12:52:12 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline void	init_shape(int shape[2])
{
	shape[0] = 0;
	shape[1] = 0;
}

void	draw_object(t_fdf_mode *mode, t_display *display, t_object *object)
{
	int	shape[2];

	init_shape(shape);
	ft_memset(display->addr, 0x0, display->width * display->height
		* (display->bits_per_pixel / 8));
	fdf_draw_grid(mode, display, object, shape);
}
