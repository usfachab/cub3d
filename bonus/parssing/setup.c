/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:26:17 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/26 14:08:24 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

int	setup_texture(t_config c)
{
	c.nt.img = mlx_xpm_file_to_image(c.mlx, c.north_path, &(c.nt.width), &(c.nt.height));
	if (!c.nt.img)
		return (0);
	c.nt.addr = mlx_get_data_addr(c.nt.img, &(c.nt.bits_per_pixel), &c.nt.line_length, &(c.nt.endian));
	if (!c.nt.addr)
		return (0);
	c.st.img = mlx_xpm_file_to_image(c.mlx, c.north_path, &(c.st.width), &(c.st.height));
	if (!c.st.img)
		return (0);
	c.st.addr = mlx_get_data_addr(c.st.img, &(c.st.bits_per_pixel), &c.st.line_length, &(c.st.endian));
	if (!c.st.addr)
		return (0);
	c.et.img = mlx_xpm_file_to_image(c.mlx, c.north_path, &(c.et.width), &(c.et.height));
	if (!c.et.img)
		return (0);
	c.et.addr = mlx_get_data_addr(c.et.img, &(c.et.bits_per_pixel), &c.et.line_length, &(c.et.endian));
	if (!c.et.addr)
		return (0);
	c.wt.img = mlx_xpm_file_to_image(c.mlx, c.north_path, &(c.wt.width), &(c.wt.height));
	if (!c.wt.img)
		return (0);
	c.wt.addr = mlx_get_data_addr(c.wt.img, &(c.wt.bits_per_pixel), &c.wt.line_length, &(c.wt.endian));
	if (!c.wt.addr)
		return (0);
	return (1);
}