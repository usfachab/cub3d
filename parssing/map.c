/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:34:09 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/26 14:04:45 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	surronded(char **map, int x, int y)
{
	if (x == 0 || y == 0)
		external_error("Wall not closed 1", EXIT_FAILURE, map);
	if (map[x + 1] == NULL || map[x][y + 1] == 0)
		external_error("Wall not closed 2", EXIT_FAILURE, map);
	if (map[x][y - 1] == ' ')
		external_error("Wall not closed 3", EXIT_FAILURE, map);
	if (map[x][y + 1] == ' ')
		external_error("Wall not closed 4", EXIT_FAILURE, map);
	if (map[x - 1][y] == ' ')
		external_error("Wall not closed 5", EXIT_FAILURE, map);
	if (map[x + 1][y] == ' ')
		external_error("Wall not closed 6", EXIT_FAILURE, map);
}

double	direction(char c)
{
	if (c == 'N')
		return (M_PI / 2);
	else if (c == 'S')
		return ((3 * M_PI) / 2);
	else if (c == 'E')
		return (0);
	if (c == 'W')
		return (M_PI);
	return (0);
}

int	valid_pos(char **map, double *x, double *y, double *c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (strchr("NSEW", map[i][j]))
			{
				*x = j;
				*y = i;
				*c = direction(map[i][j]);
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

int	check_wall(char **minimap)
{
	int	x;
	int	y;
	// int count;

	x = 0;
	// count = 0;
	while (minimap[x])
	{
		y = 0;
		while (minimap[x][y])
		{
			if (strchr("0SNEW", minimap[x][y])) // !rod lbal
				surronded(minimap, x, y);
			y++;
		}
		x++;
	}
	return (1);
}

int	valid_map(char **map)
{
	if (!check_wall(map))
		return (0);
	return (1);
}

char	valid_elem_handshake(char c)
{
	int		i;
	char	a;
	char	*elem;
	
	i = 0;
	a = 0;
	elem = " \n01NSEW";
	while(elem[i])
	{
		if (c == elem[i])
			a = c;
		i++;
	}
	return (a);
}

int	valid_elem(char *map)
{
	int		i;
	// int		j;
	int		nl;
	char	c;

	i = 0;
	nl = 0;
	while (map && map[i] == '\n')
		i++;
	while (map && map[i])
	{
		// j = 0;
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

char	*read_line(int fd)
{
	ssize_t	readed;
	char	*buffer;
	char	*str;

	str = ft_strdup("\0");
	buffer = malloc(sizeof(char) * 2);
	if (!buffer)
		return (NULL);
	while (1)
	{
		readed = read(fd, buffer, 1);
		buffer[readed] = 0;
		if (readed == -1)
			return (NULL);
		if (readed == 0)
			break ;
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

int	longest_line(char **map)
{
	int	longest;
	int	len;
	int	i;

	i = 0;
	len = 0;
	longest = 0;
	while (map && map[i])
	{
		len = ft_strlen(ft_strtrim(map[i]));
		if (len > longest)
			longest = len;
		i++;
	}
	return (longest);
}

char	**re_allocate(char **map)
{
	int		i;
	int		len;
	int		longest;
	char	**minimap;

	i = 0;
	len = 0;
	longest = longest_line(map);
	while (map[len])
		len++;
	minimap = malloc((len + 1) * sizeof(char *));
	if (!minimap)
		external_error("", EXIT_FAILURE, minimap);
	while (i < len)
	{
		minimap[i] = malloc(longest + 1);
		ft_bspace(minimap[i], longest);
		memmove(minimap[i], map[i], ft_strlen(map[i])); // ! free map
		minimap[i][longest] = 0;
		i++;
	}
	minimap[i] = NULL;
	return (minimap);
}

void	save_row_col_len(t_config *config)
{
	int 	i;
	char	**map;

	i = 0;
	map = config->map.map;
	if (!map && !map[i])
		external_error("Invalid map", EXIT_FAILURE, map);
	config->map.col_len = ft_strlen(map[i]) - 1;
	while (map && map[i])
		i++;
	config->map.row_len = i - 1;
	
}

int	parsing_map(t_config *config)
{
	char	*map;
	char	**split_config;
	char 	**minimap;
	// int		longest;

	// longest = 0;
	map = read_line(config->fd);
	if (!valid_elem(map))
		external_error("Invalid map 1", EXIT_FAILURE, &map);
	split_config = ft_split(map, "\n");
	if (!split_config[0])
		external_error("Invalid map 0", EXIT_FAILURE, split_config);
	minimap = re_allocate(split_config); // ! free minimap
	if (!valid_pos(minimap, &(config->player.x),
		&(config->player.y), &(config->player.direction)))
		external_error("Invalid map 1-1", EXIT_FAILURE, minimap);
	if (!valid_map(minimap))
		external_error("Invalid map 2", EXIT_FAILURE, minimap);
	config->map.map = minimap;
	save_row_col_len(config);
	return (1);
}
