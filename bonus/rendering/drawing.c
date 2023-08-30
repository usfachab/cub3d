/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:21:37 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/30 14:46:41 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_config *config, int x, int y, int color)
{
	char *dst;

	dst = config->data.addr + (y * config->data.line_length + x * (config->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int    get_texture_pixel(t_config *config, t_set_tex *set)
{
	double	x;
	double	y;
	char	*dst;

	dst = "test";
	y = config->anime[config->anime_index].height * ((set->i - set->from) / set->high);
	x = (set->x + set->y) - ((int)(set->x + set->y) / CELL_SIZE) * CELL_SIZE;
	x = config->anime[config->anime_index].width * x / CELL_SIZE;
	dst = config->anime[config->anime_index].addr + ((int)y * config->anime[config->anime_index].line_length + (int)x * (config->anime[config->anime_index].bits_per_pixel / 8));
	
	if ((*(unsigned int *) dst) >> 24)
	{
		y = set->current_texture->height * ((set->i - set->from) / set->high);
		x = (set->x + set->y) - ((int)(set->x + set->y) / CELL_SIZE) * CELL_SIZE;
		x = set->current_texture->width * x / CELL_SIZE;
		dst = set->current_texture->addr + ((int)y * set->current_texture->line_length + (int)x * (set->current_texture->bits_per_pixel / 8));
	}
	return (*(unsigned int *)dst);
}

void	draw_wall(t_config *config, t_set_tex *tex_values)
{
	double	from;
	double	to;

	tex_values->i = 0;
	to  = 0;
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

	player_size = PLAYER_SIZE;
	y = player->y - player_size / 2;
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
