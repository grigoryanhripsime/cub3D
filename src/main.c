/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:29:23 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/08 18:46:11 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	minimap(t_cub *cub)
// {
// 	void *mlx = mlx_init();
// 	void *window = mlx_new_window(mlx, 200, 200, "Minimap");
	
	
// }

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		err("Invalid count of arguments\n");
	cub = init_game(av[1]);
	init_mlx(cub);
	//minimap(cub);
	free_cub(cub);
}
