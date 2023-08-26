/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:17:49 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/26 10:57:47 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

long	ft_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	sign = 1;
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
	return (res * sign);
}