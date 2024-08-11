/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:14:16 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/11 20:00:46 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
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
	else if (vars->ray.side == 1 && vars->ray.rayDirY <= 0)
		return (vars->north);
	else if (vars->ray.side == 0 && vars->ray.rayDirX > 0)
		return (vars->south);
	else if (vars->ray.side == 0 && vars->ray.rayDirX <= 0)
		return (vars->east);
	return (vars->west);
}

unsigned int	my_mlx_color_taker(t_img data, int j, int i)
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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_wall(t_cub *cub, t_tex_place tex, int x)
{
	int	y;

	y = tex.drawStart;
	while (++y < tex.drawEnd)
	{
		tex.texY = (int)tex.texPos & (TEX_HEIGHT - 1);
		tex.texPos += tex.step;
		my_mlx_pixel_put(&cub->img, x, y,
			my_mlx_color_taker(choose_texture(cub), tex.texX, tex.texY));
	}
}
