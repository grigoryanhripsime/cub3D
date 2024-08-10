/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:03:55 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/10 16:12:28 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_close_door_texture(t_cub *cub)
{
	int	height;
	int	width;

	cub->cd.img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"textures/CloseDoor.xpm", &width, &height);
	if (!cub->cd.img || width != 64 || height != 64)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->WE.img);
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->NO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->EA.img);
		if (cub->cd.img)
			mlx_destroy_image(cub->mlx.mlx, cub->cd.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Coudn't open door textures\n");
	}
	cub->cd.wd = width;
	cub->cd.ht = height;
	cub->cd.addr = mlx_get_data_addr(cub->cd.img,
			&cub->cd.bits_per_pixel, &cub->cd.line_len, &cub->cd.endian);
}

void	set_open_door_texture(t_cub *cub)
{
	int	height;
	int	width;

	cub->od.img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"textures/OpenDoor.xpm", &width, &height);
	if (!cub->od.img || width != 64 || height != 64)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->WE.img);
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->NO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->EA.img);
		mlx_destroy_image(cub->mlx.mlx, cub->cd.img);
		if (cub->od.img)
			mlx_destroy_image(cub->mlx.mlx, cub->od.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Coudn't open door textures\n");
	}
	cub->od.wd = width;
	cub->od.ht = height;
	cub->od.addr = mlx_get_data_addr(cub->od.img,
			&cub->od.bits_per_pixel, &cub->od.line_len, &cub->od.endian);
}

void	set_gun1(t_cub *cub)
{
	int	width;
	int	height;

	cub->gun.img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"textures/00_frame.xpm", &width, &height);
	if (!cub->gun.img || width != 192 || height != 192)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->WE.img);
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->NO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->EA.img);
		mlx_destroy_image(cub->mlx.mlx, cub->od.img);
		mlx_destroy_image(cub->mlx.mlx, cub->cd.img);
		if (cub->gun.img)
			mlx_destroy_image(cub->mlx.mlx, cub->gun.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Pistol texture error\n");
	}
	cub->gun.wd = width;
	cub->gun.ht = height;
	cub->gun.addr = mlx_get_data_addr(cub->gun.img,
			&cub->gun.bits_per_pixel, &cub->gun.line_len, &cub->gun.endian);
}

void	set_gun2(t_cub *cub)
{
	int	width;
	int	height;

	cub->gun_anim.img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"textures/01_frame.xpm", &width, &height);
	if (!cub->gun_anim.img || width != 192 || height != 192)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->WE.img);
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->NO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->EA.img);
		mlx_destroy_image(cub->mlx.mlx, cub->od.img);
		mlx_destroy_image(cub->mlx.mlx, cub->cd.img);
		mlx_destroy_image(cub->mlx.mlx, cub->gun.img);
		if (cub->gun_anim.img)
			mlx_destroy_image(cub->mlx.mlx, cub->gun_anim.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Pistol texture error\n");
	}
	cub->gun_anim.wd = width;
	cub->gun_anim.ht = height;
	cub->gun_anim.addr = mlx_get_data_addr(cub->gun_anim.img,
			&cub->gun_anim.bits_per_pixel, &cub->gun_anim.line_len,
			&cub->gun_anim.endian);
}
