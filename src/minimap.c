/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:08:41 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/11 20:25:29 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_square(double i, double j, t_cub *cub, int color)
{
	int	k;
	int	l;

	k = (i * 10) - 5;
	while (k < (i * 10) + 5)
	{
		l = (j * 10) - 5;
		while (l < (j * 10) + 5)
		{
			my_mlx_pixel_put(&cub->img, l + 10, k + 10, color);
			l++;
		}
		k++;
	}
}

void	minimap(t_cub *cub)
{
	int	i;
	int	j;
	int	color;

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
				continue ;
			draw_square(i, j, cub, color);
		}
	}
	draw_square(cub->player.pos_x - 0.5, cub->player.pos_y - 0.5,
		cub, create_trgb(0, 255, 255, 0));
}
