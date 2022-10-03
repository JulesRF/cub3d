/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mstruct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:03:45 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/18 16:03:45 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_getplyr(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i] != 0)
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'S' || data->map[i][j] == 'N'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->player_x = j;
				data->player_y = i;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (printf("Error\nCouldn't find player after parsing\n"), 1);
}

int	ft_getgoodindex(char *str, int j)
{
	int	i;

	i = j;
	while (str[i])
	{
		if (str[i] == ',')
			return (i + 1);
		i++;
	}
	return (0);
}

int	ft_getcolor(char *str)
{
	int	res;
	int	i;
	int	j;

	i = ft_getgoodindex(str, 1);
	j = ft_getgoodindex(str, i);
	res = (ft_atoi(str + 1) * 65536) + (ft_atoi(str + i) * 256)
		+ ft_atoi(str + j);
	return (res);
}

int	ft_playerdir(t_data *data)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	res = -5;
	while (data->map[i] != 0)
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'W'
				|| data->map[i][j] == 'S' || data->map[i][j] == 'E')
			{
				res = ft_wichdir(data->map[i][j]);
				data->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (res);
}

int	ft_init_mstruct(t_data *data, char *arg)
{
	(void)arg;
	data->line_size = ft_largest(data->map);
	data->column_size = ft_longuest(data->map);
	// data->info = ft_cleaninf(data);
	if (!data->info)
		return (1);
	if (ft_getplyr(data))
		return (1);
	data->f_color = ft_getcolor(data->info[4]);
	data->c_color = ft_getcolor(data->info[5]);
	data->player_dir = ft_playerdir(data);
	return (0);
}
