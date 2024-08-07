/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:24:00 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/07 21:50:24 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define screenWidth 640
#define screenHeight 480
#define texWidth 64 // must be power of two
#define texHeight 64 // must be power of two
#define mapWidth 24
#define mapHeight 24

void get_player_position(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
				|| cub->map[i][j] == 'W' || cub->map[i][j] == 'E')
			{
				cub->player.posX = i;
				cub->player.posY = j;
			}
			j++;
		}
		i++;
	}
}

void init_cub_vars(t_cub *cub)
{
	cub->player.dirX = -1.0;
	cub->player.dirY = 0.0;
	cub->player.planeX = 0.0;
	cub->player.planeY = 0.66;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_img	*choose_texture(t_cub *vars)
{
	if (vars->ray.hit == 2)
		return (&vars->cdoor);
	else if (vars->ray.hit == 3)
		return (&vars->odoor);
	else if (vars->ray.side == 1 && vars->ray.rayDirY <= 0)
		return (vars->wall);
	else if (vars->ray.side == 0 && vars->ray.rayDirX > 0)
		return (vars->wall + 1);
	else if (vars->ray.side == 0 && vars->ray.rayDirX <= 0)
		return (vars->wall + 2);
	return (vars->wall + 3);
}


unsigned int	my_mlx_color_taker(t_img *data, int j, int i)
{
	char			*dst;

	if (j >= 0 && j < data->wd && i >= 0 && i < data->ht)
	{
		dst = data->addr + (i * data->line_length
				+ j * (data->bits_per_pixel / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}

void raycast(t_cub *cub)
{
	t_texture tex;
	double	wallX;
	
	init_cub_vars(cub);
	// while (1)
	// {
		for (int x = 0; x < cub->map_wd; x++)
		{
			cub->ray.cameraX = 2 * x / (double)cub->map_wd - 1;
			cub->ray.rayDirX = cub->player.dirX + cub->player.planeX * cub->ray.cameraX;
			cub->ray.rayDirY = cub->player.dirY + cub->player.planeY * cub->ray.cameraX;
			
			cub->player.mapX = (int)cub->player.posX;
			cub->player.mapY = (int)cub->player.posY;

			cub->ray.deltaDistX = (cub->ray.rayDirX == 0) ? 1e30 : fabs(1 / cub->ray.rayDirX);
			cub->ray.deltaDistY = (cub->ray.rayDirY == 0) ? 1e30 : fabs(1 / cub->ray.rayDirY);
			
			cub->ray.hit = 0;
			if(cub->ray.rayDirX < 0)
			{
				cub->player.stepX = -1;
				cub->ray.sideDistX = (cub->player.posX - cub->player.mapX) * cub->ray.deltaDistX;
			}
			else
			{
				cub->player.stepX = 1;
				cub->ray.sideDistX = (cub->player.mapX + 1.0 - cub->player.posX) * cub->ray.deltaDistX;
			}
			if(cub->ray.rayDirY < 0)
			{
				cub->player.stepY = -1;
				cub->ray.sideDistY = (cub->player.posY - cub->player.mapY) * cub->ray.deltaDistY;
			}
			else
			{
				cub->player.stepY = 1;
				cub->ray.sideDistY = (cub->player.mapY + 1.0 - cub->player.posY) * cub->ray.deltaDistY;
			}

			while (cub->ray.hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
				if(cub->ray.sideDistX < cub->ray.sideDistY)
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
				if(cub->map[cub->player.mapX][cub->player.mapY] == '1')
					cub->ray.hit = 1;
			}
			//printf("1 ->  %f | 2 -> %d\n", cub->ray.wallDist, tex.lineHeight);

			if(cub->ray.side == 0)
				cub->ray.wallDist = (cub->ray.sideDistX - cub->ray.deltaDistX);
			else
				cub->ray.wallDist = (cub->ray.sideDistY - cub->ray.deltaDistY);
			
			tex.lineHeight = (int)(cub->map_ht / cub->ray.wallDist);
			tex.drawStart = -tex.lineHeight / 2 + cub->map_ht / 2;
			if (tex.drawStart < 0)
				tex.drawStart = 0;
			tex.drawEnd = tex.lineHeight / 2 + cub->map_ht / 2;
			if (tex.drawEnd >= cub->map_ht)
				tex.drawEnd = cub->map_ht - 1;
			//

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
			tex.texPos = (tex.drawStart - cub->map_ht / 2 + tex.lineHeight / 2) * tex.step;
			
			//printf("start -> %d  |  end -> %d\n", tex.drawStart, tex.drawEnd);
			for(int y = tex.drawStart; y < tex.drawEnd; y++)
			{
				tex.texY = (int)tex.texPos & (texHeight - 1);
				tex.texPos += tex.step;
				my_mlx_pixel_put(&cub->img, x, y, create_trgb(0, 182, 165, 17));		
			}
		}
	// }
}

