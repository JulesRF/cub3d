/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascotto- <ascotto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:03:51 by ascotto-          #+#    #+#             */
/*   Updated: 2022/08/31 15:49:26 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_map(t_mlx *mlx)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	color = mlx->player->data->c_color;
	while (y < HEIGHT)
	{
		if (y > HEIGHT / 2)
			color = mlx->player->data->f_color;
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(mlx->img, x, y, color);
		y++;
	}
}
