/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_object_normalization.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:42:31 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/24 13:42:31 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	scale_and_center(t_fdf *fdf, t_object *object)
{
	t_matrix	*trsl;
	t_matrix	*scale;
	float		ratio;

	if (object->width < object->height)
		ratio = (float)object->width;
	else
		ratio = (float)object->height;
	scale = scaling(1.0f / ratio, 1.0f / ratio, -1.0f / ratio);
	if (!scale)
		return (0);
	transform_object(fdf, object, scale);
	trsl = translation(-object->center->points[0][0],
			-object->center->points[1][0], 2.0f);
	if (!trsl)
	{
		delete_matrix(scale, scale->rows);
		return (0);
	}
	transform_object(fdf, object, trsl);
	delete_matrix(trsl, trsl->rows);
	delete_matrix(scale, scale->rows);
	return (1);
}

int	object_space(t_fdf *fdf, t_object *object)
{
	float		cx;
	float		cy;
	float		cz;
	t_matrix	*trsl;
	t_matrix	*inv_trsl;

	trsl = translation(0.0f, 0.0f, 2.0f);
	if (!trsl)
		return (0);
	inv_trsl = translation(0.0f, 0.0f, -2.0f);
	if (!inv_trsl)
	{
		delete_matrix(trsl, trsl->rows);
		return (0);
	}
	cx = get_point(object->center, 0, 0);
	cy = get_point(object->center, 1, 0);
	cz = get_point(object->center, 2, 0);
	set_translate(object->t_center, cx, cy, cz);
	set_translate(object->rev_t_center, -cx, -cy, -cz);
	set_translate_transform(fdf, object, trsl);
	set_inv_translate_transform(fdf, object, inv_trsl);
	delete_matrix(trsl, trsl->rows);
	delete_matrix(inv_trsl, inv_trsl->rows);
	return (1);
}

int	normalize_object(t_fdf *fdf, t_object *object)
{
	if (!scale_and_center(fdf, object))
		return (0);
	if (!object_space(fdf, object))
		return (0);
	return (1);
}
