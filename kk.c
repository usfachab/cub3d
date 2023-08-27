# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <ctype.h>
# include <fcntl.h>
# include <unistd.h>
# include <mlx.h>
# include <math.h>
# include <limits.h>

# define CELL_SIZE 40
# define PLAYER_SIZE 10
# define MOVE_SPEED 10
# define TURN_ANGLE (M_PI / 60)
# define HIGHT 1000
# define WIDTH 1000
# define FOV (M_PI / 3)

typedef struct
{
	double ray_x;
	double ray_y;
	double ray_dx;
	double ray_dy;
	double distance;
} t_ray;

typedef struct s_data
{
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int 	endian;
}	t_data;

// !PARSING
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int 	endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	direction;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		row_len;
	int		col_len;
}	t_map;

typedef struct s_set_tex
{
	double		high; //hight of the wall
	double		from; //begin of the wall
	double		x; //cordonate of the wall on x
	double		y; //cordonate of the wall on y
	int			i; //that used in draw_wall
	t_texture	*current_texture; //texture that will used
}	t_set_tex;

typedef struct  s_config
{
	t_texture	nt;
	t_texture	st;
	t_texture	et;
	t_texture	wt;
	t_data		data;
	t_map		map;
	t_player	player;
	void		*mlx;
	void		*mlx_win;
	void		*img;
	int			j;
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;
	char		*ceiling;
	char		*floor;
	int			nbr_instru;
	int			floor_color[3];
	int			ceiling_color[3];
	int			floor_rgb;
	int			ceiling_rgb;
	int			fd;
	int			color;
}	t_config;


typedef struct s_plit
{
	int		i;
	int		j;
	int		y;
	char	**resl;
}			t_split;

typedef struct s_intersection {
	double	x;
	double	y;
	double	distance;
	int		hit;
}	t_intersection;

