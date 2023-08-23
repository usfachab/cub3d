/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:34:09 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/23 17:50:25 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pars.h"

int	parsing_map(t_config *config)
{
	char *line = get_line(config->fd);
	printf("Line: %s", line);
	return(1);
}