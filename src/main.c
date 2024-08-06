/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:29:23 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/06 15:58:04 by hrigrigo         ###   ########.fr       */
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
	exit(0);
	return (0);
}

void draw_patalok_u_pol(t_cub *cub)
{
	unsigned int	*dst;
	unsigned int	i;

	dst = (unsigned int *) cub->img.addr;
	i = cub->map_wd * cub->map_ht / 2 + 1;
	while (--i > 0)
		*dst++ = cub->rc;
	i = cub->map_wd * cub->map_ht / 2 + 1;
	while (--i > 0)
		*dst++ = cub->fc;
}

void ft_redraw(t_cub *cub)
{
	cub->img.img = mlx_new_image(cub->mlx.mlx, cub->map_wd, cub->map_ht);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
	draw_patalok_u_pol(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->img.img, 0, 0);
	mlx_destroy_image(cub->mlx.mlx, cub->img.img);
}

void	initing(t_cub *cub)
{
	cub->map_wd = 1080;
	cub->map_ht = 720;
	cub->mlx.mlx = mlx_init();
	cub->mlx.win = mlx_new_window(cub->mlx.mlx, cub->map_wd, cub->map_ht, "cub3D");
	ft_redraw(cub);
	mlx_hook(cub->mlx.win, 17, 0, ext, &cub);
	mlx_loop(cub->mlx.mlx);
}

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		err("Invalid count of arguments\n");
	cub = init_game(av[1]);
	initing(cub);
	free_cub(cub);
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