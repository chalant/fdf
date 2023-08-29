#include "fdf.h"

int	fdf_init(t_fdf *fdf)
{
	fdf->map = NULL;
	fdf->mlx = NULL;
	fdf->window = NULL;
	fdf->display = NULL;
	fdf->transforms = NULL;
	fdf->tmp = NULL;
	fdf->centering = NULL;
	fdf->isometric_mode = NULL;
	fdf->perspective_mode = NULL;
	fdf->ctrl = NULL;
	fdf->shift = NULL;
	fdf->command = NULL;
	fdf->rotations = NULL;
	fdf->translations = NULL;
	fdf->rev_translations = NULL;
	fdf->rev_rotations = NULL;
	fdf->scalings = NULL;
	fdf->rev_scalings = NULL;
	fdf->zooming_in = NULL;
	fdf->zooming_out = NULL;
	return (1);
}
