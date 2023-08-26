/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:24:15 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/26 17:03:18 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void my_mlx_pixel_put(t_config *config, int x, int y, int color)
{
	char *dst;

	dst = config->data.addr + (y * config->data.line_length + x * (config->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_wall(t_config *config, double from, double to, int j)
{
	int	i;

	i = 0;
	while (i < from && i < HIGHT)
	{
		my_mlx_pixel_put(config, j, i, 0xEFDEAB);
		i++;
	}
	while (i < to && i < HIGHT)
	{
		my_mlx_pixel_put(config, j, i, config->color);
		i++;
	}
	while (i < HIGHT)
	{
		my_mlx_pixel_put(config, j, i, 0x0F0FF0);
		i++;
	}
}

void clear_window(t_config *config)
{
    int x, y;
    y = -1;
    while (++y < HIGHT)
    {
        x = -1;
        while (++x < WIDTH)
            my_mlx_pixel_put(config, x, y, 0x000000);
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
    while(i < 1000)
    {
        ray_angle = player->direction + (FOV / 2) - ((FOV / 1000) * i);
        cast_ray(config, player, ray_angle, (FOV / 2) - ((FOV / 1000) * i));
        i++;
    }
}
