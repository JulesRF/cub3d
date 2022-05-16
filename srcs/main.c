/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:52 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/05/16 14:09:09 by ascotto-         ###   ########.fr       */
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
		printf("A.x = %f .y = %f B.x = %f . y = %f\n", A.x, A.y, B.x, B.y);
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
	A.x = floorf(A.x);
	A.y = floorf(A.y);
	B.x = floorf(B.x);
	B.y = floorf(B.y);
	printf("A.x = %f .y = %f B.x = %f . y = %f\n", A.x, A.y, B.x, B.y);
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
	x += 250;
	y += 250;
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
	t_point2d	A;
	t_point2d	B;

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
	A.x = mlx->player->x;
	A.y = mlx->player->y;
	B.x = mlx->player->x + mlx->player->dx * 5;
	B.y = mlx->player->y + mlx->player->dy * 5;
	ft_drawline(A, B, mlx->img, 0x00FF0000);
}

void	ft_draw_map(t_mlx *mlx, char **map, int width, int height)
{
	t_image	img;
	int		x;
	int		y;

	img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img = &img;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == '1')
				ft_draw_square(mlx, x * TILE_SIZE, y * TILE_SIZE, 0x606060);
			if (map[y][x] == '0')
				ft_draw_square(mlx, x * TILE_SIZE, y * TILE_SIZE, 0xC0C0C0);
			x++;
		}
		y++;
	}
	ft_draw_player(mlx, mlx->player->x, mlx->player->y);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img->img);
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
		mlx->player->x += mlx->player->dx;
		mlx->player->y += mlx->player->dy;
		ft_draw_map(mlx, mlx->map, 8, 8);
	}
	if (keycode == 'a')
	{
		mlx->player->angle -= 0.1;
		if (mlx->player->angle < 0)
			mlx->player->angle += (2 * PI);
		mlx->player->dx = cosf(mlx->player->angle) * 5;
		mlx->player->dy = sinf(mlx->player->angle) * 5;
		ft_draw_map(mlx, mlx->map, 8, 8);
	}
	if (keycode == 's')
	{
		mlx->player->x -= mlx->player->dx;
		mlx->player->y -= mlx->player->dy;
		ft_draw_map(mlx, mlx->map, 8, 8);
	}
	if (keycode == 'd')
	{
		mlx->player->angle += 0.1;
		if (mlx->player->angle > (2 * PI))
			mlx->player->angle -= (2 * PI);
		mlx->player->dx = cosf(mlx->player->angle) * 5;
		mlx->player->dy = sinf(mlx->player->angle) * 5;
		ft_draw_map(mlx, mlx->map, 8, 8);
	}
	return (1);
}

int main(int argc, char **argv)
{
	(void)argv;
	(void)argc;

	t_mlx		mlx;
	t_player	player;
	
	player.x = 350;
	player.y = 350;
	player.angle = PI;
	player.dx = cosf(player.angle) * 5;
	player.dy = sinf(player.angle) * 5;
	
	char *map[8] =	{"11111111",
					"10000001",
					"10010001",
					"10011001",
					"10000001",
					"10000001",
					"10000001",
					"11111111"};	

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "cub3d");
	mlx.player = &player;
	mlx.map = map;
	ft_draw_map(&mlx, mlx.map, 8, 8);
	mlx_hook(mlx.win, 2, 1L << 0, ft_key_hooks, &mlx);
	mlx_loop(mlx.mlx);
}
