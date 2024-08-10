/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_wall_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:02:19 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/10 15:30:59 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_SO_texture(t_cub *cub)
{
	int	height;
	int	width;

	cub->SO.img = mlx_xpm_file_to_image(cub->mlx.mlx,
			cub->types->SO, &width, &height);
	if (!cub->SO.img || width != 64 || height != 64)
	{
		printf("hehe   width: %d, height: %d\n", width, height);
		if (cub->SO.img)
			mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Coudn't open wall textures\n");
	}
	cub->SO.wd = width;
	cub->SO.ht = height;
	cub->SO.addr = mlx_get_data_addr(cub->SO.img,
			&cub->SO.bits_per_pixel, &cub->SO.line_len, &cub->SO.endian);
}

void	set_NO_texture(t_cub *cub)
{
	int	height;
	int	width;

	cub->NO.img = mlx_xpm_file_to_image(cub->mlx.mlx,
			cub->types->NO, &width, &height);
	if (!cub->NO.img || width != 64 || height != 64)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		if (cub->NO.img)
			mlx_destroy_image(cub->mlx.mlx, cub->NO.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Coudn't open wall textures\n");
	}
	cub->NO.wd = width;
	cub->NO.ht = height;
	cub->NO.addr = mlx_get_data_addr(cub->NO.img,
			&cub->NO.bits_per_pixel, &cub->NO.line_len, &cub->NO.endian);
}

void	set_WE_texture(t_cub *cub)
{
	int	height;
	int	width;

	cub->WE.img = mlx_xpm_file_to_image(cub->mlx.mlx,
			cub->types->WE, &width, &height);
	if (!cub->WE.img || width != 64 || height != 64)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->NO.img);
		if (cub->WE.img)
			mlx_destroy_image(cub->mlx.mlx, cub->WE.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Coudn't open wall textures\n");
	}
	cub->WE.wd = width;
	cub->WE.ht = height;
	cub->WE.addr = mlx_get_data_addr(cub->WE.img,
			&cub->WE.bits_per_pixel, &cub->WE.line_len, &cub->WE.endian);
}

void	set_EA_texture(t_cub *cub)
{
	int	height;
	int	width;

	cub->EA.img = mlx_xpm_file_to_image(cub->mlx.mlx,
			cub->types->EA, &width, &height);
	if (!cub->EA.img || width != 64 || height != 64)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->WE.img);
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->NO.img);
		if (cub->EA.img)
			mlx_destroy_image(cub->mlx.mlx, cub->EA.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Coudn't open wall textures\n");
	}
	cub->EA.wd = width;
	cub->EA.ht = height;
	cub->EA.addr = mlx_get_data_addr(cub->EA.img,
			&cub->EA.bits_per_pixel, &cub->EA.line_len, &cub->EA.endian);
}
