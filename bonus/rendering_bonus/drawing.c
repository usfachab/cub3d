/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:24:15 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/26 10:03:43 by ysabr            ###   ########.fr       */
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
    int i = 0;
    if (config->j >= WIDTH)
        config->j = 0;
    while (i < from)
    {
        my_mlx_pixel_put(config, j, i, 0xEFDEAB);
        i++;
    }
    while (i < to)
    {
        my_mlx_pixel_put(config, j, i, 0xFFEEEE);
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
    while(i < 1000)
    {
        ray_angle = player->direction + (FOV / 2) - ((FOV / 1000) * i);
        cast_ray(config, player, ray_angle, (FOV / 2) - ((FOV / 1000) * i));
        i++;
    }
}

void draw_map_on_minimap(t_config *config)
{
    int y, x, color, cell_value;
    y = 0;
    x = 0;
    while (y < config->map.row_len * CELL_SIZE)
    {
        x = 0;
        while (x < config->map.col_len * CELL_SIZE)
        {
            cell_value = config->map.map[y / CELL_SIZE][x / CELL_SIZE];
            color = (cell_value == '1') ? COLOR_WHITE : COLOR_GREEN;
            my_mlx_pixel_put(config, x / config->mini_map_scale, y / config->mini_map_scale, color);
            x += config->mini_map_scale;
        }
        y += config->mini_map_scale;
    }
}

void draw_player_on_minimap(t_config *config)
{
    int player_minimap_x = config->player.x / config->mini_map_scale;
    int player_minimap_y = config->player.y / config->mini_map_scale;
    int py = 0, px = 0;

    while (py < 5)
    {
        px = 0;
        while (px < 5)
        {
            my_mlx_pixel_put(config, player_minimap_x + px, player_minimap_y + py, COLOR_BLACK);
            px++;
        }
        py++;
    }
}

void draw_minimap(t_config *config)
{
    draw_map_on_minimap(config);
    draw_player_on_minimap(config);
}
