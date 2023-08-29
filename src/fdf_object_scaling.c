/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_object_scaling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/29 15:53:50 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_scaling_transforms(t_fdf *fdf, t_object *object,
		t_matrix *transform)
{
	t_matrix	*target;

	target = object->transforms;
	inplace_matmul(transform, target, fdf->tmp);
}

void	to_model_space(t_object *object)
{
	inplace_matmul(object->rev_transforms, object->body, object->result);
	inplace_matmul(object->rev_transforms, object->center, object->tmp);
}

void	from_model_space(t_object *object)
{
	inplace_matmul(object->transforms, object->body, object->result);
	inplace_matmul(object->transforms, object->center, object->tmp);
}

void	scale_object(t_fdf *fdf, t_object *object, t_matrix *transform)
{
	float	elevation;
	float	width;
	float	height;

	to_model_space(fdf->map);
	elevation = fabs(object->body->points[2][object->max_elevation_idx]
			* transform->points[2][2]);
	height = fabs(object->body->points[1][object->body->cols - 1])
		* transform->points[1][1];
	width = fabs(object->body->points[0][object->body->cols - 1])
		* transform->points[0][0];
	if (elevation > 0.01f && elevation < 2.0f && width > 0.3f && width < 3.0f
		&& height > 0.3f && height < 3.0f)
	{
		inplace_matmul(transform, object->body, object->result);
		inplace_matmul(transform, object->center, object->tmp);
	}
	if (elevation > 2.0f && transform->points[2][2] > 0.0f)
	{
		inplace_matmul(transform, object->body, object->result);
		inplace_matmul(transform, object->center, object->tmp);
	}
	from_model_space(fdf->map);
}
