/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:43:59 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/18 15:43:59 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_infline(char *map_path)
{
	int		line;
	int		fd;
	int		obj;
	char	*dest;

	fd = open(map_path, O_RDONLY);
	line = 0;
	obj = 0;
	while ((line == 0 || dest != NULL))// && obj != 6)
	{
		dest = get_next_line(fd);
		if (dest == NULL)
			break ;
		if (!ft_checkobj(dest, obj))
			obj++;
		free (dest);
		line++;
	}
	if (obj != 6)
		return (close (fd), line);
	return (close (fd), 6);
}

char	**ft_getinf(char *map_path, int i)
{
	char	**dest;
	char	*temp;
	int		fd;
	int		line;

	line = ft_infline(map_path);
	if (!line || line != 6)
		return (printf("Error\ninfo are badly placed\n"), NULL);
	dest = ft_init(line);
	if (!dest)
		return (printf("Error\nBad allocation\n"), NULL);
	fd = open(map_path, O_RDONLY);
	while (i < line)
	{
		temp = get_next_line(fd);
		if (ft_ischar(temp, '\n'))
			temp[ft_specialstrlen(temp)] = '\0';
		dest[i] = ft_strdup(temp);
		free (temp);
		if (!dest[i])
			return (printf("Error\nsalut\n"), NULL);
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int	ft_tabsize(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

int	ft_skip(char **full_file, int inf_line)
{
	int	res;

	res = 0;
	while (full_file[inf_line + res] != 0
		&& !ft_ischar(full_file[inf_line + res], '1'))
		res++;
	return (res);
}

char	**ft_getmap(char **full_file, char **inf, int i)
{
	char	**dest;
	int		line;
	int		skip;
	int		inf_line;

	inf_line = ft_tabsize(inf);
	line = ft_tabsize(full_file) - inf_line;
	if (!line)
		return (printf("Error\nMap is badly placed\n"), NULL);
	skip = ft_skip(full_file, inf_line);
	dest = ft_init(line);
	if (!dest)
		return (printf("Error\nBad allocation\n"), NULL);
	while (i < line)
	{
		dest[i] = ft_strdup(full_file[inf_line + i + skip]);
		i++;
	}
	dest[i] = 0;
	return (dest);
}
