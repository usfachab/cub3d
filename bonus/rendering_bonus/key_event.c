/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:52:19 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/27 17:57:01 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void rotate_player(t_player *player, double angle)
{
    player->direction += angle;
}

void	free_config_resources(t_config *config)
{
	int i;

	i = 0;
	// Freeing the map
	if (config->map.map)
	{
		while (i < config->map.row_len)
		{
			if (config->map.map[i])
				free(config->map.map[i]);
			i++;
		}
		free(config->map.map);
	}

	// Free texture paths and other dynamically allocated strings
	if (config->north_path)
		free(config->north_path);
	if (config->south_path)
		free(config->south_path);
	if (config->east_path)
		free(config->east_path);
	if (config->west_path)
		free(config->west_path);
	if (config->ceiling)
		free(config->ceiling);
	if (config->floor)
		free(config->floor);

	// Add freeing for other dynamically allocated resources if needed
}


int key_hook(int keycode, void *param)
{
	t_config *config = (t_config *)param;
	if (keycode == 65307)
	{
		free_config_resources(config);
		mlx_destroy_window(config->mlx, config->mlx_win);
		exit(0);
	}
	if (keycode == 115)
		 move_player(&config->player, &config->map, config->player.direction + M_PI);
	if (keycode == 119)
		move_player(&config->player, &config->map, config->player.direction);
	if (keycode == 100)
		move_player(&config->player, &config->map, config->player.direction - M_PI/2);
	if (keycode == 97)
		move_player(&config->player, &config->map, config->player.direction + M_PI/2);
	if (keycode == 65363)
		rotate_player(&config->player, -TURN_ANGLE);
	if (keycode == 65361)
		rotate_player(&config->player, +TURN_ANGLE);
	render_rays(config, &config->player);tex_values
	mlx_put_image_to_window(config->mlx, config->mlx_win, config->img, 0, 0);
	return (0);
}

bool is_valid_position(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->col_len * CELL_SIZE || y < 0
		|| y >= map->row_len * CELL_SIZE)
		return (false);
	if (map->map[y / CELL_SIZE][x / CELL_SIZE] == '1')
		return (false);
	return (true);
}

void	move_player(t_player *player, t_map *map, double direction)
{
	double new_x, new_y;
	const double buffer = 1;

	new_x = player->x + cos(direction) * MOVE_SPEED;
	new_y = player->y - sin(direction) * MOVE_SPEED;
	if (is_valid_position(map, new_x + buffer * cos(direction), player->y))
		player->x = new_x;
	if (is_valid_position(map, player->x, new_y - buffer * sin(direction)))
		player->y = new_y;
}

void free_map(t_map *map)
{
	int i;
	i = 0;
	while (i < map->row_len)
		free(map->map[i++]);
	free(map->map);
}

int mouse_move(int x, int y, void *param)
{
	(void)y;
	t_config *config = (t_config *)param;

	if (x < config->last_mouse_x)
		rotate_player(&config->player, MOUSE_SPEED);
	else if (x > config->last_mouse_x)
		rotate_player(&config->player, -MOUSE_SPEED);
	config->last_mouse_x = x;
	render_rays(config, &config->player);
	mlx_put_image_to_window(config->mlx, config->mlx_win, config->img, 0, 0);
	return (0);
}
