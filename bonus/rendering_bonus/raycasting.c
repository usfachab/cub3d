/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:41:56 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/26 10:03:20 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub_bonus.h"

double get_hight(double dis)
{
    double r_dis = (HIGHT / 2) * tan(0.5);
    double hight = (r_dis * 40) / dis;
    return (hight);
}

void from_to(double *from, double *to, double hight)
{
    *from = (HIGHT / 2) - hight / 2;
    *to = (HIGHT / 2) + hight / 2;
    if (*from < 0)
        *from = 0;
    if (*to > HIGHT)
        *to = HIGHT;
}

void initialize_intersections(t_intersection *horizontal, t_intersection *vertical)
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

void find_horizontal_intersection(t_config *config, t_ray ray, double angle, t_intersection *horizontal)
{
    double xinter, yinter;
    double stepx;
    double stepy;

    stepy = CELL_SIZE;
    stepx = (CELL_SIZE / tan(angle));
    yinter = (int)(ray.ray_y / CELL_SIZE) * CELL_SIZE;
    if (sin(angle) > 0)
        stepy *= -1;
    else
    {
        stepx *= -1;
        yinter += CELL_SIZE;
    }
    xinter = ray.ray_x + (ray.ray_y - yinter) / tan(angle);
    while (1)
    {
        if (xinter < 0 || yinter < 0 || xinter >= config->map.col_len * CELL_SIZE || yinter >= config->map.row_len * CELL_SIZE)
            break;
        if (stepy < 0 && config->map.map[(int)yinter / CELL_SIZE - 1][(int)xinter / CELL_SIZE] == '1')
            break;
        else if (config->map.map[(int)yinter / CELL_SIZE][(int)xinter / CELL_SIZE] == '1')
            break;
        xinter += stepx;
        yinter += stepy;
    }
    horizontal->x = xinter;
    horizontal->y = yinter;
    horizontal->distance = sqrt((ray.ray_x - horizontal->x) * (ray.ray_x - horizontal->x) +
                                (ray.ray_y - horizontal->y) * (ray.ray_y - horizontal->y));
}

void find_vertical_intersection(t_config *config, t_ray ray, double angle, t_intersection *vertical)
{
    double yinter;
    double xinter;
    double stepx;
    double stepy;

    xinter = (int)(ray.ray_x / CELL_SIZE) * CELL_SIZE;
    stepx = CELL_SIZE;
    stepy = CELL_SIZE * tan(angle);
    if (cos(angle) < 0)
        stepx *= -1;
    else
    {
        stepy *= -1;
        xinter += CELL_SIZE;
    }
    yinter = ray.ray_y + (ray.ray_x - xinter) * tan(angle);
    while (1)
    {
        if (xinter < 0 || yinter < 0 || xinter >= config->map.col_len * CELL_SIZE || yinter >= config->map.row_len * CELL_SIZE)
            break;
        if (stepx < 0 && config->map.map[(int)yinter / CELL_SIZE][(int)xinter / CELL_SIZE - 1] == '1')
            break;
        else if (config->map.map[(int)yinter / CELL_SIZE][(int)xinter / CELL_SIZE] == '1')
            break;
        xinter += stepx;
        yinter += stepy;
    }
    vertical->x = xinter;
    vertical->y = yinter;
    vertical->distance = sqrt((ray.ray_x - vertical->x) * (ray.ray_x - vertical->x) +
                              (ray.ray_y - vertical->y) * (ray.ray_y - vertical->y));
}

void cast_ray(t_config *config, t_player *player, double angle, double t)
{
    double from, to, hight;
    t_ray ray;
    t_intersection horizontal, vertical;

    angle = remainder(angle, M_PI * 2);
    if (angle < 0)
        angle += 2 * M_PI;
    init_ray(&ray, player, angle);
    initialize_intersections(&horizontal, &vertical);
    find_horizontal_intersection(config, ray, angle, &horizontal);
    find_vertical_intersection(config, ray, angle, &vertical);
    horizontal.distance *= cos(t);
    vertical.distance *= cos(t);
    if (horizontal.distance < vertical.distance)
        hight = get_hight(horizontal.distance);
    else
        hight = get_hight(vertical.distance);
    from_to(&from, &to, hight);
    draw_wall(config, from, to, config->j++);
}
