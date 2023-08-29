/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:42:31 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/24 13:42:31 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	get_point(t_matrix *matrix, int i, int j)
{
	return (matrix->points[i][j]);
}

void	set_point(t_matrix *matrix, int i, int j, float value)
{
	matrix->points[i][j] = value;
}

float	**get_points(t_matrix *matrix)
{
	return (matrix->points);
}
