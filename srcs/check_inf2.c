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

int	ft_checkcolor(char *line)
{
	int	i;
	int	j;

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
	int	k;

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

int	ft_is_info(char *str)
{
	int			index1;
	int			index2;

	index1 = ft_skipspace(str);
	index2 = index1 + 1 + ft_skipspace(str + index1 + 1);
	if (str[index1] == 'N' && str[index2] == 'O')
		return (0);
	else if (str[index1] == 'S' && str[index2] == 'O')
		return (0);
	else if (str[index1] == 'W' && str[index2] == 'E')
		return (0);
	else if (str[index1] == 'E' && str[index2] == 'A')
		return (0);
	else if (str[index1] == 'F')
		return (0);
	else if (str[index1] == 'C')
		return (0);
	return (1);
}

int	ft_checkdbl(char *map_path)
{
	int		fd;
	char	*dest;
	int		count;

	count = 0;
	fd = open(map_path, O_RDONLY);
	while (count == 0 || dest != NULL)
	{
		dest = get_next_line(fd);
		if (dest == NULL)
			break ;
		if (!ft_is_info(dest))
			count++;
		free (dest);
	}
	if (count > 6)
		return (1);
	return (0);
}
