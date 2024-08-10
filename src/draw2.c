/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:04:58 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/10 16:08:14 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
			&cub->img.line_len, &cub->img.endian);
	draw_patalok_u_pol(cub);
	raycasting(cub);
	minimap(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->img.img, 0, 0);
	mlx_destroy_image(cub->mlx.mlx, cub->img.img);
	return (0);
}

void	gun(t_cub *cub)
{
	int	x;
	int	y;
	int	px;
	int	py;

	px = 0;
	x = cub->map_wd / 2 - cub->gun.wd / 2 - 1;
	while (++x < cub->map_wd / 2 + cub->gun.wd / 2)
	{
		y = cub->map_ht - cub->gun.ht - 1;
		py = 0;
		while (++y < cub->img.ht)
		{
			my_mlx_pixel_put(&cub->img, x, y,
				my_mlx_color_taker(cub->gun, px, py));
			py++;
		}
		px++;
	}
}
