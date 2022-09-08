/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:06:55 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/09/01 17:01:26 by ascotto-         ###   ########.fr       */
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

//Parsing
//	get_next_line.c
char		*get_next_line(int fd);

//	get_next_line_utils.c
int			ft_strlen(char *str);
int			ft_is_next_line(char *str, char nl);
char		*ft_strdup(char *s1);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_sep_after(char *src);

//	alloc_map.c
char		**ft_init(int line);
int			ft_file_line(char *map_path);
int			ft_longuestline(char *map_path, int i);
char		*ft_alloc_line(char *dest, char *temp, int large, int j);
char		**ft_alloc_map(char *map_path, int i, int j, int large);

//	checkmap_utils.c
int			ft_checkline(char **map, int i, int j);
int			ft_checkcolumn(char **map, int i, int j);
int			ft_checkplayer(char **map, int i, int j);
int			ft_checkobj(char *str, int obj);
int			ft_digitonly(char *str);

//	checkmap_utils2.c
int			ft_isplyr(char c);
int			ft_largest(char **map);
int			ft_longuest(char **map);
int			ft_wichdir(char c);
void		ft_cleanmap(char **map);

//	checkmap.c
int			ft_test(char *str, char *set, int count, int i);
int			ft_checkname(char *str, char *set);
int			ft_checkclosed(char **map, int i, int j);
int			ft_checkinf(char **inf, int i);
int			ft_checkmap(char *map_path, t_data *data);

//	cleaninf.c
int			ft_wichline(char *str);
int			ft_strsize(char *str);
char		*ft_fill(char *dest, char *src, int size);
char		**ft_cleaninf(t_data *data);

//	getmap.c
int			ft_infline(char *map_path);
char		**ft_getinf(char *map_path, int i);
int			ft_tabsize(char **tab);
int			ft_skip(char **full_file, int inf_line);
char		**ft_getmap(char **full_file, char **inf, int i);

//	init_mstruct.c
int			ft_getplyr(t_data *data);
int			ft_getcolor(char *str);
int			ft_init_mstruct(t_data *data, char *arg);
void		ft_cleandata(t_data *data);

//	parsing_utils.c
int			ft_specialstrlen(char *str);
int			ft_atoi(char *str);
int			ft_ischar(char *str, char c);
int			ft_skipspace(char *str);

void		ft_init_mlxwinimg(t_data *data);

//Raycasting
int			ft_doall(t_mlx *mlx, t_player *player);
int			ft_key_hooks(int keycode, t_mlx *mlx);
int			ft_release_hooks(int keycode, t_mlx *mlx);

void		ft_draw_map(t_mlx *mlx);

t_line		ft_line(int x0, int y0, int x1, int y1);
void		ft_drawline(t_line line, void *img, int color);
void		my_mlx_pixel_put(t_image *data, int x, int y, int color);

int			ft_open_textures(t_image *textures, t_mlx *mlx);

void		ft_init_image(t_image *img, t_mlx *mlx);
void		ft_init_rc(t_raycasting *rc, t_player *player, int x);

void		ft_print(t_raycasting *rc, t_mlx *mlx, t_image *textures, int x);
void		ft_find_texture(t_raycasting *rc);
void		ft_compute_line_height(t_raycasting *rc, t_mlx *mlx);
void		ft_get_wall_distance(t_raycasting *rc, t_player *player);

#endif
