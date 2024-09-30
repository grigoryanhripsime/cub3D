/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:14:16 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/15 17:49:38 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_img	choose_texture(t_cub *vars)
{
	if (vars->ray.hit == 2)
		return (vars->cd);
	if (vars->ray.hit == 3)
		return (vars->od);
	else if (vars->ray.side == 1 && vars->ray.ray_dir_y <= 0)
		return (vars->north);
	else if (vars->ray.side == 0 && vars->ray.ray_dir_x > 0)
		return (vars->south);
	else if (vars->ray.side == 0 && vars->ray.ray_dir_x <= 0)
		return (vars->east);
	return (vars->west);
}

unsigned int	get_color(t_img data, int j, int i)
{
	char			*dst;
	unsigned int	color;

	if (j >= 0 && j < data.wd && i >= 0 && i < data.ht)
	{
		dst = data.addr + (i * data.line_len
				+ j * (data.bits_per_pixel / 8));
		color = *(unsigned int *)dst;
		if (color == 4278190080)
			return (0);
		return (color);
	}
	return (0);
}

int	create_rgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_wall(t_cub *cub, t_tex_place tex, int x)
{
	int	y;

	y = tex.draw_start;
	while (++y < tex.draw_end)
	{
		tex.tex_y = (int)tex.tex_pos & (TEX_HEIGHT - 1);
		tex.tex_pos += tex.step;
		my_pixel_put(&cub->img, x, y,
			get_color(choose_texture(cub), tex.tex_x, tex.tex_y));
	}
}
