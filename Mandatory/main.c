/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 08:36:38 by ysabr             #+#    #+#             */
/*   Updated: 2023/09/03 14:13:13 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_ray(t_ray *ray, t_player *player, double angle)
{
	ray->ray_x = player->x;
	ray->ray_y = player->y;
	ray->ray_dx = cos(angle);
	ray->ray_dy = sin(angle);
}

int	initialize_graphics(t_config *config)
{
	int			sizex;
	int			sizey;
	
	mlx_get_screen_size(config->mlx, &sizex, &sizey);
	config->mlx_win = mlx_new_window(config->mlx, sizex, sizey, "cub3D");
	if (!config->mlx_win)
		return (0);
	config->img = mlx_new_image(config->mlx, sizex, sizey);
	if (!config->img)
		return (0);
	config->data.addr = mlx_get_data_addr(config->img,
			&config->data.bits_per_pixel, &config->data.line_length,
			&config->data.endian);
	if (!config->data.addr)
		return (0);
	return (1);
}

int	exit_game(t_config *config)
{
	free_config_resources(config);
	exit(1);
}

void	free_config_resources(t_config *config)
{
	freeall(config->map.map);
	mlx_destroy_image(config->mlx, config->nt.img);
	mlx_destroy_image(config->mlx, config->st.img);
	mlx_destroy_image(config->mlx, config->et.img);
	mlx_destroy_image(config->mlx, config->wt.img);
	mlx_destroy_image(config->mlx, config->img);
	mlx_clear_window(config->mlx, config->mlx_win);
	mlx_destroy_window(config->mlx, config->mlx_win);
	mlx_destroy_display(config->mlx);
	free(config->mlx);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_config	config;

	if (argc != 2)
	{
		printf("too few argument\n");
		return (EXIT_FAILURE);
	}
	config = initialize_game(argv[1]);
	config.player.x = config.player.x * CELL_SIZE + 20;
	config.player.y = config.player.y * CELL_SIZE + 20;
	
	if (!initialize_graphics(&config))
		return (EXIT_FAILURE);
	mlx_hook(config.mlx_win, 2, 1, key_hook, &config);
	mlx_hook(config.mlx_win, 17, 0, exit_game, &config);
	render_rays(&config, &config.player);
	mlx_put_image_to_window(config.mlx, config.mlx_win, config.img, 0, 0);
	mlx_loop(config.mlx);
	return (EXIT_SUCCESS);
}
