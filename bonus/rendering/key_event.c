/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:39:49 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/31 14:54:17 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_player(t_player *player, double angle)
{
	player->direction += angle;
}

void	door(t_player *player, t_map *map, double direction)
{
	double			new_x;
	double			new_y;

	new_x = player->x + cos(direction) * CELL_SIZE;
	new_y = player->y
		- sin(direction) * CELL_SIZE;
	if (is_valid_position(map, new_x, player->y)
		|| is_valid_position(map, player->x, new_y))
	{
		if (map->map[(int)new_y / CELL_SIZE][(int)new_x / CELL_SIZE] == 'D')
			map->map[(int)new_y / CELL_SIZE][(int)new_x / CELL_SIZE] = 'R';
		else if (map->map[(int)new_y / CELL_SIZE]
			[(int)new_x / CELL_SIZE] == 'R')
			map->map[(int)new_y / CELL_SIZE][(int)new_x / CELL_SIZE] = 'D';
	}
}

int	key_hook(int keycode, void *param)
{
	t_config	*config;

	config = (t_config *)param;
	if (keycode == 65307)
		free_config_resources(config);
	if (keycode == 115)
		move_player(&config->player,
			&config->map, config->player.direction + M_PI);
	if (keycode == 119)
		move_player(&config->player,
			&config->map, config->player.direction);
	if (keycode == 100)
		move_player(&config->player, &config->map,
			config->player.direction - M_PI / 2);
	if (keycode == 97)
		move_player(&config->player,
			&config->map, config->player.direction + M_PI / 2);
	if (keycode == 101)
		door(&config->player,
			&config->map, config->player.direction);
	if (keycode == 65363)
		rotate_player(&config->player, -TURN_ANGLE);
	if (keycode == 65361)
		rotate_player(&config->player, +TURN_ANGLE);
	return (0);
}

bool	is_valid_position(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->col_len * CELL_SIZE || y < 0
		|| y >= map->row_len * CELL_SIZE)
		return (false);
	if (map->map[y / CELL_SIZE][x / CELL_SIZE] == '1')
		return (false);
	if (map->map[y / CELL_SIZE][x / CELL_SIZE] == 'D')
		return (false);
	return (true);
}

void	move_player(t_player *player, t_map *map, double direction)
{
	double			new_x;
	double			new_y;

	new_x = player->x + cos(direction) * MOVE_SPEED;
	new_y = player->y - sin(direction) * MOVE_SPEED;
	if (is_valid_position(map, new_x + 3 * ((cos(direction) > 0)
				- (cos(direction) < 0)), player->y))
		player->x = new_x;
	if (is_valid_position(map, player->x, new_y - 3 * ((sin(direction) > 0)
				- (sin(direction) < 0))))
		player->y = new_y;
}
