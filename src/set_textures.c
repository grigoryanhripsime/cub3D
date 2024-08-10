/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:03:55 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/10 18:07:00 by anrkhach         ###   ########.fr       */
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
	cub->gun = malloc(sizeof(t_img) * 5);
	// if (!cub->gun)
	// 	error
	cub->gun[0].img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"./textures/00_frame.xpm", &cub->gun[0].wd,
			&cub->gun[0].ht);
	cub->gun[1].img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"./textures/01_frame.xpm", &cub->gun[1].wd,
			&cub->gun[1].ht);
	cub->gun[2].img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"./textures/02_frame.xpm", &cub->gun[2].wd,
			&cub->gun[2].ht);
	cub->gun[3].img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"./textures/03_frame.xpm", &cub->gun[3].wd,
			&cub->gun[3].ht);
	cub->gun[4].img = mlx_xpm_file_to_image(cub->mlx.mlx,
			"./textures/04_frame.xpm", &cub->gun[4].wd,
			&cub->gun[4].ht);
	// if (!cub->gun[0].img || !cub->gun[1].img
	// 	|| !cub->gun[2].img || !cub->gun[3].img
	// 	|| !cub->gun[4].img)
	// 	error
	int i = -1;
	while (++i < 5)
	{
		cub->gun[i].addr = mlx_get_data_addr(cub->gun[i].img,
				&cub->gun[i].bits_per_pixel, &cub->gun[i].line_len,
				&cub->gun[i].endian);
		// if (!cub->gun[i].addr)
		// 	error
	}
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
