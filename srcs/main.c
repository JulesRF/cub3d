/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:52 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/06/26 15:59:58 by ascotto-         ###   ########.fr       */
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


/* DDA ALGORIHM */
/*
void	ft_drawline(int x0, int y0, int x1, int y1, void *img, int color)
{
	float	dx;
	float	dy;
	float	len;
	float	x;
	float	y;

	dx = x1 - x0;
	dy = y1 - y0;
	if (fabs(dx) > fabs(dy))
		len = fabs(dx);
	else
		len = fabs(dy);
	dx = dx / len;
	dy = dy / len;
	x = x0;
	y = y0;
	//A mettre dans une autre fonction. qui prend x0, y0, dx et dy
	for (int i = 0; i < len ; i++)
	{	
		my_mlx_pixel_put(img, (int)(floorf(x)), (int)(floorf(y)), color);
		x += dx;
		y += dy;
	}
} */

//BRESENHAM
void ft_drawline(int x0, int y0, int x1, int y1, void *img, int color)
{
	int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = dx + dy, e2; /* error value e_xy */

	for (;;){  /* loop */
		my_mlx_pixel_put(img, x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}

void	ft_draw_small_square(t_mlx *mlx, int x, int y, int color)
{
	double	i;
	double	j;

	i = 0;
	while (x + i < x + (3))
	{
		j = 0;
		while (y + j < y + (3))
		{
			my_mlx_pixel_put(mlx->img, x + i, y + j, color);
			j++;
		}
		i++;
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
			my_mlx_pixel_put(mlx->img, x + j, y + i, color);
			if (i >= TILE_H - OUTLINE || j >= TILE_W - OUTLINE)
				my_mlx_pixel_put(mlx->img, x + j, y + i, 0x000000);
			j++;
		}
		i++;
	}
}

void	ft_draw_player(t_mlx *mlx, float x, float y)
{
	double	i;
	double	j;

	x = x * TILE_W;
	y = y * TILE_H;
	y = y + HEIGHT_TOP;
	i = 0;
	while (y + i < y + (PLAYER_SIZE))
	{
		j = 0;
		while (x + j < x + (PLAYER_SIZE))
		{
			my_mlx_pixel_put(mlx->img, floorf(x) + j, floorf(y) + i, 0x0FFFF00);
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

	y = HEIGHT_TOP;
	i = 0;
	while (i < h)
	{
		x = 0;
		while (x < w)
		{
			if (mlx->player->map[i][x] == 1)
				ft_draw_square(mlx, x * TILE_W, i * TILE_H + y, 0x606060);
			if (mlx->player->map[i][x] == 0)
				ft_draw_square(mlx, x * TILE_W , i * TILE_H + y, 0xC0C0C0);
			x++;
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
	color = 0x00FFFF;
	while (y < HEIGHT_TOP)
	{
		if (y > HEIGHT_TOP / 2)
			color = 0x00000000;
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(mlx->img, x, y, color);
		y++;
	}
}

void	ft_doall(t_mlx *mlx, t_player *player)
{
	t_image	img;

	img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img = &img;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);


	ft_draw_map(mlx);
	ft_draw_minimap(mlx, W_MAP, H_MAP);
	printf("PLAYER X = %f\t PlayerY = %f\n", mlx->player->x, mlx->player->y);
	for (int x = 0; x < WIDTH ; x++)
	{
		double camX = -(2 * x / (double)WIDTH - 1);
		double rX = player->dx + player->planeX * camX;
		double rY = player->dy + player->planeY * camX;
		int mapx = (int)player->x;
		int mapy = (int)player->y;

		double	sideX;
		double	sideY;

		double deltaX = (rX == 0) ? 1e30 : fabs (1 / rX);
		double deltaY = (rY == 0) ? 1e30 : fabs (1 / rY);

		double	wall_distance;

		int	stepX;
		int	stepY;
		int hit = 0;
		int	side;

		if (rX < 0)
		{
			stepX = -1;
			sideX = (player->x - mapx) * deltaX;
		}
		else
		{
			stepX = 1;
			sideX = (mapx + 1.0 - player->x) * deltaX;
		}
		if (rY < 0)
		{
			stepY = -1;
			sideY = (player->y - mapy) * deltaY;
		}
		else
		{
			stepY = 1;
			sideY = (mapy + 1.0 - player->y) * deltaY;
		}
		while (hit == 0)
		{
			if (sideX < sideY)
			{
				sideX += deltaX;
				mapx += stepX;
				side = 0;
			}
			else
			{
				sideY += deltaY;
				mapy += stepY;
				side = 1;
			}
			if (player->map[mapy][mapx] > 0)
			{
				
				if (side == 1)
				{
					ft_drawline((mlx->player->x * TILE_W + PLAYER_SIZE / 2),
						(mlx->player->y * TILE_H + HEIGHT_TOP + PLAYER_SIZE / 2),
						mapx * TILE_W + TILE_W / 2,
						mapy * TILE_H + HEIGHT_TOP + TILE_H,
						mlx->img, 0x00FF0000);

					ft_draw_small_square(mlx, mapx * TILE_W + TILE_W /2,
						mapy * TILE_H + HEIGHT_TOP + TILE_H, 0x00FFFF00);
				}
				else
				{
					ft_drawline((mlx->player->x * TILE_W + PLAYER_SIZE / 2),
						(mlx->player->y * TILE_H + HEIGHT_TOP + PLAYER_SIZE / 2),
						mapx * TILE_W + TILE_W,
						mapy * TILE_H + HEIGHT_TOP + TILE_H / 2,
						mlx->img, 0x00FF0000);

					ft_draw_small_square(mlx, mapx * TILE_W + TILE_W,
						mapy * TILE_H + HEIGHT_TOP + TILE_H / 2, 0x00FFFF00);
				}
				hit = 1;
			}
		}
		if (stepX < 0) 
			mapx = mapx - stepX;
		if (stepY < 0)
			mapy = mapy - stepY;
		if (side == 0)
			wall_distance = sideX - deltaX;
		else
			wall_distance = sideY - deltaY;

		//SECOND PART : compute pixel from the wall_distance we got
		int lineHeight = (int)(HEIGHT_TOP / wall_distance);

		int drawStart = -lineHeight / 2 + HEIGHT_TOP / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT_TOP / 2;
		if (drawEnd >= HEIGHT_TOP)
			drawEnd = HEIGHT_TOP - 1;

		int	color;
		if (side == 0)
			color = 0xFF0000;
		else
			color = 0x8A0000;
		(void)color;
		ft_drawline(x, drawStart, x, drawEnd, mlx->img, color);
	}		
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
		if (mlx->player->map[(int)mlx->player->y][(int)(mlx->player->x + mlx->player->dx * mlx->Mspeed)] == 0)
			mlx->player->x += mlx->player->dx * mlx->Mspeed;
		if (mlx->player->map[(int)(mlx->player->y + mlx->player->dy * mlx->Mspeed)][(int)mlx->player->x] == 0)
			mlx->player->y += mlx->player->dy * mlx->Mspeed;
	}
	if (keycode == 's')
	{
		if (mlx->player->map[(int)mlx->player->y][(int)(mlx->player->x - mlx->player->dx * mlx->Mspeed)]== 0)
			mlx->player->x -= mlx->player->dx * mlx->Mspeed;
		if (mlx->player->map[(int)(mlx->player->y - mlx->player->dy * mlx->Mspeed)][(int)mlx->player->x] == 0)
			mlx->player->y -= mlx->player->dy * mlx->Mspeed;
	}
	if (keycode == 'd')
	{
		double OldX = mlx->player->dx;
		mlx->player->dx = mlx->player->dx * cos(mlx->rotSpeed) -
			mlx->player->dy * sin(mlx->rotSpeed);
		mlx->player->dy = OldX * sin(mlx->rotSpeed) + mlx->player->dy * cos(mlx->rotSpeed);
		double OldPlaneX = mlx->player->planeX;
		mlx->player->planeX = mlx->player->planeX * cos(mlx->rotSpeed) - mlx->player->planeY * sin(mlx->rotSpeed);
		mlx->player->planeY = OldPlaneX * sin(mlx->rotSpeed) + mlx->player->planeY * cos(mlx->rotSpeed);
	}
	if (keycode == 'a')
	{
		double OldX = mlx->player->dx;
		mlx->player->dx = OldX * cos(-mlx->rotSpeed) -
			mlx->player->dy * sin(-mlx->rotSpeed);
		mlx->player->dy = OldX * sin(-mlx->rotSpeed) + mlx->player->dy * cos(-mlx->rotSpeed);
		double OldPlaneX = mlx->player->planeX;
		mlx->player->planeX = OldPlaneX * cos(-mlx->rotSpeed) - mlx->player->planeY * sin(-mlx->rotSpeed);
		mlx->player->planeY = OldPlaneX * sin(-mlx->rotSpeed) + mlx->player->planeY * cos(-mlx->rotSpeed);

	}
	if (keycode == 65505)
			mlx->Mspeed = 0.3;
//	else
//		printf("keycode = %d\n", keycode);
	ft_doall(mlx, mlx->player);
	return (1);
}

int	ft_release_hooks(int keycode, t_mlx *mlx)
{
	if (keycode == 65505)
			mlx->Mspeed = 0.1;
	return (1);
}

int main(int argc, char **argv)
{
	(void)argv;
	(void)argc;

	t_mlx		mlx;
	t_player	player = 
	{ 0, 0, 0, 0, 0, 0,
		{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,1,0,0,0,1},
			{1,0,1,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,1,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,1,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,1,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,1,1,0,1,2,2,2,2,2,1,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		}};


	player.x = 16;
	player.y = 8;
	player.dx = -1;
	player.dy = 0;
	player.planeX = 0;
	player.planeY = 0.70;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "cub3d");
	mlx.player = &player;
	mlx.Mspeed = 0.1;
	mlx.rotSpeed = 0.05;


	ft_doall(&mlx, &player);
	mlx_hook(mlx.win, 2, 1L << 0, ft_key_hooks, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, ft_release_hooks, &mlx);
	mlx_loop(mlx.mlx);
}
