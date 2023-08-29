/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_object_rotation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:42:31 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/24 13:42:31 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_rotate_transforms(t_fdf *fdf, t_object *object, t_matrix *transform)
{
	t_matrix	*target;

	target = object->transforms;
	inplace_matmul(object->rev_t_center, target, fdf->tmp);
	inplace_matmul(transform, target, fdf->tmp);
	inplace_matmul(object->t_center, target, fdf->tmp);
}

void	set_inverse_rotate_transforms(t_fdf *fdf, t_object *object,
		t_matrix *rev_transform)
{
	t_matrix	*target;

	target = object->rev_transforms;
	matmul(target, object->t_center, fdf->tmp);
	matrix_copy(fdf->tmp, target);
	matmul(target, rev_transform, fdf->tmp);
	matrix_copy(fdf->tmp, target);
	matmul(target, object->rev_t_center, fdf->tmp);
	matrix_copy(fdf->tmp, target);
}

void	rotate_object(t_fdf *fdf, t_object *object, t_matrix *transform,
		t_matrix *rev_transform)
{
	(void)object;
	apply_on_center(fdf->map, transform);
	set_rotate_transforms(fdf, fdf->map, transform);
	set_inverse_rotate_transforms(fdf, fdf->map, rev_transform);
}
