
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <mlx.h>
#include <math.h>
#include <limits.h>

#define CELL_SIZE 40
#define PLAYER_SIZE 10
#define MOVE_SPEED 5
#define TURN_ANGLE (M_PI / 60)
#define HIGHT 1000
#define WIDTH 1000
#define MOUSE_SPEED 0.05
#define FOV (M_PI / 3)
// #define MINIMAP_SCALE 0.2
// #define MINIMAP_WIDTH (WIDTH * MINIMAP_SCALE)
// #define MINIMAP_HEIGHT (HIGHT * MINIMAP_SCALE)
# define MINIMAP_SIZE 200
# define MINIMAP_SCALE 5
#define MINIMAP_CELL_SIZE (CELL_SIZE * MINIMAP_SCALE)
#define MINIMAP_PLAYER_SIZE (PLAYER_SIZE * MINIMAP_SCALE)
typedef struct
{
	double ray_x;
	double ray_y;
	double ray_dx;
	double ray_dy;
	double distance;
} t_ray;



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

typedef struct s_set_tex
{
	double		high; //hight of the wall
	double		from; //begin of the wall
	double		x; //cordonate of the wall on x
	double		y; //cordonate of the wall on y
	int			i; //that used in draw_wall
	t_texture	*current_texture; //texture that will used
	double		to;
}	t_set_tex;

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
typedef struct s_data
{
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int 	endian;
}	t_data;
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
	int			last_mouse_x;
    int			mini_map_scale;
	int			color;
}	t_config;

typedef struct s_plit
{
	int		i;
	int		j;
	int		y;
	char	**resl;
}			t_split;

enum Colors
{
    COLOR_BLACK = 0,
    COLOR_WHITE = 0xFFFFFF,
    COLOR_RED = 0xFF0000,
    COLOR_GREEN = 0x00FF00,
    COLOR_BLUE = 0x0000FF
};

typedef struct s_intersection {
	double	x;
	double	y;
	double	distance;
	int		hit;
}	t_intersection;




