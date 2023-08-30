/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:31:54 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/30 15:53:37 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	get_hight(double dis)
{
	double	r_dis;
	double	hight;

	r_dis = (HIGHT / 2);
	hight = (r_dis * 40) / dis;
	return (hight);
}

void	from_to(double *from, double *to, double hight)
{
	*from = (HIGHT / 2) - hight / 2;
	*to = (HIGHT / 2) + hight / 2;
	if (*from < 0)
		*from = 0;
	if (*to > HIGHT)
		*to = HIGHT;
}

void	initialize_intersections(t_intersection *horizontal, t_intersection *vertical)
{
	horizontal->x = 0;
	horizontal->y = 0;
	horizontal->distance = INT_MAX;
	horizontal->hit = 0;
	vertical->x = 0;
	vertical->y = 0;
	vertical->distance = INT_MAX;
	vertical->hit = 0;
}

typedef struct s_intersection_params
{
	double	xinter;
	double	yinter;
	double	stepx;
	double	stepy;
}	t_intersection_params;

void init_horizontal_values(t_ray ray, double angle, t_intersection_params *params)
{
	params->stepy = CELL_SIZE;
	params->stepx = CELL_SIZE / tan(angle);
	params->yinter = (int)(ray.ray_y / CELL_SIZE) * CELL_SIZE;
	if (sin(angle) > 0) {
		params->stepy *= -1;
	} else {
		params->stepx *= -1;
		params->yinter += CELL_SIZE;
	}
	params->xinter = ray.ray_x + (ray.ray_y - params->yinter) / tan(angle);
}

void init_vertical_values(t_ray ray, double angle, t_intersection_params *params)
{
	params->xinter = (int)(ray.ray_x / CELL_SIZE) * CELL_SIZE;
	params->stepx = CELL_SIZE;
	params->stepy = CELL_SIZE * tan(angle);
	if (cos(angle) < 0) {
		params->stepx *= -1;
	} else {
		params->stepy *= -1;
		params->xinter += CELL_SIZE;
	}
	params->yinter = ray.ray_y + (ray.ray_x - params->xinter) * tan(angle);
}

void find_horizontal_intersection(t_config *config, t_ray ray, double angle, t_intersection *horizontal)
{
	t_intersection_params params;
	init_horizontal_values(ray, angle, &params);
	while(1)
	{
		if (params.xinter < 0 || params.yinter < 0 || params.xinter >= config->map.col_len * CELL_SIZE || params.yinter >= config->map.row_len * CELL_SIZE)
			break ;
		if (config->map.map[(int)params.yinter/ CELL_SIZE][(int)params.xinter / CELL_SIZE] == 'D')
		{
			config->flage = 1;
			break ;
		}
		if (params.stepy < 0 && params.yinter >= CELL_SIZE && config->map.map[(int)params.yinter/ CELL_SIZE - 1][(int)params.xinter / CELL_SIZE] == 'D')
		{
			config->flage = 1;
			break ;
		}
		if (config->map.map[(int)params.yinter/ CELL_SIZE][(int)params.xinter / CELL_SIZE] == '1')
			break ;
		if (params.stepy < 0 && params.yinter >= CELL_SIZE && config->map.map[(int)params.yinter/ CELL_SIZE - 1][(int)params.xinter / CELL_SIZE] == '1')
			break ;
		params.xinter += params.stepx;
		params.yinter += params.stepy;
	}
	horizontal->x = params.xinter;
	horizontal->y = params.yinter;
	horizontal->distance = sqrt((ray.ray_x - horizontal->x) * (ray.ray_x - horizontal->x) +
							(ray.ray_y - horizontal->y) * (ray.ray_y - horizontal->y)); 
}

void find_vertical_intersection(t_config *config, t_ray ray, double angle, t_intersection *vertical)
{
	t_intersection_params	params;

	init_vertical_values(ray, angle, &params);
	while (1)
	{
		if (params.xinter < 0 || params.yinter < 0 || params.xinter >= config->map.col_len * CELL_SIZE
			|| params.yinter >= config->map.row_len * CELL_SIZE)
			break ;
		if (config->map.map[(int)params.yinter/ CELL_SIZE][(int)params.xinter / CELL_SIZE] == 'D')
		{
			config->flage = 1;
			break ;
		}
		if (params.stepx < 0 && params.xinter >= CELL_SIZE && config->map.map[(int)params.yinter / CELL_SIZE][(int)params.xinter / CELL_SIZE - 1] == 'D')
		{
			config->flage = 1;
			break ;
		}
		if (config->map.map[(int)params.yinter/ CELL_SIZE][(int)params.xinter / CELL_SIZE] == '1')
			break;
		if (params.stepx < 0 && params.xinter >= CELL_SIZE && config->map.map[(int)params.yinter / CELL_SIZE][(int)params.xinter / CELL_SIZE - 1] == '1')
			break ;
		params.xinter += params.stepx;
		params.yinter += params.stepy;
	}
	vertical->x = params.xinter;
	vertical->y = params.yinter;
	vertical->distance = sqrt((ray.ray_x - vertical->x) * (ray.ray_x - vertical->x) +
							  (ray.ray_y - vertical->y) * (ray.ray_y - vertical->y));
}

void	cast_ray(t_config *config, t_player *player, double angle, double t)
{
	t_ray ray;
	t_intersection horizontal, vertical;
	t_set_tex tex_values;

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
		if (sin(angle) > 0)
			tex_values.current_texture = &(config->nt); // Nort
		else
			tex_values.current_texture = &config->st; // South
	}
	else
	{
		tex_values.x = vertical.x;
		tex_values.y = vertical.y;
		tex_values.high = get_hight(vertical.distance);
		tex_values.from = (HIGHT / 2) - tex_values.high / 2;
		if (cos(angle) > 0)
			tex_values.current_texture = &config->et; // West
		else
			tex_values.current_texture = &config->wt; // East
	}
	draw_wall(config, &tex_values);
	config->j++;
}
