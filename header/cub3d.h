/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:06:55 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/05/11 14:06:57 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include "mlx.h"

typedef struct s_data {
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img;
	char		*addr;
	char		**map;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			line_size;
	int			column_size;
	int			player_x;
	int			player_y;
}				t_data;

#endif