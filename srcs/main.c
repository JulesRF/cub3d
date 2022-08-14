/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:52 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/14 15:36:57 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_doall(t_mlx *mlx, t_player *player)
{
	t_image	img;
	t_image	minimap;

	img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img = &img;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);

	minimap.img = mlx_new_image(mlx->mlx, W_MAP * TILE_W, H_MAP * TILE_H);
	mlx->minimap = &minimap;
	minimap.addr = mlx_get_data_addr(minimap.img, &minimap.bits_per_pixel,
			&minimap.line_length, &minimap.endian);



	ft_draw_map(mlx);
	ft_draw_minimap(mlx, W_MAP, H_MAP);

	t_image	textures[4];

	ft_open_textures(textures, mlx);
	int	fov = 0;
	for (int x = 0; x < WIDTH ; x++)
	{
		double camX = -(2 * x / (double)WIDTH - 1);
		double rX = player->dx + player->planex * camX;
		double rY = player->dy + player->planey * camX;
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
		if (fov > WIDTH / 2 - 120 && fov < WIDTH / 2 + 240)
		{
			ft_drawline(ft_line((mlx->player->x * TILE_W + PLAYER_SIZE / 2),
				(mlx->player->y * TILE_H + PLAYER_SIZE / 2),
				wallX * TILE_W, wallY * TILE_H), mlx->minimap, 0x89a6bc);
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
		{
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
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->minimap->img, MAP_X, MAP_Y);
	mlx_destroy_image(mlx->mlx, mlx->img->img);
	mlx_destroy_image(mlx->mlx, mlx->minimap->img);
	mlx_destroy_image(mlx->mlx, textures[0].img);
	mlx_destroy_image(mlx->mlx, textures[1].img);
	mlx_destroy_image(mlx->mlx, textures[2].img);
	mlx_destroy_image(mlx->mlx, textures[3].img);
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
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
			{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1},
			{1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
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
	player.planex = 0;
	player.planey = 0.70;
	player.mspeed = M_SPEED;
	player.rotspeed = 0.08;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "cub3d");
	mlx.player = &player;


	ft_doall(&mlx, &player);
	mlx_hook(mlx.win, 2, 1L << 0, ft_key_hooks, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, ft_release_hooks, &mlx);
	mlx_loop(mlx.mlx);
}
