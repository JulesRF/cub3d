/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:06:55 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/05/16 15:18:25 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx_linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define TILE_SIZE		25
# define PLAYER_SIZE	10
# define OUTLINE		1	

# define WIDTH	1280
# define HEIGHT	1024

# define PI		3.141592653589793

typedef struct s_point2d
{
	float	x;
	float	y;
}	t_point2d;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	color;
}	t_line;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	angle;
}	t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_image		*img;
	t_player	*player;
	char		**map;
}	t_mlx;

#endif
