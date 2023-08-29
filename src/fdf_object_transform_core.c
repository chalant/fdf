/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_object_transform_core.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:42:31 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/24 13:42:31 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	transform_object(t_fdf *fdf, t_object *object, t_matrix *transform)
{
	(void)fdf;
	inplace_matmul(transform, object->body, object->result);
	inplace_matmul(transform, object->center, object->tmp);
}

void	apply_on_center(t_object *object, t_matrix *transform)
{
	inplace_matmul(object->rev_t_center, object->body, object->result);
	inplace_matmul(transform, object->body, object->result);
	inplace_matmul(object->t_center, object->body, object->result);
}
