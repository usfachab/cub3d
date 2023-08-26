/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:09:22 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/26 11:55:49 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_config initialize_game(char *filename)
{
	t_config	config;

	if (!parsing_texture(&config, filename))
		external_error("1", EXIT_FAILURE, NULL);
	if (!parsing_map(&config))
		external_error("2", EXIT_FAILURE, NULL);
	if (!setup_texture(config))
		external_error("3", EXIT_FAILURE, NULL);
	// printf("rgb: %d\n", config.floor_rgb);
	// printf("rgb: %d\n", config.ceiling_rgb);
	// printf("NO: %s\n", config.north_path);
	// printf("SO: %s\n", config.south_path);
	// printf("EA: %s\n", config.east_path);
	// printf("WE: %s\n", config.west_path);
	// printf("C: %s\n", config.ceiling);
	// printf("F: %s\n", config.floor);
	// printf("X: %f\n", config.player.x);
	// printf("Y: %f\n", config.player.y);
	// printf("P: %f\n", config.player.direction);
	// printf("P: %d\n", config.map.col_len);
	// printf("P: %d\n", config.map.row_len);
	
	// for (int i = 0; config.map.map[i]; i++)
	// 	printf("%s\n", config.map.map[i]);
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
// 	if (!setup_texture(config))
// 		external_error("3", EXIT_FAILURE, NULL);
// 	return (0);
// }
