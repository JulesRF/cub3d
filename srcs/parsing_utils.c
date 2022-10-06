/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:56:14 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/18 15:56:14 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_specialstrlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	if (str[i - 1] == '\n')
		i--;
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	moins;
	int	res;

	i = 0;
	moins = 0;
	res = 0;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			moins++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10;
		res = res + str[i] - 48;
		i++;
	}
	if (moins % 2 == 1)
		return (-res);
	return (res);
}

int	ft_ischar(char *str, char c)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_skipspace(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			return (i);
		i++;
	}
	return (0);
}

void	ft_cleanmap(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i] != 0)
	{
		free(map[i]);
		i++;
	}
	free (map);
}
