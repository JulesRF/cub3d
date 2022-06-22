/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:52 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/06/22 19:15:11 by ascotto-         ###   ########.fr       */
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


double	ft_timestamp(t_mlx *mlx)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - mlx->start_time);
}

/* DDA ALGORIHM */
void	drawline(int x0, int y0, int x1, int y1, void *img, int color)
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
	for (int i = 0; i < len ; i++)
	{	
		my_mlx_pixel_put(img, (int)(floorf(x)), (int)(floorf(y)), color);
		x += dx;
		y += dy;
	}
}

void	ft_draw_map(t_mlx *mlx, int width, int height)
{
	int		x;
	int		y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x++ < width)
			my_mlx_pixel_put(mlx->img, x, y, 0x0000FF00);
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


	ft_draw_map(mlx, WIDTH, HEIGHT);
	for (int x = 0; x < WIDTH ; x++)
	{
		double camX = 2 * x / (double)WIDTH - 1;
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
		if (rX < 0)
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
			if (player->map[mapx][mapy] > 0)
				hit = 1;
		}

		if (side == 0)
			wall_distance = sideX - deltaX;
		else
			wall_distance = sideY - deltaY;

		//SECOND PART : compute pixel from the wall_distance we got
		int lineHeight = (int)(HEIGHT / wall_distance);

		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		int	color;
		if (side == 0)
			color = 0xFF0000;
		else
			color = 0x8A0303;
		drawline(x, drawStart, x, drawEnd, mlx->img, color);
	}		
	mlx->oldtime = mlx->time;
	mlx->time = ft_timestamp(mlx);
	double frametime = (mlx->time - mlx->oldtime) / 1000;
	printf("%f\n",frametime);
	mlx->Mspeed = frametime * 5.0;
	mlx->rotSpeed = (frametime * 3.0) * (M_PI / 180);
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
		if (mlx->player->map[(int)(mlx->player->x + mlx->player->dx * mlx->Mspeed)][(int)mlx->player->y] == 0)
			mlx->player->x += mlx->player->dx * mlx->Mspeed;
		if (mlx->player->map[(int)mlx->player->x][(int)(mlx->player->y + mlx->player->dy * mlx->Mspeed)] == 0)
			mlx->player->y += mlx->player->dy * mlx->Mspeed;
	}
	if (keycode == 's')
	{
		if (mlx->player->map[(int)(mlx->player->x - mlx->player->dx * mlx->Mspeed)][(int)mlx->player->y] == 0)
			mlx->player->x -= mlx->player->dx * mlx->Mspeed;
		if (mlx->player->map[(int)mlx->player->x][(int)(mlx->player->y - mlx->player->dy * mlx->Mspeed)] == 0)
			mlx->player->y -= mlx->player->dy * mlx->Mspeed;	}
	if (keycode == 'a')
	{
		double OldX = mlx->player->dx;
		mlx->player->dx = mlx->player->dx * cos(mlx->rotSpeed) -
			mlx->player->dy * sin(mlx->rotSpeed);
		mlx->player->dy = OldX * sin(mlx->rotSpeed) + mlx->player->dy * cos(mlx->rotSpeed);
		double OldPlaneX = mlx->player->planeX;
		mlx->player->planeX = mlx->player->planeX * cos(mlx->rotSpeed) - mlx->player->planeY * sin(mlx->rotSpeed);
		mlx->player->planeY = OldPlaneX * sin(mlx->rotSpeed) + mlx->player->planeY * cos(mlx->rotSpeed);
	}
	if (keycode == 'd')
	{
		double OldX = mlx->player->dx;
		mlx->player->dx = OldX * cos(-mlx->rotSpeed) -
			mlx->player->dy * sin(-mlx->rotSpeed);
		mlx->player->dy = OldX * sin(-mlx->rotSpeed) + mlx->player->dy * cos(-mlx->rotSpeed);
		double OldPlaneX = mlx->player->planeX;
		mlx->player->planeX = OldPlaneX * cos(-mlx->rotSpeed) - mlx->player->planeY * sin(-mlx->rotSpeed);
		mlx->player->planeY = OldPlaneX * sin(-mlx->rotSpeed) + mlx->player->planeY * cos(-mlx->rotSpeed);

	}
	ft_doall(mlx, mlx->player);
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
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		}};


	player.x = 22;
	player.y = 12;
	player.dx = -1;
	player.dy = 0;
	player.planeX = 0;
	player.planeY = 0.90;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "cub3d");
	mlx.player = &player;
	mlx.start_time = 0;
	mlx.start_time = ft_timestamp(&mlx);
	mlx.time = 0;
	mlx.oldtime = 0;


	ft_doall(&mlx, &player);
	mlx_hook(mlx.win, 2, 1L << 0, ft_key_hooks, &mlx);
	mlx_loop(mlx.mlx);
}
