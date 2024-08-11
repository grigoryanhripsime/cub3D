/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:24:00 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/11 20:37:11 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_ray(t_cub *cub, int x)
{
	cub->ray.camera_x = 2 * x / (double)cub->map_wd - 1;
	cub->ray.ray_dir_x = cub->player.dir_x
		+ cub->player.plane_x * cub->ray.camera_x;
	cub->ray.ray_dir_y = cub->player.dir_y
		+ cub->player.plane_y * cub->ray.camera_x;
	cub->player.map_x = (int)cub->player.pos_x;
	cub->player.map_y = (int)cub->player.pos_y;
	if (cub->ray.ray_dir_x == 0)
		cub->ray.delta_dist_x = 1e30;
	else
		cub->ray.delta_dist_x = fabs(1 / cub->ray.ray_dir_x);
	if (cub->ray.ray_dir_y == 0)
		cub->ray.delta_dist_y = 1e30;
	else
		cub->ray.delta_dist_y = fabs(1 / cub->ray.ray_dir_y);
}

void	check_ray(t_cub *cub)
{
	if (cub->ray.ray_dir_x < 0)
	{
		cub->player.step_x = -1;
		cub->ray.side_dist_x = (cub->player.pos_x - cub->player.map_x)
			* cub->ray.delta_dist_x;
	}
	else
	{
		cub->player.step_x = 1;
		cub->ray.side_dist_x = (cub->player.map_x + 1.0 - cub->player.pos_x)
			* cub->ray.delta_dist_x;
	}
	if (cub->ray.ray_dir_y < 0)
	{
		cub->player.step_y = -1;
		cub->ray.side_dist_y = (cub->player.pos_y - cub->player.map_y)
			* cub->ray.delta_dist_y;
	}
	else
	{
		cub->player.step_y = 1;
		cub->ray.side_dist_y = (cub->player.map_y + 1.0 - cub->player.pos_y)
			* cub->ray.delta_dist_y;
	}
}

void	find_wall(t_cub *cub)
{
	while (cub->ray.hit == 0)
	{
		if (cub->ray.side_dist_x < cub->ray.side_dist_y)
		{
			cub->ray.side_dist_x += cub->ray.delta_dist_x;
			cub->player.map_x += cub->player.step_x;
			cub->ray.side = 0;
		}
		else
		{
			cub->ray.side_dist_y += cub->ray.delta_dist_y;
			cub->player.map_y += cub->player.step_y;
			cub->ray.side = 1;
		}
		if (cub->map[cub->player.map_x][cub->player.map_y] == '1')
			cub->ray.hit = 1;
		if (cub->map[cub->player.map_x][cub->player.map_y] == 'C')
			cub->ray.hit = 2;
		if (cub->map[cub->player.map_x][cub->player.map_y] == 'O')
			cub->ray.hit = 3;
	}
}

t_tex_place	set_texture(t_cub *cub)
{
	double		wall_x;
	t_tex_place	tex;

	tex.line_height = (int)(cub->map_ht / cub->ray.wall_dist);
	tex.draw_start = -tex.line_height / 2 + cub->map_ht / 2;
	if (tex.draw_start < 0)
		tex.draw_start = 0;
	tex.draw_end = tex.line_height / 2 + cub->map_ht / 2;
	if (tex.draw_end >= cub->map_ht)
		tex.draw_end = cub->map_ht - 1;
	if (cub->ray.side == 0)
		wall_x = cub->player.pos_y + cub->ray.wall_dist * cub->ray.ray_dir_y;
	else
		wall_x = cub->player.pos_x + cub->ray.wall_dist * cub->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	tex.tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if (cub->ray.side == 0 && cub->ray.ray_dir_x > 0)
		tex.tex_x = TEX_WIDTH - tex.tex_x - 1;
	if (cub->ray.side == 1 && cub->ray.ray_dir_y < 0)
		tex.tex_x = TEX_WIDTH - tex.tex_x - 1;
	tex.step = 1.0 * TEX_HEIGHT / tex.line_height;
	tex.tex_pos = (tex.draw_start - cub->map_ht / 2 + tex.line_height / 2)
		* tex.step;
	return (tex);
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
		if (cub->ray.side == 0)
			cub->ray.wall_dist = cub->ray.side_dist_x - cub->ray.delta_dist_x;
		else
			cub->ray.wall_dist = cub->ray.side_dist_y - cub->ray.delta_dist_y;
		tex = set_texture(cub);
		draw_wall(cub, tex, x);
	}
}
