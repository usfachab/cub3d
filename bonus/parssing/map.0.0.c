/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.0.0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:34:09 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/30 20:52:13 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	valid_pos(t_config *config)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (config->map.map && config->map.map[i])
	{
		j = 0;
		while (config->map.map[i][j])
		{
			if (strchr("NSEW", config->map.map[i][j]))
			{
				config->player.x = j;
				config->player.y = i;
				config->player.direction = direction(config->map.map[i][j]);
				count += 1;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (0);
	return (1);
}

int	valid_map(char **minimap)
{
	int	x;
	int	y;

	x = 0;
	if (!minimap)
		return (0);
	while (minimap[x])
	{
		y = 0;
		while (minimap[x][y])
		{
			if (ft_strchr("0SNEWD", minimap[x][y]))
				surronded(minimap, x, y);
			y++;
		}
		x++;
	}
	return (1);
}

int	valid_elem(char *map)
{
	int		i;
	int		nl;
	char	c;

	i = 0;
	nl = 0;
	while (map && map[i] == '\n')
		i++;
	while (map && map[i])
	{
		c = valid_elem_handshake(map[i]);
		if (c != map[i])
			return (0);
		while (map[i] && (map[i] == '\n' && map[i + 1] == '\n'))
		{
			nl += 2;
			i++;
		}
		if (map[i + 1] != 0 && nl >= 2)
			return (0);
		i++;
	}
	return (1);
}

char	**creat_minimap(int fd)
{
	char	*map;
	char	**split_config;
	char	**minimap;

	map = read_line(fd);
	if (!valid_elem(map))
		external_error("Invalid param", EXIT_FAILURE, NULL);
	split_config = ft_split(map, "\n");
	free(map);
	if (!split_config && !split_config[0])
		external_error("Invalid map", EXIT_FAILURE, NULL);
	minimap = re_allocate(split_config);
	freeall(split_config);
	return (minimap);
}

int	parsing_map(t_config *config)
{
	config->map.map = creat_minimap(config->fd);
	if (!valid_pos(config))
		external_error("Invalid map", EXIT_FAILURE, config->map.map);
	if (!valid_map(config->map.map))
		external_error("Invalid map", EXIT_FAILURE, config->map.map);
	save_row_col_len(config);
	return (1);
}
