/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:35:16 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/29 23:14:32 by yachaab          ###   ########.fr       */
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
	c->door.img = img(c->mlx, "./bonus/parssing/src/door.xpm",
			&(c->door.width), &(c->door.height));
	c->door.addr = addr(c->door.img, &(c->door.bits_per_pixel),
			&c->door.line_length, &(c->door.endian));
	return (1);
}

int	setup_animation(t_config *c)
{
	int		i;
	char	*path;

	i = 0;
	path = ft_strdup("./bonus/parssing/animation/anime_1.xpm");
	while (i < 6)
	{
		c->anime[i].img = img(c->mlx, path, &(c->anime[i].width),
				&(c->anime[i].height));
		c->anime[i].addr = addr(c->anime[i].img,
				&(c->anime[i].bits_per_pixel),
				&c->anime[i].line_length,
				&(c->anime[i].endian));
		path[33] += 1;
		i++;
	}
	return (free(path), 1);
}
