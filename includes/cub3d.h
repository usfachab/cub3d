/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:25:41 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/26 10:15:40 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

// !RENDRING
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



//libft
int			ft_strlen(char *str);

//drawing
void		my_mlx_pixel_put(t_config *config, int x, int y, int color);
void		clear_window(t_config *config);
void		render_map(t_config *config, t_map *map);
void		draw_player(t_config *config, t_player *player);
void		draw_wall(t_config *config, double from, double to, int j);

//ray_casting
void		cast_ray(t_config *config, t_player *player, double angle, double t);
void		initialize_intersections(t_intersection *horizontal, t_intersection *vertical);
void		find_horizontal_intersection(t_config *config, t_ray ray, double angle, t_intersection *horizontal);
void		find_vertical_intersection(t_config *config, t_ray ray, double angle, t_intersection *vertical);
double		get_hight(double dis);
void		from_to(double *from, double *to, double hight);
bool		is_ray_colliding(t_map *map, t_ray *ray);
void		init_ray(t_ray *ray, t_player *player, double angle);
void		render_rays(t_config *config, t_player *player);

//key_hook
void		rotate_player(t_player *player, double angle);
int			key_hook(int keycode, void *param);
bool		is_valid_position(t_map *map, int x, int y);
void		move_player(t_player *player, t_map *map, double direction);
void		free_map(t_map *map);
int			initialize_graphics(t_config *config);

//main function and utils
void		init_ray(t_ray *ray, t_player *player, double angle);
void		init_ray(t_ray *ray, t_player *player, double angle);
void		initialize_game(t_config *config, char *map_file);
void		handle_error(char *message);
char		**ft_split(char *str, int row_len, int col_len);
void		calculate_map_size(char *buffer, int bytes_read, int *row_len, int *col_len);
void		read_map(char *filename, t_map *map);

#endif