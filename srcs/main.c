/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:52 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/05/14 15:28:00 by ascotto-         ###   ########.fr       */
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

typedef struct s_point2d
{
	float	x;
	float	y;
	int		size;
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

void	ft_draw2(t_point2d A, t_point2d B, void *img, t_line line)
{
	int	e2;

	while (1)
	{
		ft_mlx_pixel_put(img, A.x, A.y, line.color);
		if (A.x == B.x && A.y == B.y)
			break ;
		e2 = line.err;
		if (e2 > -(line.dx))
		{
			line.err -= line.dy;
			A.x = A.x + line.sx;
		}
		if (e2 < line.dy)
		{
			line.err += line.dx;
			A.y = A.y + line.sy;
		}
	}
}

void	ft_drawline(t_point2d A, t_point2d B, void *img, int color)
{
	t_line	line;

	line.dx = (int)floorf(fabsf(B.x - A.x));
	line.dy = (int)floorf(fabsf(B.y - A.y));
	if (A.x < B.x)
		line.sx = 1;
	else
		line.sx = -1;
	if (A.y < B.y)
		line.sy = 1;
	else
		line.sy = -1;
	if (line.dx > line.dy)
		line.err = line.dx / 2;
	else
		line.err = -(line.dy) / 2;
	line.color = color;
	ft_draw2(A, B, img, line);
}

void	ft_draw_square(t_data *data, int x, int y, int color)
{
	double	i;
	double	j;

	i = 0;
	while (x + i < x + (TILE_SIZE))
	{
		j = 0;
		while (y + j < y + (TILE_SIZE))
		{
			ft_mlx_pixel_put(data, x + i, y + j, color);
			if (i >= TILE_SIZE - OUTLINE || j >= TILE_SIZE - OUTLINE)
				ft_mlx_pixel_put(data, x + i, y + j, 0x000000);
			j++;
		}
		i++;
	}
}

void	ft_draw_player(t_data *data, int x, int y)
{
//	double		i;
//	double		j;
	t_point2d	A;
	t_point2d	B;

/*	i = 0;
	while (x + i < x + (PLAYER_SIZE))
	{
		j = 0;
		while (y + j < y + (PLAYER_SIZE))
		{
			ft_mlx_pixel_put(data, x + i, y + j, 0x00FF0000);
			j++;
		}
		i++;
	}*/
	ft_mlx_pixel_put(data, x, y, 0x00FF0000);
	A.x = data->player_x;
	A.y = data->player_y;
	B.x = data->player_x + data->player_dx * 5;
	B.y = data->player_y + data->player_dy * 5;
	ft_drawline(A, B, data, 0x00FF0000);
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
		img->player_x += img->player_dx;
		img->player_y += img->player_dy;
		ft_draw_map(img, img->map, img->line_size * TILE_SIZE,
				img->column_size * TILE_SIZE);
	}
	if (keycode == 'a')
	{
		img->player_angle -= 0.1;
		if (img->player_angle < 0)
			img->player_angle += (2 * M_PI);
		img->player_dx = cosf(img->player_angle ) * 5;
		img->player_dy = sinf(img->player_angle) * 5;
		ft_draw_map(img, img->map, img->line_size * TILE_SIZE,
				img->column_size * TILE_SIZE);
	}
	if (keycode == 's')
	{
		img->player_x -= img->player_dx;
		img->player_y -= img->player_dy;
		ft_draw_map(img, img->map, img->line_size * TILE_SIZE,
				img->column_size * TILE_SIZE);
	}
	if (keycode == 'd')
	{
		img->player_angle += 0.1;
		if (img->player_angle > (2 * M_PI))
			img->player_angle -= (2 * M_PI);
		img->player_dx = cosf(img->player_angle ) * 5;
		img->player_dy = sinf(img->player_angle) * 5;
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
	img->player_angle = M_PI;
	img->player_dx = cos(img->player_angle ) * 5;
	img->player_dy = sin(img->player_angle) * 5;
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
