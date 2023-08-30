/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:09:22 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/29 18:01:51 by yachaab          ###   ########.fr       */
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
	printf("color: %d\n", config.floor_rgb);
	cleanup(&config);
	return (config);
}

// int	main(int argc, char *argv[])
// {
// 	t_config	config;
// 	(void)argc;
// 	if (!parsing_texture(&config, argv[1]))
// 		external_error("1", EXIT_FAILURE, NULL);
// 	if (!parsing_map(&config))
// 		external_error("2", EXIT_FAILURE, NULL);
// 	if (!setup_texture(&config))
// 		external_error("3", EXIT_FAILURE, NULL);
// 	cleanup(&config);
// 	return (0);
// }
