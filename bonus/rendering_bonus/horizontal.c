/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:30:11 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/25 17:30:20 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

typedef struct s_horizontal_params
{
    double xinter;
    double yinter;
    double stepx;
    double stepy;
}	t_horizontal_params;

void	initialize_horizontal_intersection(t_data *data, double angle, t_ray ray, t_horizontal_params *params)
{
	params->stepy = CELL_SIZE;
	params->stepx = (CELL_SIZE / tan(angle));
	params->yinter = (int)(ray.ray_y / CELL_SIZE) * CELL_SIZE;

	if (sin(angle) > 0)
		params->stepy *= -1;
	else
	{
		params->stepx *= -1;
		params->yinter += CELL_SIZE;
	}

	params->xinter = ray.ray_x + (ray.ray_y - params->yinter) / tan(angle);
}

int check_map_boundaries_or_obstacles(t_data *data, t_horizontal_params *params)
{
	if (params->xinter < 0 || params->yinter < 0 || params->xinter >= data->map.col_len * CELL_SIZE || params->yinter >= data->map.row_len * CELL_SIZE)
		return 1;

	if (params->stepy < 0 && data->map.map[(int)params->yinter / CELL_SIZE - 1][(int)params->xinter / CELL_SIZE] == '1')
		return 1;
	else if (data->map.map[(int)params->yinter / CELL_SIZE][(int)params->xinter / CELL_SIZE] == '1')
		return 1;

	return 0;
}

double calculate_horizontal_distance(t_ray ray, t_intersection *horizontal)
{
	return sqrt((ray.ray_x - horizontal->x) * (ray.ray_x - horizontal->x) +
				(ray.ray_y - horizontal->y) * (ray.ray_y - horizontal->y));
}

void find_horizontal_intersection(t_data *data, t_ray ray, double angle, t_intersection *horizontal)
{
	t_horizontal_params params;

	initialize_horizontal_intersection(data, angle, ray, &params);

	while (!check_map_boundaries_or_obstacles(data, &params))
	{
		params.xinter += params.stepx;
		params.yinter += params.stepy;
	}

	horizontal->x = params.xinter;
	horizontal->y = params.yinter;
	horizontal->distance = calculate_horizontal_distance(ray, horizontal);
}
