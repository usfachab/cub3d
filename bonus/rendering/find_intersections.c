/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:29:11 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/31 12:05:10 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_horizontal_values(t_ray ray, double angle,
			t_intersection_params *params)
{
	params->stepy = CELL_SIZE;
	params->stepx = CELL_SIZE / tan(angle);
	params->yinter = (int)(ray.ray_y / CELL_SIZE) *CELL_SIZE;
	if (sin(angle) > 0)
		params->stepy *= -1;
	else
	{
		params->stepx *= -1;
		params->yinter += CELL_SIZE;
	}
	params->xinter = ray.ray_x + (ray.ray_y - params->yinter) / tan(angle);
}

int	check_horizontal_map_hit(t_intersection_params params, t_config *config)
{
	if (params.xinter < 0 || params.yinter < 0
		|| params.xinter >= config->map.col_len * CELL_SIZE
		|| params.yinter >= config->map.row_len * CELL_SIZE)
		return (1);
	if (config->map.map[(int)params.yinter / CELL_SIZE]
		[(int)params.xinter / CELL_SIZE] == 'D')
		return (2);
	if (params.stepy < 0 && params.yinter >= CELL_SIZE
		&& config->map.map[(int)params.yinter / CELL_SIZE - 1]
		[(int)params.xinter / CELL_SIZE] == 'D')
		return (2);
	if (config->map.map[(int)params.yinter / CELL_SIZE]
		[(int)params.xinter / CELL_SIZE] == '1')
		return (1);
	if (params.stepy < 0 && params.yinter >= CELL_SIZE
		&& config->map.map[(int)params.yinter / CELL_SIZE - 1]
		[(int)params.xinter / CELL_SIZE] == '1')
		return (1);
	return (0);
}

int	check_vertical_map_hit(t_intersection_params params, t_config *config)
{
	if (params.xinter < 0 || params.yinter < 0
		|| params.xinter >= config->map.col_len * CELL_SIZE
		|| params.yinter >= config->map.row_len * CELL_SIZE)
		return (1);
	if (config->map.map[(int)params.yinter / CELL_SIZE]
		[(int)params.xinter / CELL_SIZE] == 'D')
		return (2);
	if (params.stepx < 0 && params.xinter >= CELL_SIZE
		&& config->map.map[(int)params.yinter / CELL_SIZE]
		[(int)params.xinter / CELL_SIZE - 1] == 'D')
		return (2);
	if (config->map.map[(int)params.yinter / CELL_SIZE]
		[(int)params.xinter / CELL_SIZE] == '1')
		return (1);
	if (params.stepx < 0 && params.xinter >= CELL_SIZE
		&& config->map.map[(int)params.yinter / CELL_SIZE]
		[(int)params.xinter / CELL_SIZE - 1] == '1')
		return (1);
	return (0);
}

void	find_vertical_intersection(t_config *config, t_ray ray,
			double angle, t_intersection *vertical)
{
	t_intersection_params	params;

	init_vertical_values(ray, angle, &params);
	while (1)
	{
		if (check_vertical_map_hit(params, config))
		{
			if (check_vertical_map_hit(params, config) == 2)
			{
				vertical->flage = 1;
				break ;
			}
			else
				break ;
		}
		params.xinter += params.stepx;
		params.yinter += params.stepy;
	}
	update_vertical_values(ray, vertical, params);
}

void	find_horizontal_intersection(t_config *config, t_ray ray,
			double angle, t_intersection *horizontal)
{
	t_intersection_params	params;

	init_horizontal_values(ray, angle, &params);
	while (1)
	{
		if (check_horizontal_map_hit(params, config))
		{
			if (check_horizontal_map_hit(params, config) == 2)
			{
				horizontal->flage = 1;
				break ;
			}
			else
				break ;
		}
		params.xinter += params.stepx;
		params.yinter += params.stepy;
	}
	update_horizontal_values(ray, horizontal, params);
}
