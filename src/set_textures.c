/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:03:55 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/11 19:59:06 by anrkhach         ###   ########.fr       */
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
		mlx_destroy_image(cub->mlx.mlx, cub->west.img);
		mlx_destroy_image(cub->mlx.mlx, cub->south.img);
		mlx_destroy_image(cub->mlx.mlx, cub->north.img);
		mlx_destroy_image(cub->mlx.mlx, cub->east.img);
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
		mlx_destroy_image(cub->mlx.mlx, cub->west.img);
		mlx_destroy_image(cub->mlx.mlx, cub->south.img);
		mlx_destroy_image(cub->mlx.mlx, cub->north.img);
		mlx_destroy_image(cub->mlx.mlx, cub->east.img);
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
