/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:31:54 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/31 09:48:43 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	initialize_intersections(t_intersection *horizontal, t_intersection *vertical)
{
	horizontal->x = 0;
	horizontal->y = 0;
	horizontal->distance = INT_MAX;
	horizontal->hit = 0;
	horizontal->flage = 0;
	vertical->x = 0;
	vertical->y = 0;
	vertical->distance = INT_MAX;
	vertical->hit = 0;
	vertical->flage = 0;
}

double	compute_distance(t_ray ray, double x, double y)
{
	return (sqrt((ray.ray_x - x) * (ray.ray_x - x) + (ray.ray_y - y) * (ray.ray_y - y)));
}

void	update_vertical_values(t_ray ray, t_intersection *vertical, t_intersection_params params)
{
	vertical->x = params.xinter;
	vertical->y = params.yinter;
	vertical->distance = compute_distance(ray, vertical->x, vertical->y);
}

void	update_horizontal_values(t_ray ray, t_intersection *horizontal, t_intersection_params params)
{
	horizontal->x = params.xinter;
	horizontal->y = params.yinter;
	horizontal->distance = compute_distance(ray, horizontal->x, horizontal->y);
}

void	init_horizontal_values(t_ray ray, double angle, t_intersection_params *params)
{
	params->stepy = CELL_SIZE;
	params->stepx = CELL_SIZE / tan(angle);
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

void	init_vertical_values(t_ray ray, double angle, t_intersection_params *params)
{
	params->xinter = (int)(ray.ray_x / CELL_SIZE) * CELL_SIZE;
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

int check_horizontal_map_hit(t_intersection_params params, t_config *config)
{
	if (params.xinter < 0 || params.yinter < 0
		|| params.xinter >= config->map.col_len * CELL_SIZE
			|| params.yinter >= config->map.row_len * CELL_SIZE)
		return (1);
	if (config->map.map[(int)params.yinter/ CELL_SIZE]
		[(int)params.xinter / CELL_SIZE] == 'D')
		return (2);
	if (params.stepy < 0 && params.yinter >= CELL_SIZE
		&& config->map.map[(int)params.yinter/ CELL_SIZE - 1]
			[(int)params.xinter / CELL_SIZE] == 'D')
		return (2);
	if (config->map.map[(int)params.yinter/ CELL_SIZE]
		[(int)params.xinter / CELL_SIZE] == '1')
		return (1);
	if (params.stepy < 0 && params.yinter >= CELL_SIZE
		&& config->map.map[(int)params.yinter/ CELL_SIZE - 1]
			[(int)params.xinter / CELL_SIZE] == '1')
		return (1);
    return (0);
}

void	find_horizontal_intersection(t_config *config, t_ray ray, double angle, t_intersection *horizontal)
{
	t_intersection_params	params;

	init_horizontal_values(ray, angle, &params);
	while(1)
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

int check_vertical_map_hit(t_intersection_params params, t_config *config)
{
	if (params.xinter < 0 || params.yinter < 0 || params.xinter >= config->map.col_len * CELL_SIZE
		|| params.yinter >= config->map.row_len * CELL_SIZE)
		return (1);
	if (config->map.map[(int)params.yinter/ CELL_SIZE][(int)params.xinter / CELL_SIZE] == 'D')
		return (2);
	if (params.stepx < 0 && params.xinter >= CELL_SIZE
		&& config->map.map[(int)params.yinter / CELL_SIZE]
			[(int)params.xinter / CELL_SIZE - 1] == 'D')
		return (2);
	if (config->map.map[(int)params.yinter/ CELL_SIZE]
		[(int)params.xinter / CELL_SIZE] == '1')
		return (1);
	if (params.stepx < 0 && params.xinter >= CELL_SIZE
		&& config->map.map[(int)params.yinter / CELL_SIZE]
			[(int)params.xinter / CELL_SIZE - 1] == '1')
		return (1);
    return (0);
}

void	find_vertical_intersection(t_config *config, t_ray ray, double angle, t_intersection *vertical)
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

void	cast_ray(t_config *config, t_player *player, double angle, double t)
{
	t_ray			ray;
	t_intersection	horizontal;
	t_intersection	vertical;
	t_set_tex		tex_values;

	tex_values.flage = 0;
	angle = remainder(angle, M_PI * 2);
	if (angle < 0)
		angle += 2 * M_PI;
	init_ray(&ray, player, angle);
	initialize_intersections(&horizontal, &vertical);
	find_horizontal_intersection(config, ray, angle, &horizontal);
	find_vertical_intersection(config, ray, angle, &vertical);
	horizontal.distance *= cos(t);
	vertical.distance *= cos(t);
	if (horizontal.distance < vertical.distance)
	{
		tex_values.x = horizontal.x;
		tex_values.y = horizontal.y;
		tex_values.high = get_hight(horizontal.distance);
		tex_values.from = (HIGHT / 2) - tex_values.high / 2;
		tex_values.flage = horizontal.flage;
		if (horizontal.flage)
			tex_values.current_texture = &config->door;
		else if (sin(angle) > 0)
			tex_values.current_texture = &(config->nt);
		else
			tex_values.current_texture = &config->st;
	}
	else
	{
		tex_values.x = vertical.x;
		tex_values.y = vertical.y;
		tex_values.high = get_hight(vertical.distance);
		tex_values.from = (HIGHT / 2) - tex_values.high / 2;
		tex_values.flage = vertical.flage;
		if (vertical.flage)
			tex_values.current_texture = &config->door;
		else if (cos(angle) > 0)
				tex_values.current_texture = &config->et;
		else
				tex_values.current_texture = &config->wt;
	}
	draw_wall(config, &tex_values);
	config->j++;
}
