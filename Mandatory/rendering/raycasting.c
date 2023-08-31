/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:31:54 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/31 11:35:44 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	choose_horizontal_texture(t_set_tex *tex,
			t_config *config, double *angle)
{
	if (sin(*angle) > 0)
		tex->current_texture = &(config->nt);
	else
		tex->current_texture = &config->st;
}

void	choose_vertical_texture(t_set_tex *tex,
			t_config *config, double *angle)
{
	if (cos(*angle) > 0)
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
		choose_horizontal_texture(&tex_values, config, &angle);
	}
	else
	{
		set_texture_values(&tex_values, &vertical);
		choose_vertical_texture(&tex_values, config, &angle);
	}
	draw_wall(config, &tex_values);
	config->j++;
}
