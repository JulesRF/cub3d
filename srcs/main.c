/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:52 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/17 15:11:20 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_specialstrlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	if (str[i - 1] == '\n')
		i--;
	return (i);
}

int	ft_ischar(char *str, char c)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

// void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

int	ft_skipspace(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			return (i);
		i++;
	}
	return (0);
}

int ft_largest(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = -4;
	while (map[i] != 0)
	{
		j = 0;
		while (map[i][j] != '\0')
			j++;
		if (max == -4)
			max = j;
		else if (j > max)
			max = j;
		i++;
	}
	return (max);
}

int ft_longuest(char **map)
{
	int	i;

	i = 0;
	while (map[i] != 0)
		i++;
	return (i);
}

char	**ft_init(int line)
{
	char	**init;

	init = malloc(sizeof(char *) * (line + 1));
	if (!init)
		return (write(1, "Error\nmalloc fail", 17), NULL);
	init[0] = 0;
	return (init);
}

int	ft_file_line(char *map_path)
{
	int		line;
	char	*dest;
	int		fd;

	fd = open(map_path, O_RDONLY);
	line = 0;
	while (line == 0 || dest != NULL)
	{
		dest = get_next_line(fd);
		if (dest == NULL)
			break ;
		free (dest);
		line++;
	}
	return (close (fd), line);
}

int	ft_longuestline(char *map_path, int i)
{
	int		max;
	int		fd;
	char	*dest;

	max = 0;
	fd = open(map_path, O_RDONLY);
	while (max == 0 || dest != NULL)
	{
		dest = get_next_line(fd);
		if (!dest)
			break ;
		if (ft_specialstrlen(dest) > max)
			max = ft_strlen(dest);
		free (dest);
		i++;
	}
	return (close (fd), max);
}

char	*ft_alloc_line(char *dest, char *temp, int large, int j)
{
	dest = malloc(sizeof(char) * (large + 1));
	if (!dest)
		return (NULL);
	while (j < large)
	{
		if (j >= ft_specialstrlen(temp))
			dest[j] = ' ';
		else
			dest[j] = temp[j];
		j++;
	}
	dest[j - 1] = '\0';
	free (temp);
	return (dest);
}

char	**ft_alloc_map(char *map_path, int i, int j, int large)
{
	char	**dest;
	char	*temp;
	int		fd;
	int		line;

	line = ft_file_line(map_path);
	large = ft_longuestline(map_path, 0);
	dest = ft_init(line);
	if (!dest)
		return (NULL);
	fd = open(map_path, O_RDONLY);
	while (i < line)
	{
		j = 0;
		temp = get_next_line(fd);
		dest[i] = ft_alloc_line(dest[i], temp, large, j);
		if (!dest[i])
			return (NULL);
		i++;
	}
	dest[i] = 0;
	return (close (fd), dest);
}

// void	ft_init_mlxwinimg(t_data *data)
// {
// 	data->mlx_ptr = mlx_init();
// 	data->mlx_win = mlx_new_window(data->mlx_ptr, data->line_size * 25,
// 			data->column_size * 25, "cub3d");
// 	data->img = mlx_new_image(data->mlx_ptr, data->line_size * 25,
// 			data->column_size * 25);
// 	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
// 			&data->line_length, &data->endian);
// }

void	ft_cleanmap(char **map)
{
	int i;

	i = 0;
	while (map[i] != 0)
	{
		free(map[i]);
		i++;
	}
	free (map);
}

int	ft_wichline(char *str)
{
	int index1;
	int index2;

	index1 = ft_skipspace(str);
	if (index1 + 1 <= ft_strlen(str))
		index2 = index1 + 1 + ft_skipspace(str + index1 + 1);
	if (str[index1] == 'N' && str[index2] == 'O')
		return (0);
	else if (str[index1] == 'S' && str[index2] == 'O')
		return (1);
	else if (str[index1] == 'W' && str[index2] == 'E')
		return (2);
	else if (str[index1] == 'E' && str[index2] == 'A')
		return (3);
	else if (str[index1] == 'F')
		return (4);
	else if (str[index1] == 'C')
		return (5);
	return (-5);
}

int	ft_strsize(char *str)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			res++;
		i++;
	}
	return (res);
}

