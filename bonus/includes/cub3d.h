/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:51:25 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/30 21:06:51 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <ctype.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>

# define HIGHT 1000
# define WIDTH 1000
# define CELL_SIZE 40
# define MOVE_SPEED 10
# define PLAYER_SIZE 10
# define FOV 1.0471975511965976
# define TURN_ANGLE 0.05235987755982988
#define MOUSE_SPEED 0.05
# define WIDTH_MINIMAP 200
# define HIGH_MINIMAP 200

// !--------------- PARSING -----------------! //
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		endian;
	int		line_length;
	int		bits_per_pixel;
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

typedef struct s_data
{
	char	*addr;
	int		endian;
	int		line_length;
	int		bits_per_pixel;
}	t_data;

typedef struct s_config
{
	t_texture	anime[6];
	t_texture	nt;
	t_texture	st;
	t_texture	et;
	t_texture	wt;
	t_texture	door;
	t_map		map;
	t_data		data;
	t_player	player;
	void		*mlx;
	void		*img;
	void		*mlx_win;
	char		*floor;
	char		*ceiling;
	char		*east_path;
	char		*west_path;
	char		*north_path;
	char		*south_path;
	int			j;
	int			fd;
	int			color;
	int			floor_rgb;
	int			ceiling_rgb;
	int			nbr_instru;
	int			floor_color[3];
	int			ceiling_color[3];
	int			last_mouse_x;
	int			anime_index;
}	t_config;

// *-------------- UTILS -------------* //
char		*get_line(int fd);
long		ft_atoi(char *str);
char		*read_line(int fd);
char		*ft_strtrim(char *str);
int			ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
char		valid_elem_handshake(char c);
int			ft_strcmp(char *s1, char *s2);
char		**ft_split(char *str, char *del);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char *s1, const char *s2);
int			count_word(const char *string, char *delim);
void		initiate_textures_with_null(t_config *config);
void		external_error(char *str, int errnum, char **ptr);
void		*ft_memmove(void *dst, const void *src, size_t len);
// *------------- TEXTURES ------------* //
void		freeall(char **ptr);
int			valid_color_schema(char *str);
int			setup_texture(t_config *config);
int			incomplete_inst(t_config *config);
void		start_converting(int *arr, char *str, int *rgb);
int			parsing_texture(t_config *c, char *file_name);
char		*store_texture(char *texture, char *value, t_config *config);
// *--------------- MAP ---------------* //
double		direction(char c);
int			longest_line(char **map);
void		ft_bspace(void *s, int n);
char		**re_allocate(char **map);
int			parsing_map(t_config *config);
t_config	initialize_game(char *filename);
void		save_row_col_len(t_config *config);
void		surronded(char **map, int x, int y);
// ! newlly added by yachaab
int			setup_animation(t_config *c);
void		*img(void *mlx, char *pt, int *w, int *h);
char		*addr(void *img, int *bpp, int *ll, int *endi);

// !--------------- RENDRING -----------------! //
typedef struct s_intersection
{
	double	x;
	double	y;
	double	distance;
	int		hit;
	int		flage;
}	t_intersection;
enum Colors
{
    COLOR_BLACK = 0,
    COLOR_WHITE = 0xFFFFFF,
    COLOR_RED = 0xFF0000,
    COLOR_GREEN = 0x00FF00,
    COLOR_BLUE = 0x0000FF
};

typedef struct s_set_tex
{
	t_texture	*current_texture;
	double		x;
	double		y;
	double		to;
	double		high;
	double		from;
	int			i;
	int		flage;
}	t_set_tex;

typedef struct s_ray
{
	double	ray_x;
	double	ray_y;
	double	ray_dx;
	double	ray_dy;
	double	distance;
}	t_ray;

typedef struct s_draw_data
{
    int	x;
	int	y;
	int	px;
	int	py;
}	t_draw_data;

// *----------------- DRAW -----------------* //
void		draw_player(t_config *config, t_player *player);
void		draw_wall(t_config *config, t_set_tex *tex_values);
void		my_mlx_pixel_put(t_config *config, int x, int y, int color);
// *--------------- RAY CAST ---------------* //
double		get_hight(double dis);
void		render_rays(t_config *config, t_player *player);
void		from_to(double *from, double *to, double hight);
void		init_ray(t_ray *ray, t_player *player, double angle);
void		cast_ray(t_config *config,
				t_player *player, double angle, double t);
void		initialize_intersections(t_intersection *horizontal,
				t_intersection *vertical);
void		find_vertical_intersection(t_config *config, t_ray ray,
				double angle, t_intersection *vertical);
void		find_horizontal_intersection(t_config *config, t_ray ray,
				double angle, t_intersection *horizontal);
// *---------------- HOOKS ----------------* //
int			key_hook(int keycode, void *param);
int			initialize_graphics(t_config *config);
void		free_config_resources(t_config *config);
bool		is_valid_position(t_map *map, int x, int y);
void		rotate_player(t_player *player, double angle);
void		init_ray(t_ray *ray, t_player *player, double angle);
void		move_player(t_player *player, t_map *map, double direction);
int mouse_move(int x, int y, void *param);
void    draw_minimap(t_config *config);
#endif