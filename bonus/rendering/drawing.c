/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:21:37 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/31 08:38:26 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_wall(t_config *config, t_set_tex *tex_values)
{
	double	from;
	double	to;

	tex_values->i = 0;
	to = 0;
	tex_values->to = to;
	from = tex_values->from;
	to = from + tex_values->high;
	config->color = 0;
	while (tex_values->i < from && tex_values->i < HIGHT)
	{
		my_mlx_pixel_put(config, config->j, tex_values->i, config->ceiling_rgb);
		tex_values->i++;
	}
	while (tex_values->i < to && tex_values->i < HIGHT)
	{
		config->color = get_texture_pixel(config, tex_values);
		my_mlx_pixel_put(config, config->j, tex_values->i, config->color);
		tex_values->i++;
	}
	while (tex_values->i < HIGHT)
	{
		my_mlx_pixel_put(config, config->j, tex_values->i, config->floor_rgb);
		tex_values->i++;
	}
}

void	draw_player(t_config *config, t_player *player)
{
	int	player_size;
	int	y;
	int	x;

	player_size = PLAYER_SIZE;
	y = player->y - player_size / 2;
	while (y <= player->y + player_size / 2)
	{
		x = player->x - player_size / 2;
		while (x <= player->x + player_size / 2)
		{
			my_mlx_pixel_put(config, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

void	render_rays(t_config *config, t_player *player)
{
	int		i;
	double	ray_angle;

	config->j = 0;
	i = 0;
	while (i < WIDTH)
	{
		ray_angle = player->direction + (FOV / 2) - ((FOV / 1000) * i);
		cast_ray(config, player, ray_angle, (FOV / 2) - ((FOV / 1000) * i));
		i++;
	}
}

int	minimap_color(t_config *config, int px, int py)
{
	int	color;

	color = COLOR_GREEN;
	if (py < 0 || px < 0)
		color = COLOR_BLACK;
	else if (px / CELL_SIZE > config->map.col_len)
		color = COLOR_BLACK;
	else if (py / CELL_SIZE > config->map.row_len)
		color = COLOR_BLACK;
	else if (config->map.map[py / CELL_SIZE][px / CELL_SIZE] == '1')
		color = COLOR_WHITE;
	else if (config->map.map[py / CELL_SIZE][px / CELL_SIZE] == 'D')
		color = COLOR_RED;
	else if (config->map.map[py / CELL_SIZE][px / CELL_SIZE] == 'R')
		color = COLOR_BLUE;
	else if (config->map.map[py / CELL_SIZE][px / CELL_SIZE] != '0')
		color = COLOR_BLACK;
	return (color);
}

void	draw_minimap(t_config *config)
{
	t_draw_data	data;
	int			color;
	t_player	mini_player;

	data.y = 0;
	data.py = config->player.y - HIGH_MINIMAP / 2;
	while (data.y < HIGH_MINIMAP)
	{
		data.x = 0;
		data.px = config->player.x - WIDTH_MINIMAP / 2;
		while (data.x < WIDTH_MINIMAP)
		{
			color = minimap_color(config, data.px, data.py);
			my_mlx_pixel_put(config, data.x, data.y, color);
			data.x++;
			data.px++;
		}
		data.y++;
		data.py++;
	}
	mini_player.x = WIDTH_MINIMAP / 2;
	mini_player.y = HIGH_MINIMAP / 2;
	draw_player(config, &mini_player);
}
