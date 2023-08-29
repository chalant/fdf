/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_loading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychalant <ychalant@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:53:50 by ychalant          #+#    #+#             */
/*   Updated: 2023/08/29 15:53:50 by ychalant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_values(char *line)
{
	char	**numbers;
	int		i;

	i = 0;
	numbers = ft_split(line, ' ');
	while (numbers[i])
		i++;
	delete_strings(numbers);
	return (i);
}

int	count_points(int fd, t_object *map)
{
	char	*line;
	int		lines;
	int		line_len;

	if (fd < 0)
		return (-1);
	lines = 0;
	line = get_next_line(fd);
	if (!line)
		return (-1);
	line_len = count_values(line);
	map->width = line_len;
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (lines * line_len);
}

int	init_center(t_object *object)
{
	object->center = homogeneous_matrix(3, 0);
	if (!object->center)
		return (0);
	object->t_center = translation(1.0f, 1.0f, 1.0f);
	if (!object->t_center)
		return (0);
	object->rev_t_center = translation(-1.0f, -1.0f, -1.0f);
	if (!object->rev_t_center)
		return (0);
	object->tmp = homogeneous_matrix(3, 0);
	if (!object->tmp)
		return (0);
	object->center->points[0][0] = (float)object->height / 2.0f;
	object->center->points[1][0] = (float)object->width / 2.0f;
	object->center->points[2][0] = 0.0f;
	return (1);
}

int	init_object(t_object *object)
{
	object->result = homogeneous_matrix(3, object->body->cols - 1);
	if (!object->result)
		return (0);
	object->projection = homogeneous_matrix(3, object->body->cols - 1);
	if (!object->projection)
		return (0);
	object->transforms = identity_matrix(3, 3);
	if (!object->transforms)
		return (0);
	object->rev_transforms = identity_matrix(3, 3);
	if (!object->rev_transforms)
		return (0);
	object->shape[0] = object->width;
	object->shape[1] = object->height;
	return (1);
}

t_object	*load_object(char *file_path)
{
	t_object	*map;
	int			fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_object));
	if (!map)
		return (NULL);
	map->body = create_matrix(4, count_points(fd, map), 1.0f);
	if (!map->body)
		return (NULL);
	map->colors = malloc(sizeof(float) * map->body->cols);
	if (!map->colors)
		return (NULL);
	map->elevations = malloc(sizeof(float) * map->body->cols);
	if (!map->elevations)
		return (NULL);
	if (!fill_map(file_path, map))
		return (NULL);
	if (!init_center(map))
		return (NULL);
	if (!init_object(map))
		return (NULL);
	return (map);
}
