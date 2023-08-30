/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.0.1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:33:34 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/28 14:20:25 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	save_row_col_len(t_config *config)
{
	int		i;
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
		ft_memmove(minimap[i], map[i], ft_strlen(map[i]));
		minimap[i][longest] = 0;
		i++;
	}
	minimap[i] = NULL;
	return (minimap);
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
		len = ft_strlen(map[i]);
		if (len > longest)
			longest = len;
		i++;
	}
	return (longest);
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

void	surronded(char **map, int x, int y)
{
	if (x == 0 || y == 0)
		external_error("Wall not closed", EXIT_FAILURE, map);
	if (map[x + 1] == NULL || map[x][y + 1] == 0)
		external_error("Wall not closed", EXIT_FAILURE, map);
	if (map[x][y - 1] == ' ')
		external_error("Wall not closed", EXIT_FAILURE, map);
	if (map[x][y + 1] == ' ')
		external_error("Wall not closed", EXIT_FAILURE, map);
	if (map[x - 1][y] == ' ')
		external_error("Wall not closed", EXIT_FAILURE, map);
	if (map[x + 1][y] == ' ')
		external_error("Wall not closed", EXIT_FAILURE, map);
}
