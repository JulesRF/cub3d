/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascotto- <ascotto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:23:53 by ascotto-          #+#    #+#             */
/*   Updated: 2022/08/14 15:33:50 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_filename(int i)
{
	i++;
	if (i == SOUTH)
		return ("textures/emma.xpm");
	if (i == EAST)
		return ("textures/eagle.xpm");
	if (i == WEST)
		return ("textures/redbrick.xpm");
	else
		return ("textures/pillar.xpm");
}

int	ft_open_textures(t_image *textures, t_mlx *mlx)
{
	int		i;
	t_image	texture;

	i = 0;
	while (i < 4)
	{
		texture.img = mlx_xpm_file_to_image(mlx->mlx, ft_filename(i),
				&texture.tw, &texture.th);
		if (texture.img != NULL)
		{
			texture.addr = mlx_get_data_addr(texture.img,
				&texture.bits_per_pixel, &texture.line_length,
				&texture.endian);
		}
		if (texture.tw != texture.th || texture.img == NULL)
		{
			if (texture.img == NULL)
				i--;
			while (i >= 0)
			{
				mlx_destroy_image(mlx->mlx, textures[i].img);
				i--;
			}
			return (1);
		}
		textures[i] = texture;
		i++;
	}
	return (0);
}
