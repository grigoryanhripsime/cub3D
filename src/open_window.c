/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:04:58 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/10 14:22:38 by hrigrigo         ###   ########.fr       */
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

void	draw_square(double i, double j, t_cub *cub, int color)
{
	int	k;
	int l;

	k = (i * 10) - 5;
	while (k < (i * 10) + 5)
	{
		l = (j * 10) - 5;
		while (l < (j * 10) + 5)
		{
			// printf("l = %d, k = %d\n", l, k);
			my_mlx_pixel_put(&cub->img, l + 10, k + 10, color);
			l++;
		}
		k++;
	}
	// my_mlx_pixel_put(&cub->img, j * 10 + 10, i * 10 + 10, create_trgb(0, 0, 0, 0));
}

void minimap(t_cub *cub)
{
	int	i;
	int	j;
	int color;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == '1')
				color = create_trgb(0, 0, 0, 153);
			else if (cub->map[i][j] == '0')
				color = create_trgb(0, 153, 204, 255);
			else if (cub->map[i][j] == 'C')
				color = create_trgb(0, 0, 204, 204);
			else if (cub->map[i][j] == 'O')
				color = create_trgb(0, 102, 255, 178);
			else
				continue;
			draw_square(i, j, cub, color);
		}
	}
	draw_square(cub->player.posX - 0.5, cub->player.posY - 0.5, cub, create_trgb(0, 255, 255, 0));
}


int	ft_redraw(t_cub *cub)
{
	cub->img.img = mlx_new_image(cub->mlx.mlx, cub->map_wd, cub->map_ht);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel,
			&cub->img.line_length, &cub->img.endian);
	draw_patalok_u_pol(cub);
	raycasting(cub);
	minimap(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->img.img, 0, 0);
	mlx_destroy_image(cub->mlx.mlx, cub->img.img);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
