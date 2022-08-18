/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroux-fo <jroux-fo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:52 by jroux-fo          #+#    #+#             */
/*   Updated: 2022/08/18 17:00:07 by jroux-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if (argc != 2)
		return (printf("Error\nInvalid arguments number\n"), 1);
	if (ft_checkmap(argv[1], &data))
		exit(1);
	else
		printf("MAP CORRECTE SELON LE PARSING\n");
	if (ft_init_mstruct(&data, argv[1]))
		return (printf("Error\nBad allocation\n"), 1);
	printf ("line_size = %d\n", data.line_size);		//print la taille des lignes de la map;
	printf ("column_size = %d\n", data.column_size);	//print la taille des colonnes de la map;
	while (data.map[i] != 0)							//print la map;
	{
		printf("%s\\0", data.map[i]);
		printf("\n");
		i++;
	}
	i = 0;
	while (data.info[i] != 0)							//print les infos (sprites + colors);
	{
		printf("%s\\0", data.info[i]);
		printf("\n");
		i++;
	}
	printf("COORDONNEES JOUEUR = player_y = %d, player_x = %d\n", data.player_y, data.player_x);	//print les coordoonnes du joueur;
	printf("Floor color : %d, Ceiling color : %d\n", data.f_color, data.c_color);					//print les couleurs du sol et du plafond en int;
	ft_cleandata(&data);
}
