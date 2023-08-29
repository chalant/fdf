/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rendering.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:59:58 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/24 13:59:58 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_RENDERING_H
# define FDF_RENDERING_H

# define BASE_COLOR 0xFFFFFF
# define MAX_COLOR

typedef struct s_line
{
	long			s0;
	long			s1;
	long			x0;
	long			y0;
	long			x1;
	long			y1;
	long			sx;
	long			sy;
	long			dx;
	long			dy;
	long			err;
	int				fail;
	unsigned int	color0;
	unsigned int	color1;
	unsigned int	color;
}					t_line;

typedef struct s_hsl
{
	float			hue;
	float			saturation;
	float			lightness;
}					t_hsl;

void				next_line_point(t_line *line);
unsigned int		hsl_to_rgb(t_hsl *hsl);
unsigned int		fdf_gradient(float fraction, unsigned int start,
						unsigned int end);
float				fdf_color(char *point_values);

t_hsl				rgb_to_hsl(float rr, float gg, float bb);
t_line				create_line(long x0, long y0, long x1, long y1);

#endif
