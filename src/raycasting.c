/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:24:00 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/09 20:02:57 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


t_img	choose_texture(t_cub *vars)
{
	if (vars->ray.hit == 2)
		return (vars->closeD);
	if (vars->ray.hit == 3)
		return (vars->openD);
	else if (vars->ray.side == 1 && vars->ray.rayDirY <= 0)
		return (vars->NO);
	else if (vars->ray.side == 0 && vars->ray.rayDirX > 0)
		return (vars->SO);
	else if (vars->ray.side == 0 && vars->ray.rayDirX <= 0)
		return (vars->EA);
	return (vars->WE);
}

unsigned int	my_mlx_color_taker(t_img data, int j, int i)
{
	char			*dst;

	if (j >= 0 && j < data.wd && i >= 0 && i < data.ht)
	{
		dst = data.addr + (i * data.line_length
				+ j * (data.bits_per_pixel / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}

void	raycasting(t_cub *cub)
{
	t_tex_place	tex;
	int			x;

	x = -1;
	while (++x < cub->map_wd)
	{
		set_ray(cub, x);
		cub->ray.hit = 0;
		check_ray(cub);
		find_wall(cub);
		//printf("1 ->  %f | 2 -> %d\n", cub->ray.wallDist, tex.lineHeight);
		if (cub->ray.side == 0)
			cub->ray.wallDist = cub->ray.sideDistX - cub->ray.deltaDistX;
		else
			cub->ray.wallDist = cub->ray.sideDistY - cub->ray.deltaDistY;
		tex = set_texture(cub);
		//printf("start -> %d  |  end -> %d\n", tex.drawStart, tex.drawEnd);
		draw_wall(cub, tex, x);
	}
}
