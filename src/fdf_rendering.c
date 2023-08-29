/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/29 15:53:50 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_projection(t_fdf *fdf, t_fdf_mode *mode, t_object *object)
{
	matmul(mode->projector, object->body, object->projection);
	mode->perspective_hook(object);
	inplace_matmul(fdf->transforms, object->projection, object->result);
	inplace_matmul(mode->scale, object->projection, object->result);
	inplace_matmul(fdf->centering, object->projection, object->result);
}

int	update_view(t_fdf *fdf)
{
	apply_projection(fdf, fdf->mode, fdf->map);
	draw_object(fdf->mode, fdf->display, fdf->map);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->display->img, 0, 0);
	return (1);
}
