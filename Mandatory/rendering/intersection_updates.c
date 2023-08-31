/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_updates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:28:06 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/31 11:28:52 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_vertical_values(t_ray ray, t_intersection *vertical,
			t_intersection_params params)
{
	vertical->x = params.xinter;
	vertical->y = params.yinter;
	vertical->distance = compute_distance(ray, vertical->x, vertical->y);
}

void	update_horizontal_values(t_ray ray, t_intersection *horizontal,
			t_intersection_params params)
{
	horizontal->x = params.xinter;
	horizontal->y = params.yinter;
	horizontal->distance = compute_distance(ray, horizontal->x, horizontal->y);
}

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

void	init_vertical_values(t_ray ray, double angle,
			t_intersection_params *params)
{
	params->xinter = (int)(ray.ray_x / CELL_SIZE) *CELL_SIZE;
	params->stepx = CELL_SIZE;
	params->stepy = CELL_SIZE * tan(angle);
	if (cos(angle) < 0)
		params->stepx *= -1;
	else
	{
		params->stepy *= -1;
		params->xinter += CELL_SIZE;
	}
	params->yinter = ray.ray_y + (ray.ray_x - params->xinter) * tan(angle);
}
