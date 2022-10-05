/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:36:45 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/18 15:36:45 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_test(char *str, char *set, int count, int i)
{
	if (count != 1)
		return (1);
	if ((str[i - 1] != set[3] || str[i - 2] != set[2] || str[i - 3] != set[1]
			|| str[i - 4] != set [0]))
		return (1);
	return (0);
}

int	ft_checkname(char *str, char *set)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == set[j])
		{
			while (str[i] == set[j] && j < 4)
			{
				i++;
				j++;
			}
			if (j == 4)
				count++;
			i = i - j;
		}
		i++;
	}
	if (ft_test(str, set, count, i))
		return (write(1, "Error\nInvalid map file name\n", 28), 1);
	return (0);
}

int	ft_checkclosed(char **map, int i, int j)
{
	if (!map)
		return (1);
	if (ft_checkline(map, i, j))
		return (1);
	if (ft_checkcolumn(map, i, j))
		return (1);
	if (ft_checkplayer(map, i, j))
		return (1);
	return (0);
}

int	ft_checkinf(char **inf, int i)
{
	int	wich;

	wich = 0;
	while (inf[i] != 0 && (inf[i][ft_skipspace(inf[i])] != 'F'
		&& inf[i][ft_skipspace(inf[i])] != 'C'))
		i++;
	if (inf[i] == 0)
		return (1);
	if (inf[i][ft_skipspace(inf[i])] && inf[i][ft_skipspace(inf[i])] == 'C')
		wich++;
	if (inf[i] != 0 && ft_digitonly(inf[i] + ft_skipspace(inf[i]) + 1))
		return (1);
	while (inf[i] != 0 && (inf[i][ft_skipspace(inf[i])] != 'C' && wich == 0))
		i++;
	if (inf[i] == 0)
		return (1);
	if (inf[i] != 0 && ft_digitonly(inf[i] + ft_skipspace(inf[i]) + 1))
		return (1);
	return (0);
}

int	ft_checkmap(char *map_path, t_data *data)
{
	char	**full;
	char	**map;
	char	**inf;

	if (ft_checkname(map_path, ".cub"))
		return (1);
	full = ft_alloc_map(map_path, 0, 0, -5);
	if (!full)
		return (1);
	inf = ft_getinf(map_path, 0);
	if (!inf || ft_checkinf(inf, 0))
		return (ft_cleanmap(full), 1);
	map = ft_getmap(full, inf, 0);
	if (!map)
		return (ft_cleanmap(inf), ft_cleanmap(full), 1);
	ft_cleanmap(full);
	if (ft_checkclosed(map, 0, 0) || ft_checkinf(inf, 0))
		return (ft_cleanmap(inf), ft_cleanmap(map), 1);
	data->map = map;
	data->info = ft_cleaninf(inf);
	for(int i = 0; data->info[i]; i++)
		printf("%s\n", data->info[i]);
	if (ft_checkinf2(data->info))
		return (1);
	return (0);
}
