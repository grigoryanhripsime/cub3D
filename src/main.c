/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:29:23 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/05 18:59:29 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// int	ext(void *params)
// {
// 	t_vars		*vars;

// 	//int			i;
// 	vars = params;
// 	mlx_destroy_window(vars->mlx, vars->win);
// 	//free_array(&vars);
// 	exit(0);
// 	return (0);
// }

// void	open_window(t_vars **vars)
// {
// 	(*vars)->mlx = mlx_init();
// 	(*vars)->win = mlx_new_window((*vars)->mlx,
// 			1920, 1280, "cub3D");
// 	mlx_hook((*vars)->win, 17, 0, ext, *vars);
// 	mlx_loop((*vars)->mlx);
// }

int	main(int ac, char **av)
{
	t_vars		*vars;
	t_cub *cub;

	if (ac != 2)
		err("Invalid count of arguments\n");
	cub = init_cub(av[1]);
	(void) vars;
	(void) ac;
	// ac = 1;
	// vars = (t_vars *)malloc(sizeof(t_vars));
	// open_window(&vars);
	free_cub(cub);
}