void my_mlx_pixel_put(t_config *config, int x, int y, int color)
{
	char *dst;

	dst = config->data.addr + (y * config->data.line_length + x * (config->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_wall(t_config *config, t_set_tex *tex_values)
{
    int i = tex_values->i;
    double from = tex_values->from;
    double to = from + tex_values->high;
	config->color = 0;
    while (i < from && i < HIGHT)
    {
        my_mlx_pixel_put(config, tex_values->x, i, config->ceiling_rgb);
        i++;
    }
    while (i < to && i < HIGHT)
    {
		//you must call your function here and set the value on config color so you must return unsigned int
        my_mlx_pixel_put(config, tex_values->x, i, config->color);
        i++;
    }
    while (i < HIGHT)
    {
        my_mlx_pixel_put(config, tex_values->x, i, config->floor_rgb);
        i++;
    }
}


void draw_player(t_config *config, t_player *player)
{
	int player_size = PLAYER_SIZE;
	int y = player->y - player_size / 2;
	while (y <= player->y + player_size / 2)
	{
		int x = player->x - player_size / 2;
		while (x <= player->x + player_size / 2)
		{
			my_mlx_pixel_put(config, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

void render_rays(t_config *config, t_player *player)
{
	int i = 0;
	double ray_angle;
	config->j = 0;
	while(i < WIDTH)
	{
		ray_angle = player->direction + (FOV / 2) - ((FOV / 1000) * i);
		cast_ray(config, player, ray_angle, (FOV / 2) - ((FOV / 1000) * i));
		i++;
	}
}

void rotate_player(t_player *player, double angle)
{
	player->direction += angle;
}

int key_hook(int keycode, void *param)
{
	t_config *config = (t_config *)param;
	if (keycode == 65307)
		exit(0);
	if (keycode == 115)
		 move_player(&config->player, &config->map, config->player.direction + M_PI);
	if (keycode == 119)
		move_player(&config->player, &config->map, config->player.direction);
	if (keycode == 100)
		move_player(&config->player, &config->map, config->player.direction - M_PI/2);
	if (keycode == 97)
		move_player(&config->player, &config->map, config->player.direction + M_PI/2);
	if (keycode == 65363)
		rotate_player(&config->player, -TURN_ANGLE);
	if (keycode == 65361)
		rotate_player(&config->player, +TURN_ANGLE);
	render_rays(config, &config->player);
	mlx_put_image_to_window(config->mlx, config->mlx_win, config->img, 0, 0);
	return (0);
}

bool is_valid_position(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->col_len * CELL_SIZE || y < 0
		|| y >= map->row_len * CELL_SIZE)
		return (false);
	if (map->map[y / CELL_SIZE][x / CELL_SIZE] == '1')
		return (false);
	return (true);
}

void move_player(t_player *player, t_map *map, double direction)
{
	double	new_x;
	double	new_y;

	new_x = player->x + cos(direction) * MOVE_SPEED;
	new_y = player->y - sin(direction) * MOVE_SPEED;
	if (is_valid_position(map, new_x, new_y)
		&& is_valid_position(map, new_x, player->y)
		&& is_valid_position(map, player->x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

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
	while(1)
	{
		if (xinter < 0 || yinter < 0 || xinter >= config->map.col_len * CELL_SIZE || yinter >= config->map.row_len * CELL_SIZE)
			break ;
		if (config->map.map[(int)yinter/ CELL_SIZE][(int)xinter / CELL_SIZE] == '1')
			break ;
		if (stepy < 0 && config->map.map[(int)yinter/ CELL_SIZE - 1][(int)xinter / CELL_SIZE] == '1')
			break ;
		xinter += stepx;
		yinter += stepy;
	}
	horizontal->x = xinter;
	horizontal->y = yinter;
	horizontal->distance = sqrt((ray.ray_x - horizontal->x) * (ray.ray_x - horizontal->x) +
							(ray.ray_y - horizontal->y) * (ray.ray_y - horizontal->y)); 
}

void	find_vertical_intersection(t_config *config, t_ray ray, double angle, t_intersection *vertical)
{
    double	yinter;
	double	xinter;
    double	stepx;
    double	stepy;

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
		if (xinter < 0 || yinter < 0 || xinter >= config->map.col_len * CELL_SIZE
			|| yinter >= config->map.row_len * CELL_SIZE)
			break ;
		
		if (config->map.map[(int)yinter/ CELL_SIZE][(int)xinter / CELL_SIZE] == '1')
			break;
		if (stepx < 0 && config->map.map[(int)yinter / CELL_SIZE][(int)xinter / CELL_SIZE - 1] == '1')
			break ;
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
    // double from;
    // double to;
    t_ray ray;
    t_intersection horizontal, vertical;
    // t_texture *current_texture;

    angle = remainder(angle, M_PI * 2);
    if (angle < 0)
        angle += 2 * M_PI;

    init_ray(&ray, player, angle);
    initialize_intersections(&horizontal, &vertical);
    find_horizontal_intersection(config, ray, angle, &horizontal);
    find_vertical_intersection(config, ray, angle, &vertical);
    horizontal.distance *= cos(t);
    vertical.distance *= cos(t);
    t_set_tex tex_values;
    tex_values.x = config->j++;
    tex_values.y = 0; // You can set this value based on your logic
    tex_values.i = 0; // Starting value
    if (horizontal.distance < vertical.distance)
    {
        tex_values.high = get_hight(horizontal.distance);
        tex_values.from = (HIGHT / 2) - tex_values.high / 2;
        if (sin(angle) > 0)
            tex_values.current_texture = &config->nt; // North
        else
            tex_values.current_texture = &config->st; // South
    }
    else
    {
        tex_values.high = get_hight(vertical.distance);
        tex_values.from = (HIGHT / 2) - tex_values.high / 2;
        if (cos(angle) > 0)
            tex_values.current_texture = &config->wt; // West
        else
            tex_values.current_texture = &config->et; // East
    }
    draw_wall(config, &tex_values);
}

void init_ray(t_ray *ray, t_player *player, double angle)
{
	ray->ray_x = player->x;
	ray->ray_y = player->y;
	ray->ray_dx = cos(angle);
	ray->ray_dy = sin(angle);
}

int initialize_graphics(t_config *config)
{
	config->mlx = mlx_init();
	if (!config->mlx)
		return (0);
	config->mlx_win = mlx_new_window(config->mlx, WIDTH, HIGHT, "Hello World!");
	if (!config->mlx_win)
		return (0);
	config->img = mlx_new_image(config->mlx, WIDTH, HIGHT);
	if (!config->img)
		return (0);
	config->data.addr = mlx_get_data_addr(config->img, &config->data.bits_per_pixel, &config->data.line_length, &config->data.endian);
	if (!config->data.addr)
		return (0);
	return (1);
}

int exit_game(void)
{
	exit(1);
}

int main(int argc, char *argv[])
{
	t_config config;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	config = initialize_game(argv[1]);
	config.player.x = config.player.x * CELL_SIZE + 20;
	config.player.y = config.player.y * CELL_SIZE + 20;
	printf("\n\nx : %f  |  y : %f\n\n map.size: %d\n", config.player.x, config.player.y,config.map.row_len);
	if (!initialize_graphics(&config))
	{
		fprintf(stderr, "Error initializing graphics.\n");
		return (EXIT_FAILURE);
	}
	mlx_put_image_to_window(config.mlx, config.mlx_win, config.img, 0, 0);
	mlx_hook(config.mlx_win, 2, 1, key_hook, &config);
	mlx_hook(config.mlx_win, 17, 0, exit_game, NULL);
	mlx_put_image_to_window(config.mlx, config.mlx_win, config.img, 0, 0);
	mlx_loop(config.mlx);
	return (EXIT_SUCCESS);
}


