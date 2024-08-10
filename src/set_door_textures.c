/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_door_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:03:55 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/10 15:35:02 by hrigrigo         ###   ########.fr       */
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
