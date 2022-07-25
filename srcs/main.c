/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:52 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/07/25 14:39:11 by ascotto-         ###   ########.fr       */
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


void	ft_drawray(int x0, int y0, int x1, int y1, void *img, int color)
{
	float	dx;
	float	dy;
	float	len;
	float	x;
	float	y;
	int		stop;

	stop = 0;
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
		if (stop > 45)
			break ;
		stop++;
	}
} 

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
} 

//BRESENHAM
/*
void ft_drawline(int x0, int y0, int x1, int y1, void *img, int color)
{
	int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = dx + dy, e2;  //error value e_xy

	for (;;){
		my_mlx_pixel_put(img, x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; } // e_xy+e_x > 0 
		if (e2 <= dx) { err += dx; y0 += sy; } // e_xy+e_y < 0 
	}
}*/

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

void	ft_minisquare(t_mlx *mlx, int x, int y, int color)
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
			if (mlx->player->map[i][x] > 0)
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
			color = 0x00000020;
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(mlx->img, x, y, color);
		y++;
	}
}

char	*ft_filename(int i)
{
	i++;
	if (i == SOUTH)
		return ("textures/wood.xpm");
	if (i == EAST)
		return ("textures/eagle.xpm");
	if (i == WEST)
		return ("textures/redbrick.xpm");
	else
		return ("textures/pillar.xpm");
}
void	ft_open_textures(t_image *textures, t_mlx *mlx)
{
	int		i;
	t_image	texture;

	i = 0;

	while (i < 4)
	{
		texture.img = mlx_xpm_file_to_image(mlx->mlx, ft_filename(i), &texture.tw, &texture.th);
		texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
				&texture.line_length, &texture.endian);
		textures[i] = texture;
		i++;
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

	t_image	textures[4];

	ft_open_textures(textures, mlx);
	int	fov = 0;
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
		int	texN;

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
			texN = player->map[mapy][mapx];
			if (texN > 0)
				hit = 1;
		}
		if (stepX < 0) 
			mapx = mapx - stepX;
		if (stepY < 0)
			mapy = mapy - stepY;
		if (side == 0)
			wall_distance = sideX - deltaX;
		else
			wall_distance = sideY - deltaY;

		double wallX; 
		double wallY; 
		wallY = mlx->player->y + wall_distance * rY;
		wallX= mlx->player->x + wall_distance * rX;
		if (fov > WIDTH / 2 && fov < WIDTH / 2 + 120)
		{
			ft_drawray((mlx->player->x * TILE_W + PLAYER_SIZE / 2),
				(mlx->player->y * TILE_H + HEIGHT_TOP + PLAYER_SIZE / 2),
				wallX * TILE_W , wallY * TILE_H + HEIGHT_TOP, mlx->img, 0x00FF0000);
		}
		fov++;

		//SECOND PART : compute pixel from the wall_distance we got

		int lineHeight = (int)(HEIGHT_TOP / wall_distance);

		int drawStart = -lineHeight / 2 + HEIGHT_TOP / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT_TOP / 2;
		if (drawEnd >= HEIGHT_TOP)
			drawEnd = HEIGHT_TOP - 1;

		char			*dst;
		unsigned int	color;
		t_image	texture;

		if (side == 1)
			if (rY < 0)
				texN = SOUTH;
			else
				texN = NORTH;
		}
		else
		{
			if (rX < 0)
				texN = EAST;
			else
				texN = WEST;
		}
		texture = textures[texN];
		if (side == 0)
			wallX = wallY;
		wallX -= floor(wallX);
		int texX = (int)((wallX * (double)texture.tw));
    	if(side == 0 && rX > 0) texX = texture.tw - texX - 1;
      	if(side == 1 && rY < 0) texX = texture.tw - texX - 1;

			
		double step = 1.0 * texture.th / lineHeight;
      // Starting texture coordinate
		double texPos = (drawStart - HEIGHT_TOP / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y< drawEnd; y++)
		{
        	int texY = (int)texPos & (texture.th - 1);
			texPos += step;
			dst = texture.addr + (texY * texture.line_length
				+ texX * (texture.bits_per_pixel / 8));
			color = *(unsigned int *)dst;
			if(side == 1) color = (color >> 1) & 8355711;
			my_mlx_pixel_put(mlx->img, x, y, color);
		}
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
		if (mlx->player->map[(int)mlx->player->y][(int)(mlx->player->x + mlx->player->dx * mlx->player->Mspeed)] == 0)
			mlx->player->x += mlx->player->dx * mlx->player->Mspeed;
		if (mlx->player->map[(int)(mlx->player->y + mlx->player->dy * mlx->player->Mspeed)][(int)mlx->player->x] == 0)
			mlx->player->y += mlx->player->dy * mlx->player->Mspeed;
	}
	if (keycode == 's')
	{
		if (mlx->player->map[(int)mlx->player->y][(int)(mlx->player->x - mlx->player->dx * mlx->player->Mspeed)]== 0)
			mlx->player->x -= mlx->player->dx * mlx->player->Mspeed;
		if (mlx->player->map[(int)(mlx->player->y - mlx->player->dy * mlx->player->Mspeed)][(int)mlx->player->x] == 0)
			mlx->player->y -= mlx->player->dy * mlx->player->Mspeed;
	}
	if (keycode == 'a')
	{
		if (mlx->player->map[(int)mlx->player->y][(int)(mlx->player->x + mlx->player->dx * mlx->player->Mspeed)] == 0)
			mlx->player->x += mlx->player->planeX * mlx->player->Mspeed;
		if (mlx->player->map[(int)(mlx->player->y + mlx->player->planeY * mlx->player->Mspeed)][(int)mlx->player->x] == 0)
			mlx->player->y += mlx->player->planeY * mlx->player->Mspeed;
	}
	if (keycode == 'd')
	{
		if (mlx->player->map[(int)mlx->player->y][(int)(mlx->player->x - mlx->player->dx * mlx->player->Mspeed)]== 0)
			mlx->player->x -= mlx->player->planeX * mlx->player->Mspeed;
		if (mlx->player->map[(int)(mlx->player->y - mlx->player->planeY * mlx->player->Mspeed)][(int)mlx->player->x] == 0)
			mlx->player->y -= mlx->player->planeY * mlx->player->Mspeed;
	}
	if (keycode == 65363)
	{
		double OldX = mlx->player->dx;
		mlx->player->dx = mlx->player->dx * cos(mlx->player->rotSpeed) -
			mlx->player->dy * sin(mlx->player->rotSpeed);
		mlx->player->dy = OldX * sin(mlx->player->rotSpeed) + mlx->player->dy * cos(mlx->player->rotSpeed);
		double OldPlaneX = mlx->player->planeX;
		mlx->player->planeX = mlx->player->planeX * cos(mlx->player->rotSpeed) - mlx->player->planeY * sin(mlx->player->rotSpeed);
		mlx->player->planeY = OldPlaneX * sin(mlx->player->rotSpeed) + mlx->player->planeY * cos(mlx->player->rotSpeed);
	}
	if (keycode == 65361)
	{
		double OldX = mlx->player->dx;
		mlx->player->dx = OldX * cos(-mlx->player->rotSpeed) -
			mlx->player->dy * sin(-mlx->player->rotSpeed);
		mlx->player->dy = OldX * sin(-mlx->player->rotSpeed) + mlx->player->dy * cos(-mlx->player->rotSpeed);
		double OldPlaneX = mlx->player->planeX;
		mlx->player->planeX = OldPlaneX * cos(-mlx->player->rotSpeed) - mlx->player->planeY * sin(-mlx->player->rotSpeed);
		mlx->player->planeY = OldPlaneX * sin(-mlx->player->rotSpeed) + mlx->player->planeY * cos(-mlx->player->rotSpeed);

	}
	if (keycode == 65505)
		mlx->player->Mspeed = 0.3;
	ft_doall(mlx, mlx->player);
	return (1);
}

int	ft_release_hooks(int keycode, t_mlx *mlx)
{
	if (keycode == 65505)
		mlx->player->Mspeed = 0.1;
	return (1);
}

int main(int argc, char **argv)
{
	(void)argv;
	(void)argc;

	t_mlx		mlx;
	t_player	player = 
	{ 0, 0, 0, 0, 0, 0, 0, 0,
		{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,8},
			{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
			{1,0,8,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,8},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1},
			{1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1},
			{1,0,1,0,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
			{1,0,0,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1},
			{1,0,1,0,1,0,0,0,0,1,1,0,1,1,0,0,1,0,0,1,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		}
	};

	player.x = 6;
	player.y = 5;
	player.dx = -1;
	player.dy = 0;
	player.planeX = 0;
	player.planeY = 0.70;
	player.Mspeed = 0.1;
	player.rotSpeed = 0.05;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "cub3d");
	mlx.player = &player;


	ft_doall(&mlx, &player);
	mlx_hook(mlx.win, 2, 1L << 0, ft_key_hooks, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, ft_release_hooks, &mlx);
	mlx_loop(mlx.mlx);
}
