/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.0.1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:08:11 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/26 14:08:29 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void	start_converting(int *arr, char *str, int *rgb)
{
	char	**value;
	int		i;

	i = 0;
	value = ft_split(str, ",");
	while (value && value[i] && i < 3)
	{
		arr[i] = ft_atoi(ft_strtrim(value[i]));
		if (arr[i] == -1)
			external_error("Invalid color schema", EXIT_FAILURE, value);
		i++;
	}
	if (i != 3)
		external_error("Invalid color schema", EXIT_FAILURE, value);
	else
		*rgb = (arr[0] << 16 | arr[1] << 8 | arr[2]); // ! CHANGED BUT NOT TESTED
	while (value[i])
	{
		free(value[i]);
		i++;
	}
	free(value);
}

int	valid_color_schema(char *str)
{
	int i;
	int	comma_nbr;
	int	nbr_of_nbr;

	i = 0;
	comma_nbr = 0;
	nbr_of_nbr = 0;	
	while (str && str[i])
	{
		while (str[i] == 32 || str[i] == '\t')
			i++;
		if (str[i] == ',')
			comma_nbr += 1;
		else if(str[i] < 48 || str[i] > 57)
			return (0);
		else if (str[i] >= 48 && str[i] <= 57)
			nbr_of_nbr += 1;
		i++;
	}
	if (comma_nbr > 2 || nbr_of_nbr > 9 || nbr_of_nbr < 3)
		return (0);
	return (1);
}

int	incomplete_inst(t_config *config)
{
	if (!config->north_path || !config->south_path
		|| !config->east_path || !config->west_path
		|| !config->ceiling || !config->floor)
		return (0);
	else
		return (1);
}

static char	*trim_newline_get_only_value(char *value)
{
	char	*nl;
	char	*path;

	nl = strchr(value, '\n'); // !Rod lbal
	if (nl)
		value[nl - value] = 0;
	path = ft_strtrim(value + 2);
	//free(value);
	return (path);
}

char	*store_texture(char *path, char *value, t_config *config)
{
	char	*result;

	result = NULL;
	if (!path)
	{
		config->nbr_instru += 1;
		result = trim_newline_get_only_value(value);
		if (*result == 0)
			external_error("Invalide value was given", EXIT_FAILURE, &result);
		return (result);
	}
	else
		external_error("Duplicate option", EXIT_FAILURE, NULL);
	return (NULL);
}