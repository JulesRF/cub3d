/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascotto- <ascotto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:35:07 by ascotto-          #+#    #+#             */
/*   Updated: 2022/08/16 17:59:49 by ascotto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_key_hooks_4(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
	{
		if (mlx->mlx && mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		if (mlx->mlx)
		{
			mlx_destroy_display(mlx->mlx);
			free(mlx->mlx);
		}
		exit(EXIT_SUCCESS);
		return (0);
	}
	if (keycode == 'a')
	{
		if (mlx->player->map[(int)mlx->player->y][(int)(mlx->player->x
			+ mlx->player->dx * mlx->player->mspeed)] == 0)
			mlx->player->x += mlx->player->planex * mlx->player->mspeed;
		if (mlx->player->map[(int)(mlx->player->y + mlx->player->planey
				* mlx->player->mspeed)][(int)mlx->player->x] == 0)
			mlx->player->y += mlx->player->planey * mlx->player->mspeed;
	}
	if (keycode == 'd')
	{
		if (mlx->player->map[(int)mlx->player->y][(int)(mlx->player->x
			- mlx->player->dx * mlx->player->mspeed)] == 0)
			mlx->player->x -= mlx->player->planex * mlx->player->mspeed;
		if (mlx->player->map[(int)(mlx->player->y - mlx->player->planey
				* mlx->player->mspeed)][(int)mlx->player->x] == 0)
			mlx->player->y -= mlx->player->planey * mlx->player->mspeed;
	}
	return (1);
}

static int	ft_key_hooks_3(int keycode, t_mlx *mlx)
{
	double	oldx;
	double	oldplanex;

	if (keycode == 65361)
	{
		oldx = mlx->player->dx;
		mlx->player->dx = oldx * cos(-mlx->player->rotspeed)
			- mlx->player->dy * sin(-mlx->player->rotspeed);
		mlx->player->dy = oldx * sin(-mlx->player->rotspeed) \
			+ mlx->player->dy * cos(-mlx->player->rotspeed);
		oldplanex = mlx->player->planex;
		mlx->player->planex = oldplanex * cos(-mlx->player->rotspeed)
			- mlx->player->planey * sin(-mlx->player->rotspeed);
		mlx->player->planey = oldplanex * sin(-mlx->player->rotspeed)
			+ mlx->player->planey * cos(-mlx->player->rotspeed);
	}
	else
		ft_key_hooks_4(keycode, mlx);
	return (1);
}

static int	ft_key_hooks_2(int keycode, t_mlx *mlx)
{
	double	oldx;
	double	oldplanex;

	if (keycode == 65363)
	{
		oldx = mlx->player->dx;
		mlx->player->dx = mlx->player->dx * cos(mlx->player->rotspeed)
			- mlx->player->dy * sin(mlx->player->rotspeed);
		mlx->player->dy = oldx * sin(mlx->player->rotspeed) \
			+ mlx->player->dy * cos(mlx->player->rotspeed);
		oldplanex = mlx->player->planex;
		mlx->player->planex = mlx->player->planex
			* cos(mlx->player->rotspeed) - mlx->player->planey
			* sin(mlx->player->rotspeed);
		mlx->player->planey = oldplanex * sin(mlx->player->rotspeed)
			+ mlx->player->planey * cos(mlx->player->rotspeed);
	}
	if (keycode == 65505)
		mlx->player->mspeed = M_SPRINT;
	else
		ft_key_hooks_3(keycode, mlx);
	return (1);
}

int	ft_key_hooks(int keycode, t_mlx *mlx)
{
	if (keycode == 'w')
	{
		if (mlx->player->map[(int)mlx->player->y][(int)(mlx->player->x
			+ mlx->player->dx * mlx->player->mspeed)] == 0)
			mlx->player->x += mlx->player->dx * mlx->player->mspeed;
		if (mlx->player->map[(int)(mlx->player->y + mlx->player->dy
				* mlx->player->mspeed)][(int)mlx->player->x] == 0)
			mlx->player->y += mlx->player->dy * mlx->player->mspeed;
	}
	if (keycode == 's')
	{
		if (mlx->player->map[(int)mlx->player->y][(int)(mlx->player->x
			- mlx->player->dx * mlx->player->mspeed)] == 0)
			mlx->player->x -= mlx->player->dx * mlx->player->mspeed;
		if (mlx->player->map[(int)(mlx->player->y - mlx->player->dy
				* mlx->player->mspeed)][(int)mlx->player->x] == 0)
			mlx->player->y -= mlx->player->dy * mlx->player->mspeed;
	}
	else
		ft_key_hooks_2(keycode, mlx);
	ft_doall(mlx, mlx->player);
	return (1);
}

int	ft_release_hooks(int keycode, t_mlx *mlx)
{
	if (keycode == 65505)
		mlx->player->mspeed = M_SPEED;
	return (1);
}
