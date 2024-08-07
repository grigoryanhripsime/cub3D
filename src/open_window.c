/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:04:58 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/07 22:12:30 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_patalok_u_pol(t_cub *cub)
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

int	ft_redraw(t_cub *cub)
{
	cub->img.img = mlx_new_image(cub->mlx.mlx, cub->map_wd, cub->map_ht);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
	draw_patalok_u_pol(cub);
	raycast(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->img.img, 0, 0);
	mlx_destroy_image(cub->mlx.mlx, cub->img.img);
	//printf("posX -> %f | posY -> %f\n", cub->player.posX, cub->player.posY);
	return (0);
}

int moveing(int key, t_cub *cub)
{
	if (key == W)
	{
		if(cub->map[(int)(cub->player.posX + cub->player.dirX * WSPEED)][(int)(cub->player.posY)] == '0')
			cub->player.posX += cub->player.dirX * WSPEED;
		if(cub->map[(int)(cub->player.posX)][(int)(cub->player.posY + cub->player.dirY * WSPEED)] == '0')
			cub->player.posY += cub->player.dirY * WSPEED;
	}
	else if (key == S)
	{
		if(cub->map[(int)(cub->player.posX - cub->player.dirX * SSPEED)][(int)(cub->player.posY)] == '0')
			cub->player.posX -= cub->player.dirX * SSPEED;
		if(cub->map[(int)(cub->player.posX)][(int)(cub->player.posY - cub->player.dirY * SSPEED)] == '0')
			cub->player.posY -= cub->player.dirY * SSPEED;
	}
	else if (key == A)
	{
		double oldDirX = cub->player.dirX;
		cub->player.dirX = cub->player.dirX * cos(-ROTSPEED) - cub->player.dirY * sin(-ROTSPEED);
		cub->player.dirY = oldDirX * sin(-ROTSPEED) + cub->player.dirY * cos(-ROTSPEED);
		double oldPlaneX = cub->player.planeX;
		cub->player.planeX = cub->player.planeX * cos(-ROTSPEED) - cub->player.planeY * sin(-ROTSPEED);
		cub->player.planeY = oldPlaneX * sin(-ROTSPEED) + cub->player.planeY * cos(-ROTSPEED);
		if(cub->map[(int)(cub->player.posX)][(int)(cub->player.posY + cub->player.dirY * ROTSPEED)] == '0')
			cub->player.posY -= cub->player.dirY * ROTSPEED;
		if(cub->map[(int)(cub->player.posX + cub->player.dirX * ROTSPEED)][(int)(cub->player.posY)] == '0')
			cub->player.posY -= cub->player.dirY * ROTSPEED;
	}
	else if (key == D)
	{
		printf("posX -> %f | posY -> %f\n", cub->player.posX, cub->player.posY);
		double oldDirX = cub->player.dirX;
		cub->player.dirX = cub->player.dirX * cos(ROTSPEED) - cub->player.dirY * sin(ROTSPEED);
		cub->player.dirY = oldDirX * sin(ROTSPEED) + cub->player.dirY * cos(ROTSPEED);
		double oldPlaneX = cub->player.planeX;
		cub->player.planeX = cub->player.planeX * cos(ROTSPEED) - cub->player.planeY * sin(ROTSPEED);
		cub->player.planeY = oldPlaneX * sin(ROTSPEED) + cub->player.planeY * cos(ROTSPEED);
	  	if(cub->map[(int)(cub->player.posX)][(int)(cub->player.posY + cub->player.dirY * ROTSPEED)] == '0')
			cub->player.posY -= cub->player.dirY * ROTSPEED;
		if(cub->map[(int)(cub->player.posX + cub->player.dirX * ROTSPEED)][(int)(cub->player.posY)] == '0')
			cub->player.posY -= cub->player.dirY * ROTSPEED;
	}
	return (0);
}

void	initing(t_cub *cub)
{
	cub->map_wd = 1080;
	cub->map_ht = 720;
	get_player_position(cub);
	cub->fc = create_trgb(0, cub->types->F->r, cub->types->F->g, cub->types->F->b);
	cub->rc = create_trgb(0, cub->types->C->r, cub->types->C->g, cub->types->C->b);
	cub->mlx.mlx = mlx_init();
	cub->mlx.win = mlx_new_window(cub->mlx.mlx,
			cub->map_wd, cub->map_ht, "cub3D");
	//ft_redraw(cub);
	mlx_hook(cub->mlx.win, 2, 0, &moveing, cub);
	mlx_loop_hook(cub->mlx.mlx, &ft_redraw, cub);
	mlx_hook(cub->mlx.win, 17, 0, ext, cub);
	mlx_loop(cub->mlx.mlx);
}
