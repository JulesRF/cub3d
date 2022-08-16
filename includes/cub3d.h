/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:06:55 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/16 12:38:36 by ascotto-         ###   ########.fr       */
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
# include "structures_and_define.h"

int			ft_key_hooks(int keycode, t_mlx *mlx);
int			ft_release_hooks(int keycode, t_mlx *mlx);

void		ft_doall(t_mlx *mlx, t_player *player);

void		ft_draw_player(t_mlx *mlx, float x, float y);
void		ft_draw_minimap(t_mlx *mlx, int w, int h);
void		ft_draw_map(t_mlx *mlx);

t_line		ft_line(int x0, int y0, int x1, int y1);
void		ft_draw_square(t_mlx *mlx, int x, int y, int color);
void		ft_drawline(t_line line, void *img, int color);
void		my_mlx_pixel_put(t_image *data, int x, int y, int color);

int			ft_open_textures(t_image *textures, t_mlx *mlx);
char		*ft_filename(int i);

void		ft_init_images_and_map(t_image *img, t_image *minimap, t_mlx *mlx);
void		ft_init_rc(t_raycasting *rc, t_player *player, int x);

void		ft_print(t_raycasting *rc, t_mlx *mlx, t_image *textures, int x);
void		ft_find_texture(t_raycasting *rc);
void		ft_compute_line_height(t_raycasting *rc, t_mlx *mlx);
void		ft_get_wall_distance(t_raycasting *rc, t_player *player);

#endif
