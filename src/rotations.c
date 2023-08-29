/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:42:31 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/24 13:42:31 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_matrix	*delete_all_rots(t_matrix *a, t_matrix *b, t_matrix *c)
{
	delete_matrix(a, a->rows);
	delete_matrix(b, b->rows);
	delete_matrix(c, c->rows);
	return (NULL);
}

t_matrix	*x_rotation(float angle)
{
	t_matrix	*matrix;

	angle = to_rad(angle);
	matrix = homogeneous_matrix(3, 3);
	if (!matrix)
		return (NULL);
	matrix->points[0][0] = 1.0f;
	matrix->points[1][1] = cosf(angle);
	matrix->points[1][2] = sinf(angle);
	matrix->points[2][1] = -sinf(angle);
	matrix->points[2][2] = cosf(angle);
	return (matrix);
}

t_matrix	*y_rotation(float angle)
{
	t_matrix	*matrix;

	angle = to_rad(angle);
	matrix = homogeneous_matrix(3, 3);
	if (!matrix)
		return (NULL);
	matrix->points[0][0] = cosf(angle);
	matrix->points[0][2] = -sinf(angle);
	matrix->points[1][1] = 1.0f;
	matrix->points[2][0] = sinf(angle);
	matrix->points[2][2] = cosf(angle);
	return (matrix);
}

t_matrix	*z_rotation(float angle)
{
	t_matrix	*matrix;

	angle = to_rad(angle);
	matrix = homogeneous_matrix(3, 3);
	if (!matrix)
		return (NULL);
	matrix->points[0][0] = cosf(angle);
	matrix->points[0][1] = -sinf(angle);
	matrix->points[1][0] = sinf(angle);
	matrix->points[1][1] = cosf(angle);
	matrix->points[2][2] = 1.0f;
	return (matrix);
}

t_matrix	*rotation(float x, float y, float z)
{
	t_matrix	*x_rot;
	t_matrix	*y_rot;
	t_matrix	*z_rot;
	t_matrix	*result;

	x_rot = x_rotation(x);
	if (!x_rot)
		return (NULL);
	y_rot = y_rotation(y);
	if (!y_rot)
		return (delete_all_rots(x_rot, NULL, NULL));
	z_rot = z_rotation(z);
	if (!z_rot)
		return (delete_all_rots(x_rot, y_rot, NULL));
	result = homogeneous_matrix(3, 3);
	if (!result)
		return (delete_all_rots(x_rot, y_rot, z_rot));
	matmul(x_rot, y_rot, result);
	matmul(result, z_rot, y_rot);
	delete_matrix(x_rot, x_rot->rows);
	delete_matrix(z_rot, z_rot->rows);
	delete_matrix(result, result->rows);
	return (y_rot);
}
