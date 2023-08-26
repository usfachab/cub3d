/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:34:09 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/24 14:40:58 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pars.h"

int	row_len(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	col_len(char **map)
{
	int		i;
	size_t	last_row_len;

	i = 0;
	while (map[i])
		i++;
	i--;
	last_row_len = ft_strlen(map[i]);
	return (last_row_len);
}


int	check_wall(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[x])
	{
		while (map[y])
		{
			
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
	int		j;
	int		nl;
	char	c;

	i = 0;
	nl = 0;
	while (map && map[i] == '\n')
		i++;
	while (map && map[i])
	{
		j = 0;
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

int	parsing_map(t_config *config)
{
	int		i;
	char	*map;
	char	**parted_map;
	
	i = 0;
	map = read_line(config->fd);
	if (!valid_elem(map))
		external_error("Invalid map 1", EXIT_FAILURE);
	parted_map = ft_split(map, "\n");
	if (!valid_map(parted_map))
		external_error("Invalid map 2", EXIT_FAILURE);
	// for (int i = 0; parted_map[i]; i++)
	// 	printf("%s", parted_map[i]);
	// if (!valid_wall(map))
	// 	external_error("Unclosed wall", EXIT_FAILURE);
}

// ! 6 possible element : 0 1 N S E W space newline -> extra elem OK | the 6 elem exist NOK
// ! the map should surronded by wall -> workin on
