/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_and_define.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascotto- <ascotto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:36:51 by ascotto-          #+#    #+#             */
/*   Updated: 2022/08/14 15:36:37 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_AND_DEFINE_H
# define STRUCTURES_AND_DEFINE_H

# include "cub3d.h"

# define WIDTH	1200
# define HEIGHT	800

# define W_MAP	24
# define H_MAP	24
# define HEIGHT_TOP	HEIGHT

# define TILE_W			10
# define TILE_H			10
# define MAP_Y			10
# define MAP_X			950//(WIDTH - (W_MAP * TILE_W)) - 10
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
	float	planex;
	float	planey;
	double	mspeed;
	double	rotspeed;
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

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_line;

#endif
