/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:53:22 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/18 15:53:22 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_init(int line)
{
	char	**init;

	init = malloc(sizeof(char *) * (line + 1));
	if (!init)
		return (write(1, "Error\nmalloc fail", 17), NULL);
	init[0] = 0;
	return (init);
}

int	ft_file_line(char *map_path)
{
	int		line;
	char	*dest;
	int		fd;

	fd = open(map_path, O_RDONLY);
	line = 0;
	while (line == 0 || dest != NULL)
	{
		dest = get_next_line(fd);
		if (dest == NULL)
			break ;
		free (dest);
		line++;
	}
	return (close (fd), line);
}

int	ft_longuestline(char *map_path, int i)
{
	int		max;
	int		fd;
	char	*dest;

	max = 0;
	fd = open(map_path, O_RDONLY);
	while (max == 0 || dest != NULL)
	{
		dest = get_next_line(fd);
		if (!dest)
			break ;
		if (ft_specialstrlen(dest) > max)
			max = ft_strlen(dest);
		free (dest);
		i++;
	}
	return (close (fd), max);
}

char	*ft_alloc_line(char *dest, char *temp, int large, int j)
{
	dest = malloc(sizeof(char) * (large + 1));
	if (!dest)
		return (NULL);
	while (j < large)
	{
		if (j >= ft_specialstrlen(temp))
			dest[j] = ' ';
		else
			dest[j] = temp[j];
		j++;
	}
	dest[j - 1] = '\0';
	free (temp);
	return (dest);
}

char	**ft_alloc_map(char *map_path, int i, int j, int large)
{
	char	**dest;
	char	*temp;
	int		fd;
	int		line;

	line = ft_file_line(map_path);
	large = ft_longuestline(map_path, 0);
	dest = ft_init(line);
	if (!dest)
		return (NULL);
	fd = open(map_path, O_RDONLY);
	while (i < line)
	{
		j = 0;
		temp = get_next_line(fd);
		dest[i] = ft_alloc_line(dest[i], temp, large, j);
		if (!dest[i])
			return (NULL);
		i++;
	}
	dest[i] = 0;
	return (close (fd), dest);
}
