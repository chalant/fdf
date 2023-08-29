/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_isometric_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:42:31 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/24 13:42:31 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	no_perspective(t_object *object)
{
	(void)object;
	return (1);
}

int	no_clipping(float value)
{
	(void)value;
	return (1);
}

int	create_isometric_mode(t_fdf *fdf)
{
	t_fdf_mode	*mode;
	t_display	*display;
	float		s;

	mode = malloc(sizeof(t_fdf_mode));
	if (!mode)
		return (0);
	display = fdf->display;
	s = 300.0f * (float)display->width / (float)display->height;
	mode->projector = isometric_projector();
	if (!mode->projector)
		return (0);
	mode->scale = scaling(s, s, s);
	if (!mode->scale)
		return (0);
	mode->clip_z = no_clipping;
	mode->up = fdf->rev_translations->z_axis;
	mode->down = fdf->translations->z_axis;
	mode->forward = fdf->rev_translations->x_axis;
	mode->backward = fdf->translations->x_axis;
	mode->left = fdf->rev_translations->y_axis;
	mode->right = fdf->translations->y_axis;
	mode->perspective_hook = no_perspective;
	fdf->isometric_mode = mode;
	return (1);
}
