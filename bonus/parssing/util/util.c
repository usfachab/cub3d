/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:15:35 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/26 15:07:34 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"



void	external_error(char *str, int errnum, char **ptr)
{
	printf("Error: %s\n", str);
	while (ptr && *ptr)
	{
		free(*ptr);
		ptr++;
	}
	exit (errnum);
}

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	ptr = malloc((i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	int	i;
	int	j;
	char	*ptr;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	ptr = malloc (((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	if (s1)
		free(s1);
	ptr[i + j] = '\0';
	return (ptr);
}

char *ft_strtrim(char *str)
{
	char	*trimmed;
	char	*start;
	char	*end;
	int		len;

    if (!str)
		return NULL;
    start = str;
	end = str + (ft_strlen(str) - 1);
    while ((*start == ' ' || *start == '\t') && *start)
		start++;
    while ((end > start) && (*end == ' ' || *end == '\t'))
		end--;
    len = end - start + 1;
    trimmed = (char *)malloc(len + 1);
    if (trimmed)
	{
        strncpy(trimmed, start, len); // !Rod lbal
   		trimmed[len] = '\0';
    }
    return (trimmed);
}


int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}
