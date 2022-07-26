/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:06:55 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/07/25 14:29:35 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx_linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <math.h>

# define WIDTH	1200
# define HEIGHT	800

# define W_MAP	24
# define H_MAP	24
# define HEIGHT_TOP	HEIGHT

# define TILE_W			10
# define TILE_H			10
# define MAP_Y			10
# define MAP_X			(WIDTH - (W_MAP * TILE_W)) - 10
# define PLAYER_SIZE	5
# define OUTLINE		1

# define M_SPEED		0.3
# define M_SPRINT		0.9

# define NORTH	0
# define SOUTH	1
# define EAST	2
# define WEST	3

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		tw;
	int		th;
}	t_image;

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	planeX;
	float	planeY;
	double	Mspeed;
	double	rotSpeed;
	int		map[H_MAP][W_MAP];
}	t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_image		*img;
	t_image		*minimap;
	t_player	*player;
}	t_mlx;

#endif
