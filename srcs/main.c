/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:52 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/05/13 16:49:55 by ascotto-         ###   ########.fr       */
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

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

int	ft_file_line(int fd)
{
	int		line;
	char	*dest;

	line = 0;
	while (dest != NULL || line == 0)
	{
		dest = get_next_line(fd);
		if (dest == NULL)
			break ;
		free (dest);
		line++;
	}
	return (line);
}

char	**ft_alloc_map(char *map_path)
{
	char	**dest;
	char	*temp;
	int		fd;
	int		i;
	int		line;

	fd = open(map_path, O_RDONLY);
	line = ft_file_line(fd);
	dest = ft_init(line);
	if (!dest)
		return (NULL);
	close (fd);
	fd = open(map_path, O_RDONLY);
	i = 0;
	while (i < line)
	{
		temp = get_next_line(fd);
		if (ft_ischar(temp, '\n'))
			temp[ft_specialstrlen(temp)] = '\0';
		dest[i] = ft_strdup(temp);
		free (temp);
		i++;
	}
	dest[i] = 0;
	return (close (fd), dest);
}

void	ft_init_mlxwinimg(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx_ptr, data->line_size * TILE_SIZE,
			data->column_size * TILE_SIZE, "cub3d");
	data->img = mlx_new_image(data->mlx_ptr, data->line_size * TILE_SIZE,
			data->column_size * TILE_SIZE);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

void	ft_init_mstruct(t_data *data, char *arg)
{
    data->map = ft_alloc_map(arg);
    data->line_size = ft_largest(data->map);
	data->column_size = ft_longuest(data->map);
}

void	ft_draw_square(t_data *data, int x, int y, int color)
{
	double	i;
	double	j;

	i = 0;
	while (x + i < x + (TILE_SIZE - 1))
	{
		j = 0;
		while (y + j < y + (TILE_SIZE - 1))
		{
			ft_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_player(t_data *data, int x, int y)
{
	double	i;
	double	j;

	i = 0;
	if (data->map[x / TILE_SIZE][y / TILE_SIZE] == '1')
		return ;
	while (x + i < x + (TILE_SIZE / 2))
	{
		j = 0;
		while (y + j < y + (TILE_SIZE / 2))
		{
			ft_mlx_pixel_put(data, x + i, y + j, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void	ft_draw_map(t_data *data, char **map, int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			if (map[j / TILE_SIZE][i / TILE_SIZE] == '1')
				ft_draw_square(data, i, j, 0x606060);
			if (map[j / TILE_SIZE][i / TILE_SIZE] == '0')
				ft_draw_square(data, i, j, 0xC0C0C0);
			if (map[j / TILE_SIZE][i / TILE_SIZE] == ' ')
				ft_draw_square(data, i, j, 0x0000FF00);
			j += TILE_SIZE;
		}
		i += TILE_SIZE;
	}
	ft_draw_player(data, data->player_x, data->player_y);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
}

int	ft_key_hooks(int keycode, t_data *img)
{
	if (keycode == 65307)
	{
		exit(EXIT_SUCCESS);
		return (0);
	}
	if (keycode == 'w')
	{
		img->player_y -= 10;
		ft_draw_map(img, img->map, img->line_size * TILE_SIZE,
				img->column_size * TILE_SIZE);
	}
	if (keycode == 'a')
	{
		img->player_x -= 10;
		ft_draw_map(img, img->map, img->line_size * TILE_SIZE,
				img->column_size * TILE_SIZE);
	}
	if (keycode == 's')
	{
		img->player_y += 10;
		ft_draw_map(img, img->map, img->line_size * TILE_SIZE,
				img->column_size * TILE_SIZE);
	}
	if (keycode == 'd')
	{
		img->player_x += 10;
		ft_draw_map(img, img->map, img->line_size * TILE_SIZE,
				img->column_size * TILE_SIZE);
	}
	return (1);
}

int main(int argc, char **argv)
{
    t_data     *img;
	int	i;
	
	i = 0;
	
    if (argc != 2)
		return (printf("Error\nInvalid arguments number\n"), 1);
    
	img = malloc(sizeof(t_data));
	
	img->player_x = 100;
	img->player_y = 100;
    ft_init_mstruct(img, argv[1]);
	
	printf ("line_size = %d\n", img->line_size);
	printf ("column_size = %d\n", img->column_size);
	ft_init_mlxwinimg(img);

	while (img->map[i] != 0)
	{
		printf("%s\n", img->map[i]);
		i++;
	}

	ft_draw_map(img, img->map, img->line_size * TILE_SIZE, img->column_size * TILE_SIZE);

	mlx_hook(img->mlx_win, 2, 1L << 0, ft_key_hooks, img);
	mlx_loop(img->mlx_ptr);
}
