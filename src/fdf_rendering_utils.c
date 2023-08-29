/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rendering_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:42:31 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/24 13:42:31 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_line	create_next_edge(t_object *object, int i, int index)
{
	float	**points;

	points = get_points(object->projection);
	return (create_line(points[1][i], points[0][i], points[1][i + index],
			points[0][i + index]));
}

void	compute_hsl(t_hsl *hsl, t_object *object, int index)
{
	int		l;
	float	mel;

	mel = object->max_elevation;
	l = object->light;
	hsl->hue = fabs(fmod(object->base_color + object->colors[index]
				+ (object->elevations[index]
					* object->intensity / mel), 360.0f));
	hsl->lightness = object->lightness * (1 - l) + l * object->lightness
		* (object->elevations[index] + mel + object->light_base)
		/ (2 * mel + object->light_base);
	hsl->saturation = object->saturation;
}

void	fdf_draw_line(t_object *object, t_display *display, int i, int d)
{
	t_line	line;
	t_hsl	hsl;
	int		index;

	index = (1 - d) + d * object->shape[0];
	line = create_next_edge(object, i, index);
	compute_hsl(&hsl, object, i);
	line.color0 = hsl_to_rgb(&hsl);
	compute_hsl(&hsl, object, i + index);
	line.color1 = hsl_to_rgb(&hsl);
	plot_line(display, object->colors[i], &line);
}

static inline void	increment_shape(t_object *object, int shape[2])
{
	shape[0]++;
	if (shape[0] >= object->shape[0])
	{
		shape[0] = 0;
		shape[1]++;
	}
}

void	fdf_draw_grid(t_fdf_mode *mode, t_display *display, t_object *object,
		int shape[2])
{
	t_matrix	*projection;
	int			i;

	projection = object->projection;
	i = 0;
	while (i < projection->cols - 1)
	{
		if (shape[0] < object->shape[0] - 1 && i + 1 < projection->cols
			&& mode->clip_z(object->body->points[2][i])
			&& mode->clip_z(object->body->points[2][i + 1]))
			fdf_draw_line(object, display, i, 0);
		if (shape[1] < object->shape[1] && i
			+ object->shape[0] < projection->cols
			&& mode->clip_z(object->body->points[2][i])
			&& mode->clip_z(object->body->points[2][i + object->shape[0]]))
			fdf_draw_line(object, display, i, 1);
		increment_shape(object, shape);
		i++;
	}
}
