/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:22:25 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/31 11:23:47 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	get_hight(double dis)
{
	double	r_dis;
	double	hight;

	r_dis = (HIGHT / 2);
	hight = (r_dis * CELL_SIZE) / dis;
	return (hight);
}

void	from_to(double *from, double *to, double hight)
{
	*from = (HIGHT / 2) - hight / 2;
	*to = (HIGHT / 2) + hight / 2;
	if (*from < 0)
		*from = 0;
	if (*to > HIGHT)
		*to = HIGHT;
}

void	initialize_intersections(t_intersection *horizontal,
			t_intersection *vertical)
{
	horizontal->x = 0;
	horizontal->y = 0;
	horizontal->distance = INT_MAX;
	horizontal->hit = 0;
	vertical->x = 0;
	vertical->y = 0;
	vertical->distance = INT_MAX;
	vertical->hit = 0;
}

double	compute_distance(t_ray ray, double x, double y)
{
	return (sqrt((ray.ray_x - x) * (ray.ray_x - x)
			+ (ray.ray_y - y) * (ray.ray_y - y)));
}

void	fishblow(t_intersection *horizontal,
			t_intersection *vertical, double *t)
{
	horizontal->distance *= cos(*t);
	vertical->distance *= cos(*t);
}
