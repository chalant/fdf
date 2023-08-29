/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/29 15:53:50 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <limits.h>

void	fdf_pixel_put(t_display *display, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || y <= 0)
		return ;
	if (x >= display->width || y >= display->height)
		return ;
	dst = display->addr + (y * display->line_length + x
			* (display->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_line	create_line(long x0, long y0, long x1, long y1)
{
	t_line	line;

	line.s0 = x0;
	line.s1 = y0;
	line.x0 = x0;
	line.x1 = x1;
	line.y0 = y0;
	line.y1 = y1;
	line.dx = fdf_labs(x1 - x0);
	line.dy = fdf_labs(y1 - y0);
	line.sx = (x0 < x1) * 1 + (x0 >= x1) * -1;
	line.sy = (y0 < y1) * 1 + (y0 >= y1) * -1;
	line.err = line.dx - line.dy;
	return (line);
}

void	next_line_point(t_line *line)
{
	int	delta;

	delta = 2 * line->err;
	if (delta > -line->dy)
	{
		line->err -= line->dy;
		line->x0 += line->sx;
	}
	if (delta < line->dx)
	{
		line->err += line->dx;
		line->y0 += line->sy;
	}
}

float	compute_ratio(int start, int end, int current)
{
	float	placement;
	float	distance;

	distance = (float)(end - start);
	if (distance == 0)
		return (1.0f);
	placement = (float)(current - start);
	return (placement / distance);
}

void	plot_line(t_display *display, int color, t_line *line)
{
	while (1)
	{
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		if (line->dx > line->dy)
			color = fdf_gradient(compute_ratio(line->s0, line->x1, line->x0),
									line->color0,
									line->color1);
		else
			color = fdf_gradient(compute_ratio(line->s1, line->y1, line->y0),
									line->color0,
									line->color1);
		fdf_pixel_put(display, line->x0, line->y0, color);
		next_line_point(line);
	}
}
