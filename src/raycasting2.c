/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:24:33 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/09 13:20:00 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_ray(t_cub *cub, int x)
{
	cub->ray.cameraX = 2 * x / (double)cub->map_wd - 1;
	cub->ray.rayDirX = cub->player.dirX + cub->player.planeX * cub->ray.cameraX;
	cub->ray.rayDirY = cub->player.dirY + cub->player.planeY * cub->ray.cameraX;
	cub->player.mapX = (int)cub->player.posX;
	cub->player.mapY = (int)cub->player.posY;
	if (cub->ray.rayDirX == 0)
		cub->ray.deltaDistX = 1e30;
	else
		cub->ray.deltaDistX = fabs(1 / cub->ray.rayDirX);
	if (cub->ray.rayDirY == 0)
		cub->ray.deltaDistY = 1e30;
	else
		cub->ray.deltaDistY = fabs(1 / cub->ray.rayDirY);
}

void	check_ray(t_cub *cub)
{
	if (cub->ray.rayDirX < 0)
	{
		cub->player.stepX = -1;
		cub->ray.sideDistX = (cub->player.posX - cub->player.mapX)
			* cub->ray.deltaDistX;
	}
	else
	{
		cub->player.stepX = 1;
		cub->ray.sideDistX = (cub->player.mapX + 1.0 - cub->player.posX)
			* cub->ray.deltaDistX;
	}
	if (cub->ray.rayDirY < 0)
	{
		cub->player.stepY = -1;
		cub->ray.sideDistY = (cub->player.posY - cub->player.mapY)
			* cub->ray.deltaDistY;
	}
	else
	{
		cub->player.stepY = 1;
		cub->ray.sideDistY = (cub->player.mapY + 1.0 - cub->player.posY)
			* cub->ray.deltaDistY;
	}
}

void	find_wall(t_cub *cub)
{
	while (cub->ray.hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (cub->ray.sideDistX < cub->ray.sideDistY)
		{
			cub->ray.sideDistX += cub->ray.deltaDistX;
			cub->player.mapX += cub->player.stepX;
			cub->ray.side = 0;
		}
		else
		{
			cub->ray.sideDistY += cub->ray.deltaDistY;
			cub->player.mapY += cub->player.stepY;
			cub->ray.side = 1;
		}
		//Check if ray has hit a wall
		if (cub->map[cub->player.mapX]
			&& cub->map[cub->player.mapX][cub->player.mapY]
			&& cub->map[cub->player.mapX][cub->player.mapY] == '1')
			cub->ray.hit = 1;
	}
}

t_tex_place	set_texture(t_cub *cub)
{
	double		wallX;
	t_tex_place	tex;

	tex.lineHeight = (int)(cub->map_ht / cub->ray.wallDist);
	tex.drawStart = -tex.lineHeight / 2 + cub->map_ht / 2;
	if (tex.drawStart < 0)
		tex.drawStart = 0;
	tex.drawEnd = tex.lineHeight / 2 + cub->map_ht / 2;
	if (tex.drawEnd >= cub->map_ht)
		tex.drawEnd = cub->map_ht - 1;
	if (cub->ray.side == 0)
		wallX = cub->player.posY + cub->ray.wallDist * cub->ray.rayDirY;
	else
		wallX = cub->player.posX + cub->ray.wallDist * cub->ray.rayDirX;
	wallX -= floor(wallX);
	tex.texX = (int)(wallX * (double)texWidth);
	if (cub->ray.side == 0 && cub->ray.rayDirX > 0)
		tex.texX = texWidth - tex.texX - 1;
	if (cub->ray.side == 1 && cub->ray.rayDirY < 0)
		tex.texX = texWidth - tex.texX - 1;
	tex.step = 1.0 * texHeight / tex.lineHeight;
	tex.texPos = (tex.drawStart - cub->map_ht / 2 + tex.lineHeight / 2)
		* tex.step;
	return (tex);
}

void	draw_wall(t_cub *cub, t_tex_place tex, int x)
{
	int	y;

	y = tex.drawStart;
	while (++y < tex.drawEnd)
	{
		tex.texY = (int)tex.texPos & (texHeight - 1);
		tex.texPos += tex.step;
		my_mlx_pixel_put(&cub->img, x, y, my_mlx_color_taker(choose_texture(cub), tex.texX, tex.texY));
		// draw_image_pixel_by_pixel(cub, x, y);
	}
}
