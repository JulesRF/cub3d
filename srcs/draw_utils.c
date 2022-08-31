/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascotto- <ascotto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:00:30 by ascotto-          #+#    #+#             */
/*   Updated: 2022/08/14 15:21:47 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_line	ft_line(int x0, int y0, int x1, int y1)
{
	t_line	res;

	res.x0 = x0;
	res.y0 = y0;
	res.x1 = x1;
	res.y1 = y1;
	return (res);
}

static void	ft_init_line(t_line *line)
{
	line->dx = abs(line->x1 - line->x0);
	line->dy = -abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx + line->dy;
}

//BRESENHAM
void	ft_drawline(t_line line, void *img, int color)
{
	ft_init_line(&line);
	while (1)
	{
		my_mlx_pixel_put(img, line.x0, line.y0, color);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			line.x0 += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			line.y0 += line.sy;
		}
	}
}

void	ft_draw_square(t_mlx *mlx, int x, int y, int color)
{
	double	i;
	double	j;

	i = 0;
	while (y + i < y + (TILE_H))
	{
		j = 0;
		while (x + j < x + (TILE_W))
		{
			my_mlx_pixel_put(mlx->minimap, x + j, y + i, color);
			if (i >= TILE_H - OUTLINE || j >= TILE_W - OUTLINE)
				my_mlx_pixel_put(mlx->minimap, x + j, y + i, 0x000000);
			j++;
		}
		i++;
	}
}
