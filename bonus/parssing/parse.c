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

void	free_config_resources(t_config *config)
{
	freeall(config->map.map);
	mlx_destroy_window(config->mlx, config->mlx_win);
	exit(1);
}
