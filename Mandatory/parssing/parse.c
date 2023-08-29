/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:09:22 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/28 15:45:05 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*img(void *mlx, char *pt, int *w, int *h)
{
	void	*image;

	image = mlx_xpm_file_to_image(mlx, pt, w, h);
	if (!image)
		external_error("creating image texture", EXIT_FAILURE, NULL);
	return (image);
}

char	*addr(void *img, int *bpp, int *ll, int *endi)
{
	char	*address;

	address = mlx_get_data_addr(img, bpp, ll, endi);
	if (!address)
		external_error("creating texture address", EXIT_FAILURE, NULL);
	return (address);
}

int	setup_texture(t_config *c)
{
	c->nt.img = img(c->mlx, c->north_path, &(c->nt.width), &(c->nt.height));
	c->nt.addr = addr(c->nt.img, &(c->nt.bits_per_pixel), &c->nt.line_length,
			&(c->nt.endian));
	c->st.img = img(c->mlx, c->south_path, &(c->st.width), &(c->st.height));
	c->st.addr = addr(c->st.img, &(c->st.bits_per_pixel), &c->st.line_length,
			&(c->st.endian));
	c->et.img = img(c->mlx, c->east_path, &(c->et.width), &(c->et.height));
	c->et.addr = addr(c->et.img, &(c->et.bits_per_pixel), &c->et.line_length,
			&(c->et.endian));
	c->wt.img = img(c->mlx, c->west_path, &(c->wt.width), &(c->wt.height));
	c->wt.addr = addr(c->wt.img, &(c->wt.bits_per_pixel), &c->wt.line_length,
			&(c->wt.endian));
	return (1);
}

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
