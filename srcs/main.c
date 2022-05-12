/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:52 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/05/12 19:08:28 by jroux-fo         ###   ########.fr       */
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
	data->mlx_win = mlx_new_window(data->mlx_ptr, data->line_size * 25,
			data->column_size * 25, "cub3d");
	data->img = mlx_new_image(data->mlx_ptr, data->line_size * 25,
			data->column_size * 25);
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
	while (x + i < x + 25)
	{
		j = 0;
		while (y + j < y + 25)
		{
			ft_mlx_pixel_put(data, x + i, y + j, color);
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
			if (map[j / 25][i / 25] == '1')
				ft_draw_square(data, i, j, 0xFF000000);
			if (map[j / 25][i / 25] == '0')
				ft_draw_square(data, i, j, 0x00FF0000);
			if (map[j / 25][i / 25] == ' ')
				ft_draw_square(data, i, j, 0x00000000);
			j += 25;
		}
		i += 25;
	}
}

int main(int argc, char **argv)
{
    t_data     *img;
	int	i;
	
	i = 0;
	
    if (argc != 2)
		return (printf("Error\nInvalid arguments number\n"), 1);
    
	img = malloc(sizeof(t_data));
	
    ft_init_mstruct(img, argv[1]);
	
	printf ("line_size = %d\n", img->line_size);
	printf ("column_size = %d\n", img->column_size);
	ft_init_mlxwinimg(img);

	while (img->map[i] != 0)
	{
		printf("%s\n", img->map[i]);
		i++;
	}

	ft_draw_map(img, img->map, img->line_size * 25, img->column_size * 25);

	mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->img, 0, 0);
	mlx_loop(img->mlx_ptr);
}
