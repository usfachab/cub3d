/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.0.2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:03:23 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/29 23:20:31 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s && s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!d && !s)
		return (0);
	if (d < s)
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	if (d > s)
	{
		i = len;
		while (i--)
			d[i] = s[i];
	}
	return ((void *)d);
}

char	valid_elem_handshake(char c)
{
	int		i;
	char	a;
	char	*elem;

	i = 0;
	a = 0;
	elem = " \n01NSEW";
	while (elem[i])
	{
		if (c == elem[i])
			a = c;
		i++;
	}
	return (a);
}

void	freeall(char **ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	if (ptr)
		free(ptr);
}

void	initiate_textures_with_null(t_config *config)
{
	config->north_path = NULL;
	config->south_path = NULL;
	config->east_path = NULL;
	config->west_path = NULL;
	config->ceiling = NULL;
	config->floor = NULL;
	config->nbr_instru = 0;
	config->ceiling_rgb = 0;
	config->floor_rgb = 0;
	config->player.x = 0;
	config->player.y = 0;
	config->player.direction = 0;
	config->anime_index = 0;
	config->mlx = mlx_init();
	if (!config->mlx)
		external_error("init mlx", EXIT_FAILURE, config->mlx);
}
