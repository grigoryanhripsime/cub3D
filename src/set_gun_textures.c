/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_gun_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:28:17 by anrkhach          #+#    #+#             */
/*   Updated: 2024/08/11 19:28:21 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_gun_0_1(t_cub *cub)
{
	cub->gun[0].img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"./textures/1.xpm", &cub->gun[0].wd,
			&cub->gun[0].ht);
	if (!cub->gun[0].img)
	{
		destroy_doors_and_walls(cub);
		free_cub(cub);
		err("Couldn't open texture!\n");
	}
	cub->gun[1].img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"./textures/2.xpm", &cub->gun[1].wd,
			&cub->gun[1].ht);
	if (!cub->gun[1].img)
	{
		destroy_doors_and_walls(cub);
		mlx_destroy_image(cub->mlx.mlx, cub->gun[0].img);
		free_cub(cub);
		err("Couldn't open texture!\n");
	}
}

void	set_gun_2_3(t_cub *cub)
{
	cub->gun[2].img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"./textures/3.xpm", &cub->gun[2].wd,
			&cub->gun[2].ht);
	if (!cub->gun[2].img)
	{
		destroy_doors_and_walls(cub);
		mlx_destroy_image(cub->mlx.mlx, cub->gun[0].img);
		mlx_destroy_image(cub->mlx.mlx, cub->gun[1].img);
		free_cub(cub);
		err("Couldn't open texture!\n");
	}
	cub->gun[3].img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"./textures/4.xpm", &cub->gun[3].wd,
			&cub->gun[3].ht);
	if (!cub->gun[3].img)
	{
		destroy_doors_and_walls(cub);
		mlx_destroy_image(cub->mlx.mlx, cub->gun[0].img);
		mlx_destroy_image(cub->mlx.mlx, cub->gun[1].img);
		mlx_destroy_image(cub->mlx.mlx, cub->gun[2].img);
		free_cub(cub);
		err("Couldn't open texture!\n");
	}
}

void	set_gun_4(t_cub *cub)
{
	cub->gun[4].img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"./textures/5.xpm", &cub->gun[4].wd,
			&cub->gun[4].ht);
	if (!cub->gun[4].img)
	{
		destroy_doors_and_walls(cub);
		mlx_destroy_image(cub->mlx.mlx, cub->gun[0].img);
		mlx_destroy_image(cub->mlx.mlx, cub->gun[1].img);
		mlx_destroy_image(cub->mlx.mlx, cub->gun[2].img);
		mlx_destroy_image(cub->mlx.mlx, cub->gun[3].img);
		free_cub(cub);
		err("Couldn't open texture!\n");
	}
}

void	set_guns(t_cub *cub)
{
	int	i;

	cub->gun = malloc(sizeof(t_img) * 5);
	if (!cub->gun)
	{
		destroy_doors_and_walls(cub);
		free_cub(cub);
		err("Malloc error!\n");
	}
	set_gun_0_1(cub);
	set_gun_2_3(cub);
	set_gun_4(cub);
	i = -1;
	while (++i < 5)
	{
		cub->gun[i].addr = mlx_get_data_addr(cub->gun[i].img,
				&cub->gun[i].bits_per_pixel, &cub->gun[i].line_len,
				&cub->gun[i].endian);
	}
}
