/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:24:33 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/07 12:26:48 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	dda_algorithm(t_cub *vars)
{
	while (vars->ray.hit == 0)
	{
		if (vars->ray.sideDistX < vars->ray.sideDistY)
		{
			vars->ray.sideDistX += vars->ray.deltadistX;
			vars->player.mapX += vars->player.stepX;
			vars->ray.side = 0;
		}
		else
		{
			vars->ray.sideDistY += vars->ray.deltadistY;
			vars->player.mapY += vars->player.stepY;
			vars->ray.side = 1;
		}
		if (vars->map[vars->player.mapX][vars->player.mapY] == '1')
			vars->ray.hit = 1;
		else if (vars->map[vars->player.mapX][vars->player.mapY] == 'D')
			vars->ray.hit = 2;
		else if (vars->map[vars->player.mapX][vars->player.mapY] == 'O')
			vars->ray.hit = 3;
	}
	if (vars->ray.side == 0)
		vars->ray.wallDist = (vars->ray.sideDistX - vars->ray.deltadistX);
	else
		vars->ray.wallDist = (vars->ray.sideDistY - vars->ray.deltadistY);
}

void	raycasting(t_cub *vars)
{
	int		i;

	//draw_floor(vars);
	i = -1;
	while (++i <= vars->map_wd)
	{
		ray_pos(vars, i);
		step_dir(vars);
		vars->ray.hit = 0;
		dda_algorithm(vars);
	}
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win, vars->img.img, 0, 0);
}
