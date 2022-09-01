/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascotto- <ascotto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:23:53 by ascotto-          #+#    #+#             */
/*   Updated: 2022/09/01 16:55:32 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static char	*ft_filename(int i, t_data *data)
// {
// 	i++;
// 	(void)data;
// 	if (i == SOUTH)
// 		return ("textures/hspriet.xpm");
// 	if (i == EAST)
// 		return ("textures/pdubois.xpm");
// 	if (i == WEST)
// 		return ("textures/jroux-fo.xpm");
// 	else
// 		return ("textures/ychibani.xpm");
// }

int	ft_open_textures2(t_image texture, t_image *textures, t_mlx *mlx, int i)
{
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
	return (0);
}

int	ft_open_textures(t_image *textures, t_mlx *mlx)
{
	int		i;
	t_image	texture;

	i = 0;
	while (i < 4)
	{
		texture.img = mlx_xpm_file_to_image(mlx->mlx,
			mlx->player->data->info[i] + 2, &texture.tw, &texture.th);
		if (texture.img != NULL)
		{
			texture.addr = mlx_get_data_addr(texture.img,
				&texture.bits_per_pixel, &texture.line_length,
				&texture.endian);
		}
		if (ft_open_textures2(texture, textures, mlx, i))
			return (1);
		textures[i] = texture;
		i++;
	}
	return (0);
}
