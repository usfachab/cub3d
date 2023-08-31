/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:22:25 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/31 12:04:05 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	choose_horizontal_texture(t_set_tex *tex,
			t_intersection *horizontal, t_config *config, double *angle)
{
	if (horizontal->flage)
		tex->current_texture = &config->door;
	else if (sin(*angle) > 0)
		tex->current_texture = &(config->nt);
	else
		tex->current_texture = &config->st;
}

double	compute_distance(t_ray ray, double x, double y)
{
	return (sqrt((ray.ray_x - x) * (ray.ray_x - x)
			+ (ray.ray_y - y) * (ray.ray_y - y)));
}

void	fishblow(t_intersection *horizontal,
			t_intersection *vertical, double *t)
{
	horizontal->distance *= cos(*t);
	vertical->distance *= cos(*t);
}

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
