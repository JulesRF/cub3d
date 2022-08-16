/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascotto- <ascotto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:49:36 by ascotto-          #+#    #+#             */
/*   Updated: 2022/08/16 13:15:41 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_images_and_map(t_image *img, t_image *minimap, t_mlx *mlx)
{
	img->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img = img;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	minimap->img = mlx_new_image(mlx->mlx, W_MAP * TILE_W, H_MAP * TILE_H);
	mlx->minimap = minimap;
	minimap->addr = mlx_get_data_addr(minimap->img, &minimap->bits_per_pixel,
			&minimap->line_length, &minimap->endian);
	ft_draw_map(mlx);
	ft_draw_minimap(mlx, W_MAP, H_MAP);
}

static void	ft_init2(t_raycasting *rc, t_player *player)
{
	if (rc->rx < 0)
	{
		rc->stepx = -1;
		rc->sidex = (player->x - rc->mapx) * rc->deltax;
	}
	else
	{
		rc->stepx = 1;
		rc->sidex = (rc->mapx + 1.0 - player->x) * rc->deltax;
	}
	if (rc->ry < 0)
	{
		rc->stepy = -1;
		rc->sidey = (player->y - rc->mapy) * rc->deltay;
	}
	else
	{
		rc->stepy = 1;
		rc->sidey = (rc->mapy + 1.0 - player->y) * rc->deltay;
	}
}

void	ft_init_rc(t_raycasting *rc, t_player *player, int x)
{
	rc->camx = -(2 * x / (double)WIDTH - 1);
	rc->rx = player->dx + player->planex * rc->camx;
	rc->ry = player->dy + player->planey * rc->camx;
	rc->mapx = (int)player->x;
	rc->mapy = (int)player->y;
	if (rc->rx == 0)
		rc->deltax = 1e30;
	else
		rc->deltax = fabs(1 / rc->rx);
	if (rc->ry == 0)
		rc->deltay = 1e30;
	else
		rc->deltay = fabs(1 / rc->ry);
	rc->hit = 0;
	ft_init2(rc, player);
}
