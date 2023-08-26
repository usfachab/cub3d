/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:41:17 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/26 10:02:49 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

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
#define MINIMAP_SCALE 0.2
#define MINIMAP_WIDTH (WIDTH * MINIMAP_SCALE)
#define MINIMAP_HEIGHT (HIGHT * MINIMAP_SCALE)
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
	int last_mouse_x;
    int mini_map_scale;
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


// libft
int	ft_strlen(char *str);

// drawing
void    my_mlx_pixel_put(t_config *config, int x, int y, int color);
void    clear_window(t_config *config);
void    render_map(t_config *config, t_map *map);
void    draw_player(t_config *config, t_player *player);
void	draw_wall(t_config *config, double from, double to, int j);
void	render_rays(t_config *config, t_player *player);
void    draw_minimap(t_config *config);

// ray_casting
void	initialize_intersections(t_intersection *horizontal, t_intersection *vertical);
void    find_horizontal_intersection(t_config *config, t_ray ray, double angle, t_intersection *horizontal);
void	find_vertical_intersection(t_config *config, t_ray ray, double angle, t_intersection *vertical);
void    cast_ray(t_config *config, t_player *player, double angle, double t);
double	get_hight(double dis);
void	from_to(double *from, double *to, double hight);
void    init_ray(t_ray *ray, t_player *player, double angle);

// key_hook
void	rotate_player(t_player *player, double angle);
int     key_hook(int keycode, void *param);
bool	is_valid_position(t_map *map, int x, int y);
void    move_player(t_player *player, t_map *map, double direction);
int     mouse_move(int x, int y, void *param);

// utils
void    free_map(t_map *map);
void	read_map(char *filename, t_map *map);
void    handle_error(char *message);
char    **ft_split(char *str, int row_len, int col_len);
void    calculate_map_size(char *buffer, int bytes_read, int *row_len, int *col_len);
void	init_ray(t_ray *ray, t_player *player, double angle);

#endif