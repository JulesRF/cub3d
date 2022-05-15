/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:52 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/05/15 18:28:26 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw2(t_point2d A, t_point2d B, void *img, t_line line)
{
	int	e2;

	while (1)
	{
		my_mlx_pixel_put(img, A.x, A.y, line.color);
		if (A.x == B.x && A.y == B.y)
			break ;
		e2 = line.err;
		if (e2 > -(line.dx))
		{
			line.err -= line.dy;
			A.x = A.x + line.sx;
		}
		if (e2 < line.dy)
		{
			line.err += line.dx;
			A.y = A.y + line.sy;
		}
	}
}

void	ft_drawline(t_point2d A, t_point2d B, void *img, int color)
{
	t_line	line;

	line.dx = (int)floorf(fabsf(B.x - A.x));
	line.dy = (int)floorf(fabsf(B.y - A.y));
	if (A.x < B.x)
		line.sx = 1;
	else
		line.sx = -1;
	if (A.y < B.y)
		line.sy = 1;
	else
		line.sy = -1;
	if (line.dx > line.dy)
		line.err = line.dx / 2;
	else
		line.err = -(line.dy) / 2;
	line.color = color;
	ft_draw2(A, B, img, line);
}

void	ft_draw_square(t_mlx *mlx, int x, int y, int color)
{
	double	i;
	double	j;

	i = 0;
	while (x + i < x + (TILE_SIZE))
	{
		j = 0;
		while (y + j < y + (TILE_SIZE))
		{
			my_mlx_pixel_put(mlx->img, x + i, y + j, color);
			if (i >= TILE_SIZE - OUTLINE || j >= TILE_SIZE - OUTLINE)
				my_mlx_pixel_put(mlx->img, x + i, y + j, 0x000000);
			j++;
		}
		i++;
	}
}

void	ft_draw_player(t_mlx *mlx, int x, int y)
{
	double		i;
	double		j;
//	t_point2d	A;
//	t_point2d	B;

	i = 0;
	while (x + i < x + (PLAYER_SIZE))
	{
		j = 0;
		while (y + j < y + (PLAYER_SIZE))
		{
			my_mlx_pixel_put(mlx->img, x + i, y + j, 0x00FF0000);
			j++;
		}
		i++;
	}
/*	ft_mlx_pixel_put(data, x, y, 0x00FF0000);
	A.x = data->player_x;
	A.y = data->player_y;
	B.x = data->player_x + data->player_dx * 5;
	B.y = data->player_y + data->player_dy * 5;
	ft_drawline(A, B, mlx->img, 0x00FF0000);*/
}

void	ft_draw_map(t_mlx *mlx, char **map, int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			if (map[j / TILE_SIZE][i / TILE_SIZE] == '1')
				ft_draw_square(mlx, i, j, 0x606060);
			if (map[j / TILE_SIZE][i / TILE_SIZE] == '0')
				ft_draw_square(mlx, i, j, 0xC0C0C0);
			j += TILE_SIZE;
		}
		i += TILE_SIZE;
	}
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
}

int	ft_key_hooks(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
	{
		exit(EXIT_SUCCESS);
		return (0);
	}
	if (keycode == 'w')
	{
		mlx->player->y -= 7;
		ft_draw_map(mlx, mlx->map, 6, 10);
	}
	if (keycode == 'a')
	{
		mlx->player->x -= 7;
		ft_draw_map(mlx, mlx->map, 6, 10);
	}
	if (keycode == 's')
	{
		mlx->player->y += 7;
		ft_draw_map(mlx, mlx->map, 6, 10);
	}
	if (keycode == 'd')
	{
		mlx->player->x += 7;
		ft_draw_map(mlx, mlx->map, 6, 10);
	}
	return (1);
}

int main(int argc, char **argv)
{
	(void)argv;
	(void)argc;

	t_mlx		mlx;
	t_player	player;
	
	player.x = 100;
	player.y = 100;
	player.angle = M_PI;
	player.dx = cos(player.angle ) * 5;
	player.dy = sin(player.angle) * 5;
	
	char *map[6] =	{"1111111111",
					"1000000001",
					"1000000001",
					"1000000001",
					"1000000001",
					"1111111111"};	

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "fdf");
	mlx.player = &player;
	mlx.map = map;
	mlx_hook(mlx.win, 2, 1L << 0, ft_key_hooks, &mlx);
	mlx_loop(mlx.mlx);
}