char	*ft_fill(char *dest, char *src, int size)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	size = ft_strsize(src);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (src[j])
	{
		if (src[j] != ' ')
		{
			dest[i] = src[j];
			i++;
		}
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

// char	**ft_initinfo(char **info, int k)
// {
// 	char	**dest;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	dest = ft_init(6);
// 	if (!dest)
// 		return (NULL);
// 	while (j < 6)
// 	{
// 		i = 0;
// 		while (k != j && info[i] != 0)
// 		{
// 			k = ft_wichline(info[i]);
// 			if (k != j)
// 				i++;
// 		}
// 		// size = ft_strsize(info[i]);
// 		dest[j] = malloc(sizeof(char) * ft_strsize(info[i]) + 1);
// 		dest[j][0] = '\0';
// 		if (!dest[j])
// 			return (NULL);
// 		j++;
// 	}
// 	dest[6] = 0;
// 	return (dest);
// }

char	**ft_cleaninf(t_data *data)
{
	char	**dest;
	int		i;
	int		k;

	i = 0;
	dest = ft_init(6);
	if (!dest)
		return (NULL);
	// dest = ft_initinfo(data->info, -5);
	// if (!dest)
	// 	return (NULL);
	// while (data->info[i] != 0)
	// {
	// 	k = -5;
	// 	while (k == -5 && data->info[i] != 0)
	// 	{
	// 		k = ft_wichline(data->info[i]);
	// 		if (k == -5)
	// 			i++;
	// 	}
	// 	ft_fill(dest[k], data->info[i]);
	// 	i++;
	// }
	while (data->info[i] != 0)
	{
		k = -5;
		while (k == -5 && data->info[i] != 0)
		{
			k = ft_wichline(data->info[i]);
			if (k == -5)
				i++;
		}
		dest[k] = ft_fill(dest[k], data->info[i], 0);
		if (!dest[k])
			return (NULL);
		i++;
	}
	dest[6] = 0;
	ft_cleanmap(data->info);
	return (dest);
}

int	ft_getplyr(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i] != 0)
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'S' || data->map[i][j] == 'N'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->player_x = j;
				data->player_y = i;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (printf("Error\nCouldn't find player after parsing\n"), 1);
}

int	ft_iterative_power(int nb, int power)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (i < power)
	{
		res = res * nb;
		i++;
	}
	return (res);
}

int	ft_hexatodeci(char *str, char *base)
{
	int	p;
	int res;
	int i;
	int	r;

	i = 0;
	res = 0;
	p = ft_strlen(str) - 1;
	while (str[i])
	{
		if (base[str[i] - 48] >= '0' && base[str[i] - 48] <= '9')
			r = str[i] - 48;
		else
			r = str[i] - 'A' + 10;
		res = res + r * ft_iterative_power(16, p);
		p--;
		i++;
	}
	return (res);
}

int	ft_init_mstruct(t_data *data, char *arg)
{
	(void)arg;
    data->line_size = ft_largest(data->map);
	data->column_size = ft_longuest(data->map);
	data->info = ft_cleaninf(data);
	if (!data->info)
		return (1);
	if (ft_getplyr(data))
		return (1);
	return (0);
}

// void	ft_draw_square(t_data *data, int x, int y, int color)
// {
// 	double	i;
// 	double	j;

// 	i = 0;
// 	while (x + i < x + 25)
// 	{
// 		j = 0;
// 		while (y + j < y + 25)
// 		{
// 			ft_mlx_pixel_put(data, x + i, y + j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	ft_draw_map(t_data *data, char **map, int x, int y)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (i < x)
// 	{
// 		j = 0;
// 		while (j < y)
// 		{
// 			if (map[j / 25][i / 25] == '1')
// 				ft_draw_square(data, i, j, 0x0000FF00);
// 			if (map[j / 25][i / 25] == '0')
// 				ft_draw_square(data, i, j, 0x00FF0000);
// 			if (map[j / 25][i / 25] == ' ')
// 				ft_draw_square(data, i, j, 0x00000000);
// 			j += 25;
// 		}
// 		i += 25;
// 	}
// }

int	ft_test(char *str, char *set, int count, int i)
{
	if (count != 1)
		return (1);
	if ((str[i - 1] != set[3] || str[i - 2] != set[2] || str[i - 3] != set[1]
			|| str[i - 4] != set [0]))
		return (1);
	return (0);
}

int	ft_checkname(char *str, char *set)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == set[j])
		{
			while (str[i] == set[j] && j < 4)
			{
				i++;
				j++;
			}
			if (j == 4)
				count++;
			i = i - j;
		}
		i++;
	}
	if (ft_test(str, set, count, i))
		return (write(1, "Error\nInvalid map file name\n", 28), 1);
	return (0);
}

int	ft_isplyr(char c)
{
	if (c != 'N' && c != 'S' && c != 'O' && c != 'W')
		return (0);
	return (1);
}

