/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascotto- <ascotto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:03:51 by ascotto-          #+#    #+#             */
/*   Updated: 2022/08/29 09:17:35 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_player(t_mlx *mlx, float x, float y)
{
	double	i;
	double	j;

	x = x * TILE_W;
	y = y * TILE_H;
	i = 0;
	while (y + i < y + (PLAYER_SIZE))
	{
		j = 0;
		while (x + j < x + (PLAYER_SIZE))
		{
			my_mlx_pixel_put(mlx->minimap, floorf(x) + j,
				floorf(y) + i, 0x0FFFF00);
			j++;
		}
		i++;
	}
}

void	ft_draw_minimap(t_mlx *mlx, int w, int h)
{
	int		x;
	int		y;
	int		i;
	int		j;

	y = 0;
	x = 0;
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			if (mlx->player->map[i][j] == '1')
				ft_draw_square(mlx, j * TILE_W + x, i * TILE_H + y, 0x606060);
			if (mlx->player->map[i][j] != '1')
				ft_draw_square(mlx, j * TILE_W + x, i * TILE_H + y, 0xC0C0C0);
			j++;
		}
		i++;
	}
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);
}

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
