/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_object_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/29 15:53:50 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rotation_hook(int code, t_fdf *fdf)
{
	if (code == RL && fdf->shift->pressed)
		rotate_object(fdf, fdf->map, fdf->rev_rotations->z_axis,
				fdf->rotations->z_axis);
	else if (code == RR && fdf->shift->pressed)
		rotate_object(fdf, fdf->map, fdf->rotations->z_axis,
				fdf->rev_rotations->z_axis);
	else if (code == RU)
		rotate_object(fdf, fdf->map, fdf->rev_rotations->y_axis,
				fdf->rotations->y_axis);
	else if (code == RL)
		rotate_object(fdf, fdf->map, fdf->rev_rotations->x_axis,
				fdf->rotations->x_axis);
	else if (code == RR)
		rotate_object(fdf, fdf->map, fdf->rotations->x_axis,
				fdf->rev_rotations->x_axis);
	else if (code == RD)
		rotate_object(fdf, fdf->map, fdf->rotations->y_axis,
				fdf->rev_rotations->y_axis);
	return (1);
}

int	scaling_hook(int code, t_fdf *fdf)
{
	if (code == RL)
		scale_object(fdf, fdf->map, fdf->scalings->y_axis);
	else if (code == RR)
		scale_object(fdf, fdf->map, fdf->rev_scalings->y_axis);
	else if (code == RU && fdf->shift->pressed)
		scale_object(fdf, fdf->map, fdf->scalings->z_axis);
	else if (code == RD && fdf->shift->pressed)
		scale_object(fdf, fdf->map, fdf->rev_scalings->z_axis);
	else if (code == RU)
		scale_object(fdf, fdf->map, fdf->rev_scalings->x_axis);
	else if (code == RD)
		scale_object(fdf, fdf->map, fdf->scalings->x_axis);
	return (1);
}

int	translation_hook(int code, t_fdf *fdf)
{
	t_fdf_mode	*mode;

	mode = fdf->mode;
	if (code == TR)
		translate_object(fdf, fdf->map, mode->right, mode->left);
	else if (code == TU && fdf->shift->pressed)
		translate_object(fdf, fdf->map, mode->up, mode->down);
	else if (code == TD && fdf->shift->pressed)
		translate_object(fdf, fdf->map, mode->down, mode->up);
	else if (code == TU)
		translate_object(fdf, fdf->map, mode->forward, mode->backward);
	else if (code == TD)
		translate_object(fdf, fdf->map, mode->backward, mode->forward);
	else if (code == TL)
		translate_object(fdf, fdf->map, mode->left, mode->right);
	return (1);
}
