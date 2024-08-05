/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:29:23 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/05 20:35:33 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_whitespace(char s)
{
	if (s == ' ' || s == '\t' || s == '\r'
		|| s == '\n' || s == '\v' || s == '\f')
		return (1);
	return (0);
}

int	ext(void *params)
{
	t_cub		*cub;

	cub = params;
	mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	//free_map(&vars);
	exit(0);
	return (0);
}

void ft_redraw(t_cub *cub)
{
	cub->img.img = mlx_new_image(cub->mlx.mlx, cub->map_wd, cub->map_ht);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
	draw_patalok_u_pol();
}

void	initing(char **map)
{
	t_cub	cub;
	int		x = 100;
	int		y = 100;
	(void)map;
	
	cub.mlx.mlx = mlx_init();
	cub.mlx.win = mlx_new_window(cub.mlx.mlx, cub.map_ht, cub.map_wd, "cub3D");
	ft_redraw(&cub);
	mlx_hook(cub.mlx.win, 17, 0, ext, &cub);
	mlx_loop(cub.mlx.mlx);
}

int	main(int ac, char **av)
{
	char **map;

	if (ac != 2)
		err("Invalid count of arguments\n");
	map = init_map(av[1]);
	initing(map);
	free_map(map);
}



	//int		i;
	
	// i = 1;
	// cub.char_map = NULL;
	// cub.wall = NULL;
	// cub.map = NULL;
	// cub.epath = NULL;
	// cub.npath = NULL;
	// cub.wpath = NULL;
	// cub.spath = NULL;
	// cub.fcolor = NULL;
	// cub.rcolor = NULL;
	// init_cub(&cub, map);