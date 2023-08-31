/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:21:37 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/31 11:08:23 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_config *config, int x, int y, int color)
{
	char	*dst;

	dst = config->data.addr + (y * config->data.line_length
			+ x * (config->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_texture_pixel(t_set_tex *set)
{
	double	x;
	double	y;
	char	*dst;

	y = set->current_texture->height
		* ((set->i - set->from) / set->high);
	x = set->current_texture->width * set->x / CELL_SIZE;
	dst = set->current_texture->addr
		+ ((int)y * set->current_texture->line_length
			+ (int)x * (set->current_texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_wall(t_config *config, t_set_tex *tex_values)
{
	double	from;
	double	to;

	tex_values->i = 0;
	from = tex_values->from;
	to = from + tex_values->high;
	tex_values->to = to;
	config->color = 0;
	tex_values->x = (tex_values->x + tex_values->y)
		- ((int)(tex_values->x + tex_values->y) / CELL_SIZE) * CELL_SIZE;
	while (tex_values->i < from && tex_values->i < HIGHT)
	{
		my_mlx_pixel_put(config, config->j, tex_values->i, config->ceiling_rgb);
		tex_values->i++;
	}
	while (tex_values->i < to && tex_values->i < HIGHT)
	{
		config->color = get_texture_pixel(tex_values);
		my_mlx_pixel_put(config, config->j, tex_values->i++, config->color);
	}
	while (tex_values->i < HIGHT)
		my_mlx_pixel_put(config, config->j, tex_values->i++, config->floor_rgb);
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

	i = 0;
	config->j = 0;
	while (i < WIDTH)
	{
		ray_angle = player->direction + (FOV / 2) - ((FOV / 1000) * i);
		cast_ray(config, player, ray_angle, (FOV / 2) - ((FOV / 1000) * i));
		i++;
	}
}
