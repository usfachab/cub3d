/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 08:37:17 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/31 08:43:36 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_config *config, int x, int y, int color)
{
	char	*dst;

	dst = config->data.addr
		+ (y * config->data.line_length
			+ x * (config->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_texture_pixel(t_config *config, t_set_tex *set)
{
	double	x;
	double	y;
	char	*dst;

	y = config->anime[config->anime_index].height
		* ((set->i - set->from) / set->high);
	x = (set->x + set->y) - ((int)(set->x + set->y) / CELL_SIZE) * CELL_SIZE;
	x = config->anime[config->anime_index].width * x / CELL_SIZE;
	dst = config->anime[config->anime_index].addr
		+ ((int)y * config->anime[config->anime_index].line_length
			+ (int)x * (config->anime[config->anime_index].bits_per_pixel / 8));
	if ((*(unsigned int *) dst) >> 24 || set->flage)
	{
		y = set->current_texture->height
			* ((set->i - set->from) / set->high);
		x = (set->x + set->y) - ((int)(set->x + set->y)
				/ CELL_SIZE) * CELL_SIZE;
		x = set->current_texture->width * x / CELL_SIZE;
		dst = set->current_texture->addr
			+ ((int)y * set->current_texture->line_length
				+ (int)x * (set->current_texture->bits_per_pixel / 8));
	}
	return (*(unsigned int *)dst);
}

int	mouse_move(int x, int y, void *param)
{
	t_config	*config;

	(void)y;
	config = (t_config *)param;
	if (x < config->last_mouse_x)
		rotate_player(&config->player, MOUSE_SPEED);
	else if (x > config->last_mouse_x)
		rotate_player(&config->player, -MOUSE_SPEED);
	config->last_mouse_x = x;
	return (0);
}

double	get_hight(double dis)
{
	double	r_dis;
	double	hight;

	r_dis = (HIGHT / 2);
	hight = (r_dis * 40) / dis;
	return (hight);
}

void	from_to(double *from, double *to, double hight)
{
	*from = (HIGHT / 2) - hight / 2;
	*to = (HIGHT / 2) + hight / 2;
	if (*from < 0)
		*from = 0;
	if (*to > HIGHT)
		*to = HIGHT;
}
