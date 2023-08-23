/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachaab <yachaab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:09:22 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/23 17:33:52 by yachaab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pars.h"

int	main(int argc, char *argv[])
{
	t_config	config;

	if (argc != 2)
		external_error("number of arguments not true.", EXIT_FAILURE);
	if (!parsing_texture(&config, argv[1]))
		return (1);
	if (!parsing_map(&config))
		return (1);
	return (0);
}