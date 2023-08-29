/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/29 15:53:50 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf_mode	*delete_mode(t_fdf_mode *mode)
{
	if (!mode)
		return (NULL);
	delete_matrix(mode->projector, 4);
	delete_matrix(mode->scale, 4);
	free(mode);
	return (NULL);
}

t_transforms_3d	*delete_transforms(t_transforms_3d *transforms)
{
	if (!transforms)
		return (NULL);
	delete_matrix(transforms->x_axis, transforms->x_axis->rows);
	delete_matrix(transforms->y_axis, transforms->y_axis->rows);
	delete_matrix(transforms->z_axis, transforms->z_axis->rows);
	free(transforms);
	return (NULL);
}

t_object	*delete_object(t_object *object)
{
	if (!object)
		return (NULL);
	delete_matrix(object->body, object->body->rows);
	delete_matrix(object->center, object->center->rows);
	delete_matrix(object->result, object->result->rows);
	delete_matrix(object->tmp, object->tmp->rows);
	delete_matrix(object->transforms, object->transforms->rows);
	delete_matrix(object->rev_transforms, object->rev_transforms->rows);
	delete_matrix(object->t_center, object->t_center->rows);
	delete_matrix(object->rev_t_center, object->rev_t_center->rows);
	delete_matrix(object->projection, object->projection->rows);
	free(object->colors);
	free(object->elevations);
	free(object);
	return (NULL);
}

void	fdf_free_mlx(t_fdf *fdf)
{
	if (fdf->display->img)
		mlx_destroy_image(fdf->mlx, fdf->display->img);
	if (fdf->window)
		mlx_destroy_window(fdf->mlx, fdf->window);
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
}

int	fdf_free(t_fdf *fdf, int status)
{
	if (!fdf->map)
		return (0);
	delete_object(fdf->map);
	delete_transforms(fdf->translations);
	delete_transforms(fdf->rotations);
	delete_transforms(fdf->rev_rotations);
	delete_transforms(fdf->rev_translations);
	delete_transforms(fdf->scalings);
	delete_transforms(fdf->rev_scalings);
	delete_all_matrix(fdf->transforms);
	delete_all_matrix(fdf->tmp);
	delete_all_matrix(fdf->centering);
	delete_all_matrix(fdf->zooming_in);
	delete_all_matrix(fdf->zooming_out);
	if (fdf->isometric_mode)
		delete_mode(fdf->isometric_mode);
	if (fdf->perspective_mode)
		delete_mode(fdf->perspective_mode);
	if (fdf->ctrl)
		free(fdf->ctrl);
	if (fdf->shift)
		free(fdf->shift);
	if (fdf->command)
		free(fdf->command);
	fdf_free_mlx(fdf);
	return (status);
}
