/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:04:58 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/06 16:11:14 by hrigrigo         ###   ########.fr       */
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

void	ft_redraw(t_cub *cub)
{
	cub->img.img = mlx_new_image(cub->mlx.mlx, cub->map_wd, cub->map_ht);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
	draw_patalok_u_pol(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->img.img, 0, 0);
	mlx_destroy_image(cub->mlx.mlx, cub->img.img);
}

void	initing(t_cub *cub)
{
	cub->map_wd = 1080;
	cub->map_ht = 720;
	cub->fc = create_trgb(0, 135, 67, 94);
	cub->rc = create_trgb(0, 15, 21, 190);
	cub->mlx.mlx = mlx_init();
	cub->mlx.win = mlx_new_window(cub->mlx.mlx,
			cub->map_wd, cub->map_ht, "cub3D");
	ft_redraw(cub);
	mlx_hook(cub->mlx.win, 17, 0, ext, cub);
	mlx_loop(cub->mlx.mlx);
}
