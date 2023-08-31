/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:29:11 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/31 11:31:30 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_horizontal_map_hit(t_intersection_params params, t_config *config)
{
	if (params.xinter < 0 || params.yinter < 0
		|| params.xinter >= config->map.col_len * CELL_SIZE
		|| params.yinter >= config->map.row_len * CELL_SIZE)
		return (1);
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
		[(int)params.xinter / CELL_SIZE] == '1')
		return (1);
	if (params.stepx < 0 && params.xinter >= CELL_SIZE
		&& config->map.map[(int)params.yinter / CELL_SIZE]
		[(int)params.xinter / CELL_SIZE - 1] == '1')
		return (1);
	return (0);
}

void	find_horizontal_intersection(t_config *config, t_ray ray,
			double angle, t_intersection *horizontal)
{
	t_intersection_params	params;

	init_horizontal_values(ray, angle, &params);
	while (1)
	{
		if (check_horizontal_map_hit(params, config))
			break ;
		params.xinter += params.stepx;
		params.yinter += params.stepy;
	}
	update_horizontal_values(ray, horizontal, params);
}

void	find_vertical_intersection(t_config *config, t_ray ray,
			double angle, t_intersection *vertical)
{
	t_intersection_params	params;

	init_vertical_values(ray, angle, &params);
	while (1)
	{
		if (check_vertical_map_hit(params, config))
			break ;
		params.xinter += params.stepx;
		params.yinter += params.stepy;
	}
	update_vertical_values(ray, vertical, params);
}
