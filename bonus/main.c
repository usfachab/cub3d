//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:28:26 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/23 22:28:47 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub_bonus.h"

void init_ray(t_ray *ray, t_player *player, double angle)
{
	ray->ray_x = player->x;
	ray->ray_y = player->y;
	ray->ray_dx = cos(angle);
	ray->ray_dy = sin(angle);
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
        return EXIT_FAILURE;
    }
    config.j = 0;
    config.mini_map_scale = 8;
    config.last_mouse_x = WIDTH / 2;
	config = initialize_game(argv[1]);
    config.player.x = config.player.x * CELL_SIZE + 20;
	config.player.y = config.player.y * CELL_SIZE + 20;
    config.mlx = mlx_init();
    if (!config.mlx)
    {
        fprintf(stderr, "Error initializing MLX.\n");
        return EXIT_FAILURE;
    }

    config.mlx_win = mlx_new_window(config.mlx, HIGHT, WIDTH, "Hello World!");
    if (!config.mlx_win)
    {
        fprintf(stderr, "Error creating window.\n");
        return EXIT_FAILURE;
    }
    config.img = mlx_new_image(config.mlx, HIGHT, WIDTH);
    if (!config.img)
    {
        fprintf(stderr, "Error creating image.\n");
        return EXIT_FAILURE;
    }
    config.data.addr = mlx_get_data_addr(config.img, &config.data.bits_per_pixel, &config.data.line_length, &config.data.endian);
    if (!config.data.addr)
    {
        fprintf(stderr, "Error getting data address.\n");
        return EXIT_FAILURE;
    }
    mlx_put_image_to_window(config.mlx, config.mlx_win, config.img, 0, 0);
    mlx_hook(config.mlx_win, 2, 1, key_hook, &config);
    mlx_hook(config.mlx_win, 6, 1L << 6, mouse_move, &config); // 64 in decimal
    mlx_hook(config.mlx_win, 17, 0, exit_game, NULL);
    mlx_put_image_to_window(config.mlx, config.mlx_win, config.img, 0, 0);
    mlx_loop(config.mlx);
    mlx_destroy_window(config.mlx, config.mlx_win);
    return (EXIT_SUCCESS);
}
