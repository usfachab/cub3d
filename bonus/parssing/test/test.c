// void	read_config_file_and_store_nsewcf(int fd, t_config *config)
// {
// 	int		i;
// 	int		count;
// 	char	*config_file;
// 	char	**splited;
// 	char	*br;
// 	char	*holdem;
// 	char	*cmds[5];

// 	cmds[0] = "NO";
// 	cmds[1] = "SO";
// 	cmds[2] = "WE";
// 	cmds[3] = "EA";
// 	cmds[4] = NULL;
	
// 	config_file = read_all_config_file(fd);
// 	count = 0;
// 	while (config_file && *config_file && count < 4)
// 	{
// 		br = strchr(config_file, '\n');
// 		holdem = ft_strdup(config_file);
// 		if (br)
// 			holdem[br - config_file] = 0;
// 		if (count_word(holdem, " \t") > 2)
// 			external_error("Texture path has more than one argument", EXIT_FAILURE);
// 		if (ft_strlen(holdem) > 2)
// 			splited = ft_split(holdem, " \t");
// 		else
// 			splited = NULL;
// 		free(holdem);
// 		i = 0;
// 		while (cmds[i] && splited && splited[1])
// 		{
// 			printf("cmd[i]: %s | splited[0] : %s\n", cmds[i], splited[0]);
// 			if (!strcmp(cmds[i], splited[0]))
// 			{
// 				if (!config->textures[i])
// 					config->textures[i] = splited[1];
// 				else
// 					external_error("Duplicate option", EXIT_FAILURE);
// 				count += 1;
// 				free(splited[0]);
// 				splited[0] = NULL;
// 				break ;
// 			}
// 			i++;
// 		}
// 		if (i > 4)
// 			external_error("invalid option or missing one", EXIT_FAILURE);
// 		if (!br)
// 			break ;
// 		config_file = br + 1;
// 	}
	
// }

// while (str && str[i])
	// {
	// 	while (str[i] == 32 || str[i] == '\t')
	// 		i++;
	// 	if (str[i] == ',')
	// 		external_error("comma2", EXIT_FAILURE);
	// 	while (str[i] >= 48 && str[i] <= 57)
	// 	{
	// 		nbr = nbr * 10 + (str[i] - 48);
	// 		i++;
	// 	}
	// 	while (str[i] == 32 || str[i] == '\t')
	// 		i++;
	// 	if ( str[i] && str[i] != ',')
	// 		external_error("comma", EXIT_FAILURE);
	// 	else
	// 		i++;
	// }


// 	char	isdel(char *del, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (del[i])
// 	{
// 		if (del[i] == c)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }


// if (!isdel(delim, string[i])
// 			&& (!isdel(delim, string[i + 1])
// 				|| string[i + 1] == '\0'))


// printf("rgb: %d\n", c->floor_rgb);
// printf("rgb: %d\n", c->ceiling_rgb);
// printf("NO: %s\n", c->north_texture);
// printf("SO: %s\n", c->south_texture);
// printf("EA: %s\n", c->east_texture);
// printf("WE: %s\n", c->west_texture);
// printf("C: %s\n", c->ceiling);
// printf("F: %s\n", c->floor);
// for (int i = 0; i < 3; i++)
// {
// 	printf("C[%d]: %d\n", i, c->ceiling_color[i]);
// }
// for (int i = 0; i < 3; i++)
// {
// 	printf("C[%d]: %d\n", i, c->floor_color[i]);
// }

// int	valid_wall(char *map)
// {
// 	int	i;

// 	i = 0;
// 	while (map && map[i])
// 	{
		
// 	}
// }

	// printf("rgb: %d\n", config.floor_rgb);
	// printf("rgb: %d\n", config.ceiling_rgb);
	// printf("NO: %s\n", config.north_path);
	// printf("SO: %s\n", config.south_path);
	// printf("EA: %s\n", config.east_path);
	// printf("WE: %s\n", config.west_path);
	// printf("C: %s\n", config.ceiling);
	// printf("F: %s\n", config.floor);
	// printf("X: %f\n", config.player.x);
	// printf("Y: %f\n", config.player.y);
	// printf("P: %f\n", config.player.direction);
	// for (int i = 0; config.map.map[i]; i++)
	// 	printf("%s\n", config.map.map[i]);