void    my_mlx_pixel_put(t_config *config, int x, int y, int color)
{
	char *dst;

	dst = config->data.addr + (y * config->data.line_length + x * (config->data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int    get_texture_pixel(t_set_tex *set)
{
	double  y;
	char    *dst;

	y = set->current_texture->height * ((set->i - set->from) / set->high);
	dst = set->current_texture->addr + ((int)y * set->current_texture->line_length + (int)set->x * (set->current_texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void draw_wall(t_config *config, t_set_tex *tex_values)
{
    tex_values->i = 0;
    double from = tex_values->from;
    double to = from + tex_values->high;

	tex_values->x = tex_values->current_texture->width * ((tex_values->x + tex_values->y) - ((int)(tex_values->x + tex_values->y) / CELL_SIZE) * CELL_SIZE) / CELL_SIZE;
    
	tex_values->to = to;
	config->color = 0;
    while (tex_values->i < from && tex_values->i < HIGHT)
    {
        my_mlx_pixel_put(config, config->j, tex_values->i, config->ceiling_rgb);
        tex_values->i++;
    }
    while (tex_values->i < to && tex_values->i < HIGHT)
    {
        config->color = get_texture_pixel(tex_values);
		my_mlx_pixel_put(config, config->j, tex_values->i, config->color);
        tex_values->i++;
    }
    while (tex_values->i < HIGHT)
    {
        my_mlx_pixel_put(config, config->j, tex_values->i, config->floor_rgb);
        tex_values->i++;
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
    while(i < 1000)
    {
        ray_angle = player->direction + (FOV / 2) - ((FOV / 1000) * i);
        cast_ray(config, player, ray_angle, (FOV / 2) - ((FOV / 1000) * i));
        i++;
    }
}

void	rotate_player(t_player *player, double angle)
{
    player->direction += angle;
}

int key_hook(int keycode, void *param)
{
	t_config *config = (t_config *)param;
	if (keycode == 65307)
	{
		// free_config_resources(config);
		mlx_destroy_window(config->mlx, config->mlx_win);
		exit(0);
	}
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

void	move_player(t_player *player, t_map *map, double direction)
{
	double new_x, new_y;
	const double buffer = 1;

	new_x = player->x + cos(direction) * MOVE_SPEED;
	new_y = player->y - sin(direction) * MOVE_SPEED;
	if (is_valid_position(map, new_x + buffer * cos(direction), player->y))
		player->x = new_x;
	if (is_valid_position(map, player->x, new_y - buffer * sin(direction)))
		player->y = new_y;
}

int mouse_move(int x, int y, void *param)
{
	(void)y;
	t_config *config = (t_config *)param;

	if (x < config->last_mouse_x)
		rotate_player(&config->player, MOUSE_SPEED);
	else if (x > config->last_mouse_x)
		rotate_player(&config->player, -MOUSE_SPEED);
	config->last_mouse_x = x;
	render_rays(config, &config->player);
	mlx_put_image_to_window(config->mlx, config->mlx_win, config->img, 0, 0);
	return (0);
}

double	get_hight(double dis)
{
	double	r_dis;
	double	hight;

	r_dis = (HIGHT / 2);
	hight = (r_dis * 40) / dis;
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

void	initialize_intersections(t_intersection *horizontal, t_intersection *vertical)
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
	double	xinter;
	double	yinter;
	double	stepx;
	double	stepy;

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
		if (stepy < 0 && yinter >= CELL_SIZE && config->map.map[(int)yinter/ CELL_SIZE - 1][(int)xinter / CELL_SIZE] == '1')
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
		if (stepx < 0 && xinter >= CELL_SIZE && config->map.map[(int)yinter / CELL_SIZE][(int)xinter / CELL_SIZE - 1] == '1')
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
	t_set_tex tex_values;
	if (horizontal.distance < vertical.distance)
	{
		tex_values.x = horizontal.x;
		tex_values.y = horizontal.y;
		tex_values.high = get_hight(horizontal.distance);
		tex_values.from = (HIGHT / 2) - tex_values.high / 2;
		if (sin(angle) > 0)
			tex_values.current_texture = &(config->nt); // Nort
		else
			tex_values.current_texture = &config->st; // South
	}
	else
	{
		tex_values.x = vertical.x;
		tex_values.y = vertical.y;
		tex_values.high = get_hight(vertical.distance);
		tex_values.from = (HIGHT / 2) - tex_values.high / 2;
		if (cos(angle) > 0)
			tex_values.current_texture = &config->wt; // West
		else
			tex_values.current_texture = &config->et; // East
	}
	draw_wall(config, &tex_values);
	config->j++;
}


void    draw_minimap(t_config *config)
{
    int y = 0;
    while (y < config->map.row_len * CELL_SIZE)
    {
        int x = 0;
        while (x < config->map.col_len * CELL_SIZE)
        {
            int color = COLOR_GREEN;

            if (config->map.map[y / CELL_SIZE][x / CELL_SIZE] == '1')
                color = COLOR_WHITE;
            else if (config->map.map[y / CELL_SIZE][x / CELL_SIZE] == 'D')
                color = COLOR_RED;
            else if (config->map.map[y / CELL_SIZE][x / CELL_SIZE] == 'd')
                color = COLOR_BLUE;

            // Check if the current position is near the player to draw the player
            if (fabs(x - config->player.x) <= PLAYER_SIZE/2 && fabs(y - config->player.y) <= PLAYER_SIZE/2)
                color = COLOR_BLACK;
            // Draw the pixel on the minimap
            my_mlx_pixel_put(config, x / config->mini_map_scale, y / config->mini_map_scale, color);
            
            x += config->mini_map_scale;
        }
        y += config->mini_map_scale;
    }
}

void init_ray(t_ray *ray, t_player *player, double angle)
{
	ray->ray_x = player->x;
	ray->ray_y = player->y;
	ray->ray_dx = cos(angle);
	ray->ray_dy = sin(angle);
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
        return EXIT_FAILURE;
    }
    config.j = 0;
    config.mini_map_scale = 8;
    config.last_mouse_x = WIDTH / 2;
	config = initialize_game(argv[1]);
    config.player.x = config.player.x * CELL_SIZE + 20;
	config.player.y = config.player.y * CELL_SIZE + 20;
    config.mlx = mlx_init();
    if (!config.mlx)
    {
        fprintf(stderr, "Error initializing MLX.\n");
        return EXIT_FAILURE;
    }

    config.mlx_win = mlx_new_window(config.mlx, HIGHT, WIDTH, "Hello World!");
    if (!config.mlx_win)
    {
        fprintf(stderr, "Error creating window.\n");
        return EXIT_FAILURE;
    }
    config.img = mlx_new_image(config.mlx, HIGHT, WIDTH);
    if (!config.img)
    {
        fprintf(stderr, "Error creating image.\n");
        return EXIT_FAILURE;
    }
    config.data.addr = mlx_get_data_addr(config.img, &config.data.bits_per_pixel, &config.data.line_length, &config.data.endian);
    if (!config.data.addr)
    {
        fprintf(stderr, "Error getting data address.\n");
        return EXIT_FAILURE;
    }
    mlx_put_image_to_window(config.mlx, config.mlx_win, config.img, 0, 0);
    mlx_hook(config.mlx_win, 2, 1, key_hook, &config);
    mlx_hook(config.mlx_win, 6, 1L << 6, mouse_move, &config); // 64 in decimal
    mlx_hook(config.mlx_win, 17, 0, exit_game, NULL);
    mlx_put_image_to_window(config.mlx, config.mlx_win, config.img, 0, 0);
    // mlx_loop_hook(config.mlx, , &config);
    mlx_loop(config.mlx);
    mlx_destroy_window(config.mlx, config.mlx_win);
    return (EXIT_SUCCESS);
}
