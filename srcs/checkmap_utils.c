/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:40:13 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/18 15:40:13 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_checkline(char **map, int i, int j)
{
	while (map[i] != 0)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				j++;
			else if (map[i][j] == '0')
			{
				if ((j == 0) || (j >= 1 && (map[i][j - 1] != '1'
						&& !ft_isplyr(map[i][j - 1]))))
					return (printf("Error\nInvalid map format\n"), 1);
				while (map[i][j] && map[i][j] == '0')
					j++;
				if (!map[i][j] || (map[i][j] != '1' && !ft_isplyr(map[i][j])))
					return (printf("Error\nInvalid map format\n"), 1);
			}
			else
				j++;
		}
		i++;
	}
	return (0);
}

int	ft_checkcolumn(char **map, int i, int j)
{
	while (map[0][j] != '\0')
	{
		i = 0;
		while (map[i] != 0)
		{
			if (map[i] != 0 && map[i][j] == '1')
				i++;
			else if (map[i] != 0 && map[i][j] == '0')
			{
				if ((i == 0) || (i >= 1 && (map[i - 1][j] != '1'
						&& !ft_isplyr(map[i - 1][j]))))
					return (printf("Error\nInvalid map format\n"), 1);
				while (map[i] != 0 && map[i][j] == '0')
					i++;
				if (map[i] == 0 || (map[i][j] != '1' && !ft_isplyr(map[i][j])))
					return (printf("Error\nInvalid map format\n"), 1);
			}
			else
				i++;
		}
		j++;
	}
	return (0);
}

int	ft_checkplayer(char **map, int i, int j)
{
	int	player;

	player = 0;
	while (map[i] != 0)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				if (i == 0 || j == 0 || !map[i + 1] || map[i][j + 1] == '\0'
					|| map[i + 1][j] == ' ' || map[i][j + 1] == ' ')
					return (printf("Error\nPlayer is badly placed\n"), 1);
				player++;
			}
			j++;
		}
		i++;
	}
	if (player != 1)
		return (printf("Error\nMake sure there is 1 Player\n"), 1);
	return (0);
}

int	ft_checkobj(char *str, int obj)
{
	static int	tab[6] = {0, 0, 0, 0, 0, 0};
	int			index1;
	int			index2;

	index1 = ft_skipspace(str);
	index2 = index1 + 1 + ft_skipspace(str + index1 + 1);
	if (str[index1] == 'N' && str[index2] == 'O' && tab[obj] == 0)
		return (tab[obj]++, 0);
	else if (str[index1] == 'S' && str[index2] == 'O' && tab[obj] == 0)
		return (tab[obj]++, 0);
	else if (str[index1] == 'W' && str[index2] == 'E' && tab[obj] == 0)
		return (tab[obj]++, 0);
	else if (str[index1] == 'E' && str[index2] == 'A' && tab[obj] == 0)
		return (tab[obj]++, 0);
	else if (str[index1] == 'F' && tab[obj] == 0)
		return (tab[obj]++, 0);
	else if (str[index1] == 'C' && tab[obj] == 0)
		return (tab[obj]++, 0);
	return (1);
}

int	ft_digitonly(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] != ',' && str[i] != ' ')
				return (1);
		}
		i++;
	}
	return (0);
}
