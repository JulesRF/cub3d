/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:16:00 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/10/03 18:16:03 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_checkcolor(char *line)
{
	int i;
	int j;

	i = ft_getgoodindex(line, 1);
	j = ft_getgoodindex(line, i);
	if (ft_atoi(line + 1) > 255 || ft_atoi(line + i) > 255
		|| ft_atoi(line + j) > 255)
		return (printf("Error\nOne of the color is above 255\n"), 1);
	return (0);
}

int	ft_checkinfline(char *str)
{
	int	i;
	int	j;
	int k;

	k = 0;
	i = ft_getgoodindex(str, 1);
	j = ft_getgoodindex(str, i);
	while (str[j + k] >= '0' && str[j + k] <= '9' && str[j + k])
		k++;
	if (k + j + ft_skipspace(str + k + j) != ft_strlen(str))
		return (printf("Error\nTo much color argument\n"), 1);
	return (0);
}

int	ft_checkinf2(char **info)
{
	if (ft_checkcolor(info[4]) || ft_checkcolor(info[5])
		|| ft_checkinfline(info[4]) || ft_checkinfline(info[5]))
		return (1);
	return (0);
}
