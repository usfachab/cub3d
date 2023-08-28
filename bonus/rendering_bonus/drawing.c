/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:24:15 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/28 11:24:08 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void    my_mlx_pixel_put(t_config *config, int x, int y, int color)
{
	char *dst;

	dst = config->data.addr + (y * config->data.line_length + x * (config->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int    get_texture_pixel(t_set_tex *set)
{
	double  y;
	char    *dst;

	y = set->current_texture->height * ((set->i - set->from) / set->high);
	dst = set->current_texture->addr + ((int)y * set->current_texture->line_length + (int)set->x * (set->current_texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void draw_wall(t_config *config, t_set_tex *tex_values)
{
    tex_values->i = 0;
    double from = tex_values->from;
    double to = from + tex_values->high;

	tex_values->x = tex_values->current_texture->width * ((tex_values->x + tex_values->y) - ((int)(tex_values->x + tex_values->y) / CELL_SIZE) * CELL_SIZE) / CELL_SIZE;
    
	tex_values->to = to;
	config->color = 0;
    while (tex_values->i < from && tex_values->i < HIGHT)
    {
        my_mlx_pixel_put(config, config->j, tex_values->i, config->ceiling_rgb);
        tex_values->i++;
    }
    while (tex_values->i < to && tex_values->i < HIGHT)
    {
        config->color = get_texture_pixel(tex_values);
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
    while(i < 1000)
    {
        ray_angle = player->direction + (FOV / 2) - ((FOV / 1000) * i);
        cast_ray(config, player, ray_angle, (FOV / 2) - ((FOV / 1000) * i));
        i++;
    }
}
void    draw_minimap(t_config *config)
{
    int y = 0;
    while (y < config->map.row_len * CELL_SIZE)
    {
        int x = 0;
        while (x < config->map.col_len * CELL_SIZE)
        {
            int color = COLOR_GREEN;
            if (config->map.map[y / CELL_SIZE][x / CELL_SIZE] == '1')
                color = COLOR_WHITE;
            else if (config->map.map[y / CELL_SIZE][x / CELL_SIZE] == 'D')
                color = COLOR_RED;
            else if (config->map.map[y / CELL_SIZE][x / CELL_SIZE] == 'd')
                color = COLOR_BLUE;

            if (fabs(x - config->player.x) <= PLAYER_SIZE/2 && fabs(y - config->player.y) <= PLAYER_SIZE/2)
                color = COLOR_BLACK;
            my_mlx_pixel_put(config, x / MINIMAP_SCALE, y / MINIMAP_SCALE, color);
            x += MINIMAP_SCALE;
        }
        y += MINIMAP_SCALE;
    }
}
