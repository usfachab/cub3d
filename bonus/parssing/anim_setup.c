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

int	setup_animation(t_config *c)
{
	c->anime[0].img = img(c->mlx, "./bonus/parssing/animation/AnyConv.com__010.xpm", &(c->anime[0].width), &(c->anime[0].height));
	c->anime[0].addr = addr(c->anime[0].img, &(c->anime[0].bits_per_pixel), &c->anime[0].line_length,
			&(c->anime[0].endian));
	c->anime[1].img = img(c->mlx, "./bonus/parssing/animation/AnyConv.com__012.xpm", &(c->anime[1].width), &(c->anime[1].height));
	c->anime[1].addr = addr(c->anime[1].img, &(c->anime[1].bits_per_pixel), &c->anime[1].line_length,
			&(c->anime[1].endian));

	c->anime[2].img = img(c->mlx, "./bonus/parssing/animation/AnyConv.com__014.xpm", &(c->anime[2].width), &(c->anime[2].height));
	c->anime[2].addr = addr(c->anime[2].img, &(c->anime[2].bits_per_pixel), &c->anime[2].line_length,
			&(c->anime[2].endian));

	c->anime[3].img = img(c->mlx, "./bonus/parssing/animation/AnyConv.com__016.xpm", &(c->anime[3].width), &(c->anime[3].height));
	c->anime[3].addr = addr(c->anime[3].img, &(c->anime[3].bits_per_pixel), &c->anime[3].line_length,
			&(c->anime[3].endian));

	c->anime[4].img = img(c->mlx, "./bonus/parssing/animation/AnyConv.com__018.xpm", &(c->anime[4].width), &(c->anime[4].height));
	c->anime[4].addr = addr(c->anime[4].img, &(c->anime[4].bits_per_pixel), &c->anime[4].line_length,
			&(c->anime[4].endian));

	c->anime[5].img = img(c->mlx, "./bonus/parssing/animation/AnyConv.com__020.xpm", &(c->anime[5].width), &(c->anime[5].height));
	c->anime[5].addr = addr(c->anime[5].img, &(c->anime[5].bits_per_pixel), &c->anime[5].line_length,
			&(c->anime[5].endian));
	return (1);
}