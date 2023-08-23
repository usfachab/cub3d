/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:17:35 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/23 17:36:50 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct  s_config
{
	int		fd;
    char	**map;
    char	*north_texture;
    char	*south_texture;
    char	*east_texture;
    char	*west_texture;
	char	*ceiling;
	char	*floor;
	int		nbr_instru;
    int		floor_color[3];
    int		ceiling_color[3];
	int		floor_rgb;
	int		ceiling_rgb;
    // float	player_pos_x;
    // float	player_pos_y;
    // int		map_rows;
    // int		map_cols;
    // char	player_start_direction;
}	t_config;
/* --------------- util.c --------------- */
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, const char *s2);
char	**ft_split(char *str, char *del);
int		count_word(const char *string, char *delim);
char	*get_line(int fd);
void	external_error(char *str, int errnum);
char	*ft_strtrim(char *str);
int		ft_strcmp(char *s1, char *s2);
long	ft_atoi(char *str);
// ?--------------- TEXTURES ----------------? //
int		parsing_texture(t_config *c, char *file_name);
char	*store_texture(char *texture, char *value, t_config *config);
int		incomplete_inst(t_config *config);
int		valid_color_schema(char *str);
void	start_converting(int *arr, char *str, int *rgb);
// ?--------------- MAP ----------------? //
int		parsing_map(t_config *config);
#endif
