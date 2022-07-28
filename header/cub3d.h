/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:06:55 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/05/12 18:32:27 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx_linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_data {
	// void		*mlx_ptr;
	// void		*mlx_win;
	// void		*img;
	// char		*addr;
	char		**map;
	char		**info;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			line_size;
	int			column_size;
	int			player_x;
	int			player_y;
}				t_data;

//	get_next_line.c
char	*get_next_line(int fd);

//	get_next_line_utils.c
int		ft_strlen(char *str);
int		ft_is_next_line(char *str, char nl);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_sep_after(char *src);

void	ft_init_mlxwinimg(t_data *data);

#endif