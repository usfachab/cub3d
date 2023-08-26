/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:36:38 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/26 10:10:49 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void init_ray(t_ray *ray, t_player *player, double angle)
{
	ray->ray_x = player->x;
	ray->ray_y = player->y;
	ray->ray_dx = cos(angle);
	ray->ray_dy = sin(angle);
}

void initialize_game(t_config *config, char *map_file)
{
	config->j = 0;
	read_map(map_file, &config->map);
	config->player = (t_player){2 * 40 + 20, 2 * 40 + 20, M_PI / 4};
}

int initialize_graphics(t_config *config)
{
	config->mlx = mlx_init();
	if (!config->mlx)
		return (0);
	config->mlx_win = mlx_new_window(config->mlx, HIGHT, WIDTH, "Hello World!");
	if (!config->mlx_win)
		return (0);
	config->img = mlx_new_image(config->mlx, HIGHT, WIDTH);
	if (!config->img)
		return (0);
	config->data.addr = mlx_get_data_addr(config->img, &config->data.bits_per_pixel, &config->data.line_length, &config->data.endian);
	if (!config->data.addr)
		return (0);
	return (1);
}

int exit_game(void)
{
	exit(1);
}

int main(int argc, char *argv[])
{
	t_config config;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	initialize_game(&config, argv[1]);
	if (!initialize_graphics(&config))
	{
		fprintf(stderr, "Error initializing graphics.\n");
		return (EXIT_FAILURE);
	}
	mlx_put_image_to_window(config.mlx, config.mlx_win, config.img, 0, 0);
	mlx_hook(config.mlx_win, 2, 1, key_hook, &config);
	mlx_hook(config.mlx_win, 17, 0, exit_game, NULL);
	mlx_put_image_to_window(config.mlx, config.mlx_win, config.img, 0, 0);
	mlx_loop(config.mlx);
	free_map(&config.map);
	return (EXIT_SUCCESS);
}