int	ft_checkline(char **map, int i, int j)
{
	while (map[i] != 0)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				j++;
			else if (map[i][j] == '0')
			{
				if ((j == 0) || (j >= 1 && (map[i][j - 1] != '1'
					&& !ft_isplyr(map[i][j - 1]))))
					return (printf("Error\nInvalid map format\n"), 1); //i = %d j = %d\n", i, j), 1);
				while (map[i][j] && map[i][j] == '0')
					j++;
				if (!map[i][j] || (map[i][j] != '1'  && !ft_isplyr(map[i][j])))
					return (printf("Error\nInvalid map format\n"), 1);//i = %d j = %d\n", i, j), 1);
			}
			else
				j++;
		}
		i++;
	}
	return (0);
}

int	ft_checkcolumn(char **map, int i, int j)
{
	while (map[0][j] != '\0')
	{
		i = 0;
		while (map[i] != 0)
		{
			if (map[i] != 0 && map[i][j] == '1')
				i++;
			else if (map[i] != 0 && map[i][j] == '0')
			{
				if ((i == 0) || (i >= 1 && (map[i - 1][j] != '1' && !ft_isplyr(map[i - 1][j]))))
					return (printf("Error\nInvalid map format\n"), 1); //i = %d j = %d\n", i, j), 1);
				while (map[i] != 0 && map[i][j] == '0')
					i++;
				if (map[i] == 0 || (map[i][j] != '1' && !ft_isplyr(map[i][j])))
					return (printf("Error\nInvalid map format\n"), 1); //i = %d j = %d\n", i, j), 1);
			}
			else
				i++;
		}
		j++;
	}
	return (0);
}

int	ft_checkplayer(char **map, int i, int j)
{
	int	player;

	player = 0;
	while (map[i] != 0)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				if (i == 0 || j == 0 || !map[i + 1] || map[i][j + 1] == '\0'
					|| map[i + 1][j] == ' ' || map[i][j + 1] == ' ')
					return (printf("Error\nPlayer is badly placed\n"), 1);
				player++;
			}
			j++;
		}
		i++;
	}
	if (player != 1)
		return (printf("Error\nMake sure there is 1 Player\n"), 1);
	return (0);
}

int	ft_checkobj(char *str, int obj)
{
	static int	tab[6] = {0, 0, 0, 0, 0, 0};
	int index1;
	int index2;

	index1 = ft_skipspace(str);
	index2 = index1 + 1 + ft_skipspace(str + index1 + 1);
	// printf("obj numero %d, INDEX1 = %d, INDEX2 = %d\n", obj, index1, index2);
	if (str[index1] == 'N' && str[index2] == 'O' && tab[obj] == 0)
		return (tab[obj]++, 0);
	else if (str[index1] == 'S' && str[index2] == 'O' && tab[obj] == 0)
		return (tab[obj]++, 0);
	else if (str[index1] == 'W' && str[index2] == 'E' && tab[obj] == 0)
		return (tab[obj]++, 0);
	else if (str[index1] == 'E' && str[index2] == 'A' && tab[obj] == 0)
		return (tab[obj]++, 0);
	else if (str[index1] == 'F' && tab[obj] == 0)
		return (tab[obj]++, 0);
	else if (str[index1] == 'C' && tab[obj] == 0)
		return (tab[obj]++, 0);
	return (1);
}

int	ft_infline(char *map_path)
{
	int	line;
	int	fd;
	int	obj;
	char *dest;

	fd = open(map_path, O_RDONLY);
	line = 0;
	obj = 0;
	while (( line == 0 || dest != NULL) && obj != 6)
	{
		dest = get_next_line(fd);
		if (dest == NULL)
			break ;
		if (!ft_checkobj(dest, obj))
			obj++;
		free (dest);
		line++;
	}
	if (obj != 6)
		return (close (fd), 0);
	return(close (fd), line);
}

