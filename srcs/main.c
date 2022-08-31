/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:52 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/31 16:24:01 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_doall(t_mlx *mlx, t_player *player)
{
	t_image			img;
	t_image			textures[4];
	t_raycasting	rc;
	int				x;

	ft_init_image(&img, mlx);
	ft_open_textures(textures, mlx);
	x = 0;
	while (x < WIDTH)
	{
		ft_init_rc(&rc, player, x);
		ft_get_wall_distance(&rc, player);
		ft_compute_line_height(&rc, mlx);
		ft_find_texture(&rc);
		ft_print(&rc, mlx, textures, x);
		x++;
	}	
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img->img);
	mlx_destroy_image(mlx->mlx, textures[0].img);
	mlx_destroy_image(mlx->mlx, textures[1].img);
	mlx_destroy_image(mlx->mlx, textures[2].img);
	mlx_destroy_image(mlx->mlx, textures[3].img);
}

void	ft_init_player(t_player *player, t_data *data)
{
	player->x = data->player_x;
	player->y = data->player_y;
	player->dx = -1;
	player->dy = 0;
	player->planex = 0;
	player->planey = 0.70;
	player->mspeed = M_SPEED;
	player->rotspeed = ROT_SPEED;
	player->w_map = data->line_size;
	player->h_map = data->column_size;
	player->map = data->map;
	player->data = data;
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;
	t_player	player;
	t_data		data;
	int			i;

	i = 0;
	if (argc != 2)
		return (printf("Error\nInvalid arguments number\n"), 1);
	if (ft_checkmap(argv[1], &data))
		exit(1);
	if (ft_init_mstruct(&data, argv[1]))
		return (printf("Error\nBad allocation\n"), 1);
	ft_init_player(&player, &data);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "cub3d");
	mlx.player = &player;
	ft_doall(&mlx, &player);
	mlx_hook(mlx.win, 2, 1L << 0, ft_key_hooks, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, ft_release_hooks, &mlx);
	mlx_loop(mlx.mlx);
}
//mlx_hook(mlx.win, 17, 0, ft_key_hooks, &mlx); broken de fou
