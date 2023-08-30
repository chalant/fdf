/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/30 13:04:34 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_init(t_fdf *fdf)
{
	fdf->mlx = NULL;
	fdf->window = NULL;
	fdf->isometric_mode = NULL;
	fdf->perspective_mode = NULL;
	fdf->ctrl = NULL;
	fdf->shift = NULL;
	fdf->command = NULL;
	fdf->rotations = NULL;
	fdf->translations = NULL;
	fdf->rev_rotations = NULL;
	fdf->rev_translations = NULL;
	fdf->scalings = NULL;
	fdf->rev_scalings = NULL;
	fdf->transforms = NULL;
	fdf->centering = NULL;
	fdf->tmp = NULL;
	fdf->zooming_in = NULL;
	fdf->zooming_out = NULL;
	fdf->map = NULL;
	fdf->display = NULL;
	return (1);
}
