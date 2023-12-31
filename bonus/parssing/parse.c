/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:09:22 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/31 17:27:24 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cleanup(t_config *config)
{
	free(config->ceiling);
	free(config->floor);
	free(config->north_path);
	free(config->south_path);
	free(config->east_path);
	free(config->west_path);
}

t_config	initialize_game(char *filename)
{
	t_config	config;

	if (!parsing_texture(&config, filename))
		external_error("Invalid instructions", EXIT_FAILURE, NULL);
	if (!parsing_map(&config))
		external_error("Invalid map", EXIT_FAILURE, NULL);
	if (!setup_texture(&config))
		external_error("Setup textures", EXIT_FAILURE, config.map.map);
	if (!setup_animation(&config))
		external_error("Setup animation", EXIT_FAILURE, config.map.map);
	cleanup(&config);
	return (config);
}

void	freeanime(t_config *config)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		mlx_destroy_image(config->mlx, config->anime[i].img);
		i++;
	}
	mlx_destroy_image(config->mlx, config->door.img);
}

void	free_config_resources(t_config *config)
{
	freeall(config->map.map);
	freeanime(config);
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
