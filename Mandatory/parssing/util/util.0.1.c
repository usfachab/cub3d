/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.0.1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:34:44 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/28 14:56:30 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	external_error(char *str, int errnum, char **ptr)
{
	printf("Error: %s\n", str);
	freeall(ptr);
	exit (errnum);
}

char	*get_line(int fd)
{
	char	*buffer;
	char	*result;
	ssize_t	readed;

	buffer = malloc(sizeof(char) * 2);
	if (!buffer)
		return (NULL);
	result = NULL;
	result = ft_strdup("\0");
	while (1)
	{
		readed = read(fd, buffer, 1);
		buffer[1] = 0;
		if (readed == -1)
			external_error("Read have failed", EXIT_FAILURE, &result);
		if (readed == 0)
			break ;
		result = ft_strjoin(result, buffer);
		if (strchr(result, '\n'))
			break ;
	}
	free(buffer);
	return (result);
}

void	ft_bspace(void *s, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 32;
		i++;
	}
}

long	ft_atoi(char *str)
{
	int					i;
	unsigned long long	res;

	i = 0;
	res = 0;
	while (str && str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		i++;
	}
	i = 0;
	while (str && str[i] >= 48 && str[i] <= 57)
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	if (res > 255)
		return (-1);
	return (res);
}
