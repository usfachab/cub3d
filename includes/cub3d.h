/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:25:41 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/27 20:42:30 by yachaab          ###   ########.fr       */
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
	double		to;
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



typedef struct s_intersection {
	double	x;
	double	y;
	double	distance;
	int		hit;
}	t_intersection;



//libft
// int			ft_/strlen(char *str);

//drawing
void		my_mlx_pixel_put(t_config *config, int x, int y, int color);
void		clear_window(t_config *config);
void		render_map(t_config *config, t_map *map);
void		draw_player(t_config *config, t_player *player);
// void		draw_wall(t_config *config, double from, double to, int j);
void draw_wall(t_config *config, t_set_tex *tex_values);

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
void		init_ray(t_ray *ray, t_player *player, double angle);


// ! PARSING
/*--------------- UTILS -----------------*/
int			ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, const char *s2);
char		**ft_split(char *str, char *del);
int			count_word(const char *string, char *delim);
char		*get_line(int fd);
void		external_error(char *str, int errnum, char **ptr);
char		*ft_strtrim(char *str);
int			ft_strcmp(char *s1, char *s2);
long		ft_atoi(char *str);
/*--------------- TEXTURES ----------------*/
int			parsing_texture(t_config *c, char *file_name);
char		*store_texture(char *texture, char *value, t_config *config);
int			incomplete_inst(t_config *config);
int			valid_color_schema(char *str);
void		start_converting(int *arr, char *str, int *rgb);
int			setup_texture(t_config *config);
/*--------------- MAP ---------------------*/
int			parsing_map(t_config *config);
void		ft_bspace(void *s, int n);
t_config	initialize_game(char *filename);

void		free_config_resources(t_config *config);
#endif