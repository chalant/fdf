/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_perspective_mode.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/30 13:00:30 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	perspective_divide(t_object *object)
{
	int			j;
	float		w;
	t_matrix	*mat;

	j = -1;
	mat = object->projection;
	while (++j < mat->cols)
	{
		w = mat->points[3][j];
		if (fabsf(w) > 0.00001f)
		{
			mat->points[0][j] /= w;
			mat->points[1][j] /= w;
			mat->points[3][j] = 1.0f;
		}
	}
	return (1);
}

static int	clipping_cond(float value)
{
	if (value > 0.0f)
		return (1);
	return (0);
}

int	create_perspective_mode(t_fdf *fdf)
{
	t_fdf_mode	*mode;
	t_display	*display;
	float		scl;

	mode = malloc(sizeof(t_fdf_mode));
	if (!mode)
		return (0);
	display = fdf->display;
	scl = 100.0f * (float)display->width / (float)display->height;
	mode->projector = perspective_projector(100.0f, 1.0f, -1.0f, 1.0f);
	if (!mode->projector)
		return (0);
	mode->scale = scaling(scl, scl, scl);
	if (!mode->scale)
		return (0);
	mode->clip_z = clipping_cond;
	mode->forward = fdf->rev_translations->z_axis;
	mode->backward = fdf->translations->z_axis;
	mode->left = fdf->rev_translations->y_axis;
	mode->right = fdf->translations->y_axis;
	mode->up = fdf->rev_translations->x_axis;
	mode->down = fdf->translations->x_axis;
	mode->perspective_hook = perspective_divide;
	fdf->perspective_mode = mode;
	return (1);
}
