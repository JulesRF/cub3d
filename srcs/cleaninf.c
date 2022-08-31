/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaninf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:58:40 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/18 15:58:40 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_wichline(char *str)
{
	int	index1;
	int	index2;

	index1 = ft_skipspace(str);
	if (index1 + 1 <= ft_strlen(str))
		index2 = index1 + 1 + ft_skipspace(str + index1 + 1);
	if (str[index1] == 'N' && str[index2] == 'O')
		return (0);
	else if (str[index1] == 'S' && str[index2] == 'O')
		return (1);
	else if (str[index1] == 'W' && str[index2] == 'E')
		return (2);
	else if (str[index1] == 'E' && str[index2] == 'A')
		return (3);
	else if (str[index1] == 'F')
		return (4);
	else if (str[index1] == 'C')
		return (5);
	return (-5);
}

int	ft_strsize(char *str)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			res++;
		i++;
	}
	return (res);
}

char	*ft_fill(char *dest, char *src, int size)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	size = ft_strsize(src);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (src[j])
	{
		if (src[j] != ' ')
		{
			dest[i] = src[j];
			i++;
		}
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_cleaninf(t_data *data)
{
	char	**dest;
	int		i;
	int		k;

	i = 0;
	dest = ft_init(6);
	if (!dest)
		return (NULL);
	while (data->info[i] != 0)
	{
		k = -5;
		while (k == -5 && data->info[i] != 0)
		{
			k = ft_wichline(data->info[i]);
			if (k == -5)
				i++;
		}
		dest[k] = ft_fill(dest[k], data->info[i], 0);
		if (!dest[k])
			return (NULL);
		i++;
	}
	dest[6] = 0;
	ft_cleanmap(data->info);
	return (dest);
}
