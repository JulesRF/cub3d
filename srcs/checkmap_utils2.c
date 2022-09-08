/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:51:31 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/18 15:51:31 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isplyr(char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (0);
	return (1);
}

int	ft_largest(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = -4;
	while (map[i] != 0)
	{
		j = 0;
		while (map[i][j] != '\0')
			j++;
		if (max == -4)
			max = j;
		else if (j > max)
			max = j;
		i++;
	}
	return (max);
}

int	ft_longuest(char **map)
{
	int	i;

	i = 0;
	while (map[i] != 0)
		i++;
	return (i);
}

int	ft_wichdir(char c)
{
	if (c == 'N')
		return (0);
	if (c == 'S')
		return (1);
	if (c == 'W')
		return (2);
	if (c == 'E')
		return (3);
	return (-5);
}

void	ft_cleandata(t_data *data)
{
	ft_cleanmap(data->map);
	ft_cleanmap(data->info);
}
