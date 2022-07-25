/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:27:01 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/05/12 17:39:57 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_next_line(int fd)
{
	char		buffer[1 + 1];
	char		*line;
	static char	*save = NULL;
	int			ret;

	ret = 1;
	if (fd < 0 || 1 <= 0)
		return (NULL);
	while (!ft_is_next_line(save, '\n') && ret > 0)
	{
		ret = read(fd, buffer, 1);
		if (ret <= 0)
			break ;
		buffer[ret] = '\0';
		save = ft_strjoin(save, buffer);
	}
	line = ft_strdup(save);
	save = ft_sep_after(save);
	return (line);
}