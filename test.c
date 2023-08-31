
double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return angle;
}

double	compute_distance(t_ray ray, double x, double y)
{
	return (sqrt((ray.ray_x - x) * (ray.ray_x - x) + (ray.ray_y - y) * (ray.ray_y - y)));
}

void	initialize_intersections(t_intersection *horizontal, t_intersection *vertical)
{
	horizontal->x = 0;
	horizontal->y = 0;
	horizontal->distance = INT_MAX;
	horizontal->hit = 0;
	horizontal->flage = 0;
	vertical->x = 0;
	vertical->y = 0;
	vertical->distance = INT_MAX;
	vertical->hit = 0;
	vertical->flage = 0;
}

void	update_vertical_values(t_ray ray, t_intersection *vertical, t_intersection_params params)
{
	vertical->x = params.xinter;
	vertical->y = params.yinter;
	vertical->distance = compute_distance(ray, vertical->x, vertical->y);
}

void	update_horizontal_values(t_ray ray, t_intersection *horizontal, t_intersection_params params)
{
	horizontal->x = params.xinter;
	horizontal->y = params.yinter;
	horizontal->distance = compute_distance(ray, horizontal->x, horizontal->y);
}

int check_horizontal_map_hit(t_intersection_params params, t_config *config)
{
	int map_value;

    map_value = config->map.map[(int)(params.yinter / CELL_SIZE)][(int)(params.xinter / CELL_SIZE)];
    if (map_value == 'D' || (params.stepy < 0 && params.yinter >= CELL_SIZE && map_value == '1'))
        return (1);
	return (0);
}

int	check_horizontal_bounds(t_intersection_params params, t_config *config)
{
    if (params.xinter >= 0 && params.yinter >= 0 && params.xinter < config->map.col_len * CELL_SIZE && params.yinter < config->map.row_len * CELL_SIZE)
        return (1);
	return (0);
}

void	find_horizontal_intersection(t_config *config, t_ray ray, double angle, t_intersection *horizontal)
{
	t_intersection_params	params;

	init_horizontal_values(ray, angle, &params);
	while (check_horizontal_bounds(params, config) && check_horizontal_map_hit(params, config))
	{
		if (check_horizontal_map_hit(params, config))
			break ;
		params.xinter += params.stepx;
		params.yinter += params.stepy;
	}
	update_horizontal_values(ray, horizontal, params);
}


int	check_horizontal_hit(t_intersection_params params, t_config *config)
{
	int	map_value = config->map.map[(int)(params.yinter / CELL_SIZE)][(int)(params.xinter / CELL_SIZE)];
	return (map_value == 'D' || (params.stepy < 0 && params.yinter >= CELL_SIZE && map_value == '1'));
}

void	find_vertical_intersection(t_config *config, t_ray ray, double angle, t_intersection *vertical)
{
	t_intersection_params	params;

	init_vertical_values(ray, angle, &params);
	while (check_vertical_bounds(params, config) && check_vertical_hit(params, config))
	{
		if (check_vertical_map_hit(params, config))
			break ;
		params.xinter += params.stepx;
		params.yinter += params.stepy;
	}
	update_vertical_values(ray, vertical, params);
}

int	check_vertical_bounds(t_intersection_params params, t_config *config)
{
	return (params.xinter >= 0 && params.yinter >= 0 && params.xinter < config->map.col_len * CELL_SIZE && params.yinter < config->map.row_len * CELL_SIZE);
}

int	check_vertical_hit(t_intersection_params params, t_config *config)
{
	int	map_value = config->map.map[(int)(params.yinter / CELL_SIZE)][(int)(params.xinter / CELL_SIZE)];
	return (map_value == 'D' || (params.stepx < 0 && params.xinter >= CELL_SIZE && map_value == '1'));
}

int check_vertical_map_hit(t_intersection_params params, t_config *config)
{
	if (params.xinter < 0 || params.yinter < 0 || params.xinter >= config->map.col_len * CELL_SIZE
		|| params.yinter >= config->map.row_len * CELL_SIZE)
		return (1);
	if (config->map.map[(int)params.yinter/ CELL_SIZE][(int)params.xinter / CELL_SIZE] == 'D')
	{
		vertical->flage = 1;
		return (1);
	}
	if (params.stepx < 0 && params.xinter >= CELL_SIZE && config->map.map[(int)params.yinter / CELL_SIZE][(int)params.xinter / CELL_SIZE - 1] == 'D')
	{
		vertical->flage = 1;
		return (1);
	}
	if (config->map.map[(int)params.yinter/ CELL_SIZE][(int)params.xinter / CELL_SIZE] == '1')
		return (1);
	if (params.stepx < 0 && params.xinter >= CELL_SIZE && config->map.map[(int)params.yinter / CELL_SIZE][(int)params.xinter / CELL_SIZE - 1] == '1')
		return (1);
    return (0);
}

void	compute_distances(t_intersection *horizontal, t_intersection *vertical, double t)
{
	horizontal->distance *= cos(t);
	vertical->distance *= cos(t);
}

void	select_texture_and_draw(t_config *config, t_set_tex *tex_values, double angle, t_intersection *horizontal, t_intersection *vertical)
{
	if (horizontal->distance < vertical->distance)
	{
		tex_values->x = horizontal->x;
		tex_values->y = horizontal->y;
		tex_values->high = get_height(horizontal->distance);
		tex_values->from = (HIGHT / 2) - tex_values->high / 2;
		tex_values->flage = horizontal->flage;
		if (horizontal->flage)
			tex_values->current_texture = &config->door;
		else if (sin(angle) > 0)
			tex_values->current_texture = &(config->nt);
		else
			tex_values->current_texture = &config->st;
	}
	else
	{
		tex_values->x = vertical->x;
		tex_values->y = vertical->y;
		tex_values->high = get_height(vertical->distance);
		tex_values->from = (HIGHT / 2) - tex_values->high / 2;
		tex_values->flage = vertical->flage;
		if (vertical->flage)
			tex_values->current_texture = &config->door;
		else if (cos(angle) > 0)
			tex_values->current_texture = &config->et;
		else
			tex_values->current_texture = &config->wt;
	}
	draw_wall(config, tex_values);
	config->j++;
}


void	cast_ray(t_config *config, t_player *player, double angle, double t)
{
	t_ray			ray;
	t_intersection	horizontal;
	t_intersection	vertical;
	t_set_tex		tex_values;

	initialize_tex_values(&tex_values);
	angle = normalize_angle(angle);
	init_ray(&ray, player, angle);
	initialize_intersections(&horizontal, &vertical);
	find_horizontal_intersection(config, ray, angle, &horizontal);
	find_vertical_intersection(config, ray, angle, &vertical);
	compute_distances(&horizontal, &vertical, t);
	select_texture_and_draw(config, &tex_values, angle, &horizontal, &vertical);
	config->j++;
}

int	main(void)
{
	// Your main program logic here
	return (0);
}
