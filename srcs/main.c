/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:52 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/05/11 14:04:54 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_map(t_data **data)
{

}

char	*ft_largest(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
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

char *ft_longuest(char **map)
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
	int		map_lenght;
	int		line;
	char	*dest;

	map_lenght = -1;
	line = 0;
	while (dest != NULL || line == 0)
	{
		dest = get_next_line(fd);
	}
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
}

void	ft_init_mstruct(t_data *data, char *arg);
{
    data->map = ft_alloc_map(arg);
    data->line_size = ft_largest(data->map);
	data->column_size = ft_longuest(data->map);
}

int main(int argc, char **argv)
{
    t_data     *img;

    if (argc != 2)
		return (printf("Error\nInvalid arguments number\n"), 1);
    img = malloc(sizeof(t_data));
    ft_init_mstruct(img, argv[1]);

    ft_draw_map()
    // while (i < 100)
    // {
    //     while (j < 100)
    //     {
    //         j++;
    //     }
    //     i++;
    // }
}