/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascotto- <ascotto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:26:39 by ascotto-          #+#    #+#             */
/*   Updated: 2022/10/03 15:14:28 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_wall_distance_utils(t_raycasting *rc)
{
	if (rc->stepx < 0)
		rc->mapx = rc->mapx - rc->stepx;
	if (rc->stepy < 0)
		rc->mapy = rc->mapy - rc->stepy;
	if (rc->side == 0)
		rc->wall_distance = rc->sidex - rc->deltax;
	else
		rc->wall_distance = rc->sidey - rc->deltay;
}

void	ft_get_wall_distance(t_raycasting *rc, t_player *player)
{
	while (rc->hit == 0)
	{
		if (rc->sidex < rc->sidey)
		{
			rc->sidex += rc->deltax;
			rc->mapx += rc->stepx;
			rc->side = 0;
		}
		else
		{
			rc->sidey += rc->deltay;
			rc->mapy += rc->stepy;
			rc->side = 1;
		}
		if (player->map[rc->mapy][rc->mapx] != '0')
			rc->hit = 1;
	}
	ft_wall_distance_utils(rc);
}

void	ft_compute_line_height(t_raycasting *rc, t_mlx *mlx)
{
	rc->wally = mlx->player->y + rc->wall_distance * rc->ry;
	rc->wallx = mlx->player->x + rc->wall_distance * rc->rx;
	rc->lineheight = (int)(HEIGHT / rc->wall_distance);
	rc->drawstart = -rc->lineheight / 2 + HEIGHT / 2;
	if (rc->drawstart < 0)
		rc->drawstart = 0;
	rc->drawend = rc->lineheight / 2 + HEIGHT / 2;
	if (rc->drawend >= HEIGHT)
		rc->drawend = HEIGHT - 1;
}

void	ft_find_texture(t_raycasting *rc)
{
	if (rc->side == 1)
	{
		if (rc->ry < 0)
			rc->tex_number = NORTH;
		else
			rc->tex_number = SOUTH;
	}
	else
	{
		if (rc->rx < 0)
			rc->tex_number = WEST;
		else
			rc->tex_number = EAST;
	}
	if (rc->side == 0)
		rc->wallx = rc->wally;
	rc->wallx -= floor(rc->wallx);
}

void	ft_print(t_raycasting *rc, t_mlx *mlx, t_image *textures, int x)
{
	t_image	texture;
	int		tex_y;
	int		y;

	texture = textures[rc->tex_number];
	y = rc->drawstart;
	rc->tex_x = (int)((rc->wallx * (double)texture.tw));
	if (rc->side == 0 && rc->rx > 0)
		rc->tex_x = texture.tw - rc->tex_x - 1;
	if (rc->side == 1 && rc->ry < 0)
		rc->tex_x = texture.tw - rc->tex_x - 1;
	rc->step = 1.0 * texture.th / rc->lineheight;
	rc->tex_pos = (rc->drawstart - HEIGHT / 2
			+ rc->lineheight / 2) * rc->step;
	while (y < rc->drawend)
	{
		tex_y = (int)rc->tex_pos & (texture.th - 1);
		rc->tex_pos += rc->step;
		rc->dst = texture.addr + (tex_y * texture.line_length
				+ rc->tex_x * (texture.bits_per_pixel / 8));
		rc->color = *(unsigned int *)rc->dst;
		my_mlx_pixel_put(mlx->img, x, y, rc->color);
		y++;
	}
}
