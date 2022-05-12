/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:28:03 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/05/12 17:40:07 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_is_next_line(char *str, char nl)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == nl)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s1)
{
	char	*dest;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
		if (s1[i - 1] == '\n')
			break ;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		size_dest;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		return (NULL);
	size_dest = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * size_dest + 1);
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free (s1);
	return (dest);
}

char	*ft_sep_after(char *src)
{
	char	*dest;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!src)
		return (NULL);
	while (src[i] && src[i] != '\n')
		i++;
	if (!src[i] || !src[i + 1])
		return (free(src), NULL);
	if (src[i])
		i++;
	while (src[j])
		j++;
	dest = malloc(sizeof(char) * (j - i + 1));
	if (!dest)
		return (NULL);
	j = 0;
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (free(src), dest);
}