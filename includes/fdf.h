/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:54:53 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/30 14:45:35 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "fdf_bindings.h"
# include "fdf_controls.h"
# include "fdf_rendering.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "matrix.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>

# define WORLD 0
# define VIEW 1

typedef struct s_object
{
	t_matrix		*transforms;
	t_matrix		*rev_transforms;
	t_matrix		*body;
	t_matrix		*result;
	t_matrix		*projection;
	t_matrix		*center;
	t_matrix		*t_center;
	t_matrix		*rev_t_center;
	t_matrix		*tmp;

	float			*elevations;
	float			max_elevation;
	float			min_elevation;
	float			*colors;
	int				light;
	float			base_color;
	float			intensity;
	float			lightness;
	float			light_base;
	float			saturation;
	float			sat_base;
	int				max_elevation_idx;
	int				width;
	int				height;
	int				shape[2];
}					t_object;

typedef struct s_transforms_3d
{
	t_matrix		*x_axis;
	t_matrix		*y_axis;
	t_matrix		*z_axis;
}					t_transforms_3d;

typedef struct s_display
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_display;

typedef struct s_fdf_mode
{
	t_matrix		*projector;
	t_matrix		*scale;

	int				(*perspective_hook)(t_object *object);
	int				(*clip_z)(float value);
	t_matrix		*left;
	t_matrix		*right;
	t_matrix		*up;
	t_matrix		*down;
	t_matrix		*forward;
	t_matrix		*backward;

}					t_fdf_mode;

typedef struct s_fdf_space
{
	t_matrix		*body;
	t_matrix		*tmp;
}					t_fdf_space;

typedef struct s_fdf
{
	void			*mlx;
	void			*window;

	t_fdf_mode		*mode;
	t_fdf_mode		*isometric_mode;
	t_fdf_mode		*perspective_mode;

	int				space;
	int				world;
	int				view;

	t_fdf_key		*ctrl;
	t_fdf_key		*shift;
	t_fdf_key		*command;

	t_transforms_3d	*rotations;
	t_transforms_3d	*translations;
	t_transforms_3d	*rev_rotations;
	t_transforms_3d	*rev_translations;
	t_transforms_3d	*scalings;
	t_transforms_3d	*rev_scalings;

	t_matrix		*transforms;
	t_matrix		*centering;
	t_matrix		*tmp;
	t_matrix		*zooming_in;
	t_matrix		*zooming_out;

	t_object		*map;

	t_display		*display;

}					t_fdf;

float				to_rad(float angle);
long				fdf_labs(long n);

int					fdf_init(t_fdf *fdf);
int					fdf_free(t_fdf *fdf, int status);
void				delete_all_matrix(t_matrix *matrix);

void				delete_strings(char **numbers);
void				transform_object(t_fdf *fdf, t_object *object,
						t_matrix *transform);
void				apply_on_center(t_object *object, t_matrix *transform);
void				set_translate(t_matrix *matrix, float x, float y, float z);
void				set_translate_transform(t_fdf *fdf, t_object *object,
						t_matrix *transform);
void				set_inv_translate_transform(t_fdf *fdf, t_object *object,
						t_matrix *rev_transform);

int					normalize_object(t_fdf *fdf, t_object *object);

int					fill_points(t_object *object, char *line, int x, int *z);
int					fill_map(char *file_path, t_object *object);

int					set_rotations(t_fdf *fdf, float x, float y, float z);
int					set_translations(t_fdf *fdf, float x, float y, float z);
int					set_scalings(t_fdf *fdf, float x, float y, float z);
int					set_zooming(t_fdf *fdf, float value);

int					rotation_hook(int code, t_fdf *fdf);
int					translation_hook(int code, t_fdf *fdf);
int					scaling_hook(int code, t_fdf *fdf);
int					zooming_hook(int code, t_fdf *fdf);
int					view_translation_hook(int code, t_fdf *fdf);

int					close_program(t_fdf *fdf);
int					handle_expose(t_fdf *fdf);

int					key_press_hook(int code, t_fdf *fdf);
int					key_release_hook(int code, t_fdf *fdf);

int					create_perspective_mode(t_fdf *fdf);
int					create_isometric_mode(t_fdf *fdf);

int					fdf_object_color(t_object *object);

void				fdf_increment_limit(float *target, float incr, float low,
						float high);
void				fdf_draw_grid(t_fdf_mode *mode, t_display *display,
						t_object *object, int shape[2]);

void				rotate_object(t_fdf *fdf, t_object *object,
						t_matrix *transform, t_matrix *rev_transform);
void				translate_object(t_fdf *fdf, t_object *object,
						t_matrix *trs, t_matrix *inv);
void				scale_object(t_fdf *fdf, t_object *object,
						t_matrix *transform);

void				fdf_pixel_put(t_display *display, int x, int y, int color);
void				draw_object(t_fdf_mode *mode, t_display *display,
						t_object *object);
void				plot_line(t_display *data, int color, t_line *line);
int					update_view(t_fdf *fdf);

t_matrix			*z_rotation(float angle);
t_matrix			*y_rotation(float angle);
t_matrix			*x_rotation(float angle);
t_matrix			*rotation(float x, float y, float z);
t_matrix			*translation(float x, float y, float z);
t_matrix			*scaling(float x, float y, float z);

t_matrix			*perspective_projector(float fov, float aspect, float znear,
						float zfar);
t_matrix			*isometric_projector(void);
t_matrix			*orthographic_projector(void);
t_matrix			*create_matrix(int rows, int cols, float value);
t_matrix			*delete_matrix(t_matrix *matrix, int until);
t_matrix			*homogeneous_matrix(int rows, int cols);
t_object			*load_object(char *file_path);

t_line				create_next_edge(t_object *object, int i, int d);

#endif
