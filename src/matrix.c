/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/30 12:53:55 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	*delete_matrix(t_matrix *matrix, int until)
{
	int	i;

	if (!matrix)
		return (NULL);
	i = -1;
	while (++i < until)
		free(matrix->points[i]);
	free(matrix->points);
	free(matrix);
	return (NULL);
}

float	*fdf_fill(float *vector, int size, float value)
{
	int	i;

	if (!vector)
		return (NULL);
	i = 0;
	while (i < size)
	{
		vector[i] = value;
		i++;
	}
	return (vector);
}

t_matrix	*create_matrix(int rows, int cols, float value)
{
	t_matrix	*matrix;
	int			i;

	if (cols < 0 || rows < 0)
		return (NULL);
	matrix = malloc(sizeof(t_matrix));
	if (!matrix)
		return (NULL);
	matrix->points = (float **)malloc(rows * sizeof(float *));
	if (!matrix->points)
		return (delete_matrix(matrix, 0));
	matrix->points[0] = fdf_fill((float *)malloc(cols * sizeof(float)),
			cols, value);
	i = 1;
	while (matrix->points[i - 1] && i < rows)
	{
		matrix->points[i] = fdf_fill((float *)malloc(cols * sizeof(float)),
				cols, value);
		i++;
	}
	if (!matrix->points[i - 1])
		return (delete_matrix(matrix, i));
	matrix->cols = cols;
	matrix->rows = rows;
	return (matrix);
}

t_matrix	*homogeneous_matrix(int rows, int cols)
{
	t_matrix	*matrix;

	matrix = create_matrix(rows + 1, cols + 1, 0.0f);
	if (!matrix)
		return (NULL);
	matrix->points[rows][cols] = 1.0f;
	return (matrix);
}

t_matrix	*identity_matrix(int rows, int cols)
{
	t_matrix	*matrix;

	matrix = homogeneous_matrix(rows, cols);
	if (!matrix)
		return (NULL);
	matrix->points[0][0] = 1.0f;
	matrix->points[1][1] = 1.0f;
	matrix->points[2][2] = 1.0f;
	return (matrix);
}
