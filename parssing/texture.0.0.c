/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.0.0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:06:36 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/28 14:52:16 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	valid_extension(char *file_name, char *extension)
{
	int	i;
	int	len;

	i = 3;
	len = ft_strlen(file_name);
	if (len <= 4)
		return (0);
	while (i >= 0)
	{
		if (file_name[--len] != extension[i])
			return (0);
		i--;
	}
	return (1);
}

static void	parse_texture(char *line, t_config *cf)
{
	char	**parts;

	parts = ft_split(line, " \t");
	if (!parts || !parts[0] || !parts[1])
	{
		freeall(parts);
		return ;
	}
	if (ft_strcmp(parts[0], "NO") == 0)
		cf->north_path = store_texture(cf->north_path, line, cf);
	else if (ft_strcmp(parts[0], "SO") == 0)
		cf->south_path = store_texture(cf->south_path, line, cf);
	else if (ft_strcmp(parts[0], "WE") == 0)
		cf->west_path = store_texture(cf->west_path, line, cf);
	else if (ft_strcmp(parts[0], "EA") == 0)
		cf->east_path = store_texture(cf->east_path, line, cf);
	else if (ft_strcmp(parts[0], "C") == 0)
		cf->ceiling = store_texture(cf->ceiling, line, cf);
	else if (ft_strcmp(parts[0], "F") == 0)
		cf->floor = store_texture(cf->floor, line, cf);
	else if (parts[0][0] != '\n')
		external_error("Option not included", EXIT_FAILURE, parts);
	freeall(parts);
}

static int	open_config_file(char *file_name)
{
	int	fd;

	if (!valid_extension(file_name, ".cub"))
		external_error("extention must be .cub at the end", EXIT_FAILURE, NULL);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		external_error("No such file or directory", EXIT_FAILURE, NULL);
	return (fd);
}

void	start_parse_textures(t_config *config)
{
	char	*line;

	while (1)
	{
		if (config->nbr_instru >= 6)
			break ;
		line = get_line(config->fd);
		if (line && *line && config->nbr_instru < 6)
			parse_texture(line, config);
		else
		{
			if (line)
				free(line);
			break ;
		}
		free(line);
	}
}

int	parsing_texture(t_config *c, char *file_name)
{
	initiate_textures_with_null(c);
	c->fd = open_config_file(file_name);
	start_parse_textures(c);
	if (!incomplete_inst(c))
		external_error("Incomplete instructions", EXIT_FAILURE, NULL);
	if (!valid_color_schema(c->ceiling) || !valid_color_schema(c->floor))
		external_error("Invalid color schema", EXIT_FAILURE, NULL);
	else
	{
		start_converting(c->ceiling_color, c->ceiling, &(c->ceiling_rgb));
		start_converting(c->floor_color, c->floor, &(c->floor_rgb));
	}
	return (1);
}
