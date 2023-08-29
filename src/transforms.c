/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:42:31 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/24 13:42:31 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	*translation(float x, float y, float z)
{
	t_matrix	*trans;

	trans = homogeneous_matrix(3, 3);
	if (!trans)
		return (NULL);
	trans->points[0][3] = x;
	trans->points[1][3] = y;
	trans->points[2][3] = z;
	trans->points[0][0] = 1.0;
	trans->points[1][1] = 1.0;
	trans->points[2][2] = 1.0;
	return (trans);
}

t_matrix	*scaling(float x, float y, float z)
{
	t_matrix	*scale;

	scale = homogeneous_matrix(3, 3);
	if (!scale)
		return (NULL);
	scale->points[0][0] = x;
	scale->points[1][1] = y;
	scale->points[2][2] = z;
	return (scale);
}
