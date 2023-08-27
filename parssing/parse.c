/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:09:22 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/27 20:44:48 by yachaab          ###   ########.fr       */
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
	if (!setup_texture(&config))
		external_error("3", EXIT_FAILURE, NULL);
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