char	**ft_getinf(char *map_path, int i)
{
	char	**dest;
	char	*temp;
	int		fd;
	int		line;

	line = ft_infline(map_path);
	if (!line)
		return (printf("la il manque des infos askip\n"), NULL);
	dest = ft_init(line);
	if (!dest)
		return (NULL);
	fd = open(map_path, O_RDONLY);
	while (i < line)
	{
		temp = get_next_line(fd);
		if (ft_ischar(temp, '\n'))
			temp[ft_specialstrlen(temp)] = '\0';
		dest[i] = ft_strdup(temp);
		free (temp);
		if (!dest[i])
			return (NULL);
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int	ft_tabsize(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

int	ft_skip(char **full_file, int inf_line)
{
	int res;

	res = 0;
	while (full_file[inf_line + res] != 0
		&& !ft_ischar(full_file[inf_line + res], '1'))
		res++;
	return (res);
}

char	**ft_getmap(char **full_file, char **inf, int i)
{
	char	**dest;
	int		line;
	int		skip;
	int		inf_line;

	inf_line = ft_tabsize(inf);
	line = ft_tabsize(full_file) - inf_line;
	if (!line)
		return (NULL);
	skip = ft_skip(full_file, inf_line);
	dest = ft_init(line);
	if (!dest)
		return (NULL);
	while (i < line)
	{
		dest[i] = ft_strdup(full_file[inf_line + i + skip]);
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int	ft_checkclosed(char **map, int i, int j)
{
	if (!map)
		return (1);
	if (ft_checkline(map, i, j))
		return (1);
	if (ft_checkcolumn(map, i, j))
		return (1);
	if (ft_checkplayer(map, i, j))
		return (1);
	return (0);
}

int	ft_digitonly(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] != ',' && str[i] != ' ')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_checkinf(char **inf, int i)
{
	int wich;

	wich = 0;
	while (inf[i] != 0 && (inf[i][ft_skipspace(inf[i])] != 'F'
		&& inf[i][ft_skipspace(inf[i])] != 'C'))
		i++;
	if (inf[i] == 0)
		return (1);
	if (inf[i][ft_skipspace(inf[i])] && inf[i][ft_skipspace(inf[i])] == 'C')
		wich++;
	if (inf[i] != 0 && ft_digitonly(inf[i] + ft_skipspace(inf[i]) + 1))
		return (1);
	while (inf[i] != 0 && (inf[i][ft_skipspace(inf[i])] != 'C' && wich == 0))
		i++;
	if (inf[i] == 0)
		return (1);
	if (inf[i] != 0 && ft_digitonly(inf[i] + ft_skipspace(inf[i]) + 1))
		return (1);
	return (0);
}

int	ft_checkmap(char *map_path, t_data *data)
{
	char	**full_file;
	char	**map;
	char	**inf;
	// int i = 0;

	if (ft_checkname(map_path, ".cub"))
		return (free (data), 1);
	full_file = ft_alloc_map(map_path, 0, 0, -5);
	if (!full_file)
		return (free (data), 1);
	inf = ft_getinf(map_path, 0);
	if (!inf)
		return (free (data), ft_cleanmap(full_file), 1);
	map = ft_getmap(full_file, inf, 0);
	if (!map)
		return (free (data), ft_cleanmap(inf), ft_cleanmap(full_file), 1);
	ft_cleanmap(full_file);
	// while (inf[i] != 0)
	// {
	// 	printf("Ligne numero %i = %s\\0\n", i + 1, inf[i]);
	// 	i++;
	// }
	// i = 0;
	// while (map[i] != 0)
	// {
	// 	printf("Ligne numero %i = %s\\0\n", i + 1, map[i]);
	// 	i++;
	// }
	if (ft_checkclosed(map, 0, 0) || ft_checkinf(inf, 0))
		return (free (data), ft_cleanmap(inf), ft_cleanmap(map), 1);
	data->map = map;
	data->info = inf;
	return (0);
}

void	ft_cleandata(t_data *data)
{
	ft_cleanmap(data->map);
	ft_cleanmap(data->info);
}

int main(int argc, char **argv)
{
    t_data	data;
	int		i;
	int		j;

	i = 0;

	if (argc != 2)
		return (printf("Error\nInvalid arguments number\n"), 1);

	if (ft_checkmap(argv[1], &data))
		exit(1);
	else
		printf("MAP CORRECTE SELON LE PARSING\n");
	if (ft_init_mstruct(&data, argv[1]))
		return (printf("Error\nBad allocation\n"), 1);
	// printf ("line_size = %d\n", img->line_size);
	// printf ("column_size = %d\n", img->column_size);
	// ft_init_mlxwinimg(img);

	while (data.map[i] != 0)
	{
		j = 0 ;
		while (data.map[i][j] != '\0')
		{
			// printf("%d ", data->map[i][j]);
			j++;
		}
		printf("%s\\0",data.map[i]);
		printf("\n");
		i++;
	}
	i = 0;
	while (data.info[i] != 0)
	{
		j = 0;
		while (data.info[i][j] != '\0')
		{
			// printf("%d ", data->map[i][j]);
			j++;
		}
		printf("%s\\0",data.info[i]);
		printf("\n");
		i++;
	}
	printf("COORDONNEES JOUEUR = player_y = %d, player_x = %d\n", data.player_y, data.player_x);
	printf("CONVERSION : %d\n", ft_hexatodeci("FF","0123456789abcdef"));

	ft_cleandata(&data);
	// ft_draw_map(img, img->map, img->line_size * 25, img->column_size * 25);

	// mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->img, 0, 0);
	// mlx_loop(img->mlx_ptr);
}
