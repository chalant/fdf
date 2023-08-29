/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_object_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:42:31 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/24 13:42:31 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_object_color(t_object *object)
{
	object->intensity = 0.0f;
	object->base_color = 0.0f;
	object->saturation = 0.5f;
	object->light_base = 0.5f;
	object->lightness = 0.5f;
	object->light = 1;
	return (1);
}

void	fdf_increment_limit(float *target, float incr, float low, float high)
{
	if (*target + incr < high && *target + incr >= low)
		*target += incr;
}
