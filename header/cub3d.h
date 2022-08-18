/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:06:55 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/18 16:26:49 by jroux-fo         ###   ########.fr       */
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
	char		**map;
	char		**info;
	int			line_size;
	int			column_size;
	int			player_x;
	int			player_y;
	int			c_color;
	int			f_color;
}				t_data;

//	get_next_line.c
char	*get_next_line(int fd);

//	get_next_line_utils.c
int		ft_strlen(char *str);
int		ft_is_next_line(char *str, char nl);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_sep_after(char *src);

//	alloc_map.c
char	**ft_init(int line);
int		ft_file_line(char *map_path);
int		ft_longuestline(char *map_path, int i);
char	*ft_alloc_line(char *dest, char *temp, int large, int j);
char	**ft_alloc_map(char *map_path, int i, int j, int large);

//	checkmap_utils.c
int		ft_checkline(char **map, int i, int j);
int		ft_checkcolumn(char **map, int i, int j);
int		ft_checkplayer(char **map, int i, int j);
int		ft_checkobj(char *str, int obj);
int		ft_digitonly(char *str);

//	checkmap_utils2.c
int		ft_isplyr(char c);
int 	ft_largest(char **map);
int 	ft_longuest(char **map);

//	checkmap.c
int		ft_test(char *str, char *set, int count, int i);
int		ft_checkname(char *str, char *set);
int		ft_checkclosed(char **map, int i, int j);
int		ft_checkinf(char **inf, int i);
int		ft_checkmap(char *map_path, t_data *data);

//	cleaninf.c
int		ft_wichline(char *str);
int		ft_strsize(char *str);
char	*ft_fill(char *dest, char *src, int size);
char	**ft_cleaninf(t_data *data);

//	getmap.c
int		ft_infline(char *map_path);
char	**ft_getinf(char *map_path, int i);
int		ft_tabsize(char **tab);
int		ft_skip(char **full_file, int inf_line);
char	**ft_getmap(char **full_file, char **inf, int i);

//	init_mstruct.c
int		ft_getplyr(t_data *data);
int		ft_getcolor(char *str);
int		ft_init_mstruct(t_data *data, char *arg);
void	ft_cleandata(t_data *data);

//	parsing_utils.c
int		ft_specialstrlen(char *str);
int		ft_atoi(char *str);
int		ft_ischar(char *str, char c);
int		ft_skipspace(char *str);
void	ft_cleanmap(char **map);

void	ft_init_mlxwinimg(t_data *data);

#endif