/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:31:54 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/31 12:04:36 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	initialize_intersections(t_intersection *horizontal,
			t_intersection *vertical)
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

void	choose_vertical_texture(t_set_tex *tex,
			t_intersection *vertical, t_config *config, double *angle)
{
	if (vertical->flage)
		tex->current_texture = &config->door;
	else if (cos(*angle) > 0)
		tex->current_texture = &config->et;
	else
		tex->current_texture = &config->wt;
}

void	set_texture_values(t_set_tex *tex_values, t_intersection *intersection)
{
	tex_values->x = intersection->x;
	tex_values->y = intersection->y;
	tex_values->high = get_hight(intersection->distance);
	tex_values->from = (HIGHT / 2) - tex_values->high / 2;
	tex_values->flage = intersection->flage;
}

void	cast_ray(t_config *config, t_player *player, double angle, double t)
{
	t_ray			ray;
	t_intersection	horizontal;
	t_intersection	vertical;
	t_set_tex		tex_values;

	angle = remainder(angle, M_PI * 2);
	if (angle < 0)
		angle += 2 * M_PI;
	init_ray(&ray, player, angle);
	initialize_intersections(&horizontal, &vertical);
	find_horizontal_intersection(config, ray, angle, &horizontal);
	find_vertical_intersection(config, ray, angle, &vertical);
	fishblow(&horizontal, &vertical, &t);
	if (horizontal.distance < vertical.distance)
	{
		set_texture_values(&tex_values, &horizontal);
		choose_horizontal_texture(&tex_values, &horizontal, config, &angle);
	}
	else
	{
		set_texture_values(&tex_values, &vertical);
		choose_vertical_texture(&tex_values, &vertical, config, &angle);
	}
	draw_wall(config, &tex_values);
	config->j++;
}
