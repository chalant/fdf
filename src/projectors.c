/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/30 12:57:54 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	*orthographic_projector(void)
{
	t_matrix	*matrix;

	matrix = homogeneous_matrix(3, 3);
	matrix->points[0][0] = 1.0f;
	matrix->points[1][1] = 1.0f;
	matrix->points[2][2] = -1.0f;
	matrix->points[0][3] = 0.0f;
	matrix->points[1][3] = 0.0f;
	matrix->points[2][3] = 0.0f;
	return (matrix);
}

t_matrix	*perspective_projector(float fov, float aspect, float znear,
		float zfar)
{
	t_matrix	*matrix;
	float		t;

	t = 1 / tanf(fov / 2.0f);
	matrix = homogeneous_matrix(3, 3);
	if (!matrix)
		return (NULL);
	matrix->points[0][0] = -aspect * t;
	matrix->points[1][1] = -t;
	matrix->points[2][2] = -zfar / (zfar - znear);
	matrix->points[2][3] = -(zfar * znear) / (zfar - znear);
	matrix->points[3][2] = 1.0f;
	matrix->points[3][3] = 0.0f;
	return (matrix);
}

t_matrix	*isometric_projector(void)
{
	t_matrix	*projector;
	t_matrix	*result;
	t_matrix	*rot;
	t_matrix	*scale;

	scale = scaling(0.5f, 1.0f, 1.0f);
	if (!scale)
		return (NULL);
	rot = rotation(0.0f, 32.264f, 45.0f);
	if (!rot)
		return (NULL);
	result = homogeneous_matrix(3, 3);
	if (!result)
		return (NULL);
	projector = orthographic_projector();
	if (!projector)
		return (NULL);
	matmul(rot, projector, result);
	inplace_matmul(scale, result, rot);
	delete_matrix(rot, rot->rows);
	delete_matrix(scale, scale->rows);
	delete_matrix(projector, projector->rows);
	return (result);
}
