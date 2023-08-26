/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:13:35 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/26 14:08:52 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

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