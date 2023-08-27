/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:21:37 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/27 18:10:58 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void my_mlx_pixel_put(t_config *config, int x, int y, int color)
{
	char *dst;

	dst = config->data.addr + (y * config->data.line_length + x * (config->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int    draw_texture(t_config *config, int x, int y)
{
	char *dst;

	dst = config->data.addr + (y * config->data.line_length + x * (config->data.bits_per_pixel / 8));
	return *(unsigned int *)dst;
}

void draw_wall(t_config *config, t_set_tex *tex_values)
{
    tex_values->i = 0;
    double from = tex_values->from;
    double to = from + tex_values->high;

	tex_values->to = to;
	config->color = 0;
    while (tex_values->i < from && tex_values->i < HIGHT)
    {
        my_mlx_pixel_put(config, config->j, tex_values->i, config->ceiling_rgb);
        tex_values->i++;
    }
    while (tex_values->i < to && tex_values->i < HIGHT)
    {
		//you must call your function here and set the value on config color so you must return unsigned int
        // config->color = draw_texture(config, j, i);
		my_mlx_pixel_put(config, config->j, tex_values->i, config->color);
        tex_values->i++;
    }
    while (tex_values->i < HIGHT)
    {
        my_mlx_pixel_put(config, config->j, tex_values->i, config->floor_rgb);
        tex_values->i++;
    }
}


void draw_player(t_config *config, t_player *player)
{
	int player_size = PLAYER_SIZE;
	int y = player->y - player_size / 2;
	while (y <= player->y + player_size / 2)
	{
		int x = player->x - player_size / 2;
		while (x <= player->x + player_size / 2)
		{
			my_mlx_pixel_put(config, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

void render_rays(t_config *config, t_player *player)
{
	int i = 0;
	double ray_angle;
	config->j = 0;
	while(i < WIDTH)
	{
		ray_angle = player->direction + (FOV / 2) - ((FOV / 1000) * i);
		cast_ray(config, player, ray_angle, (FOV / 2) - ((FOV / 1000) * i));
		i++;
	}
}
