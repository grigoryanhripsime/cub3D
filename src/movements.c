/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:21:11 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/10 15:36:52 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->player.posX + cub->player.dirX * WSPEED);
	y = (int)(cub->player.posY);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.posX += cub->player.dirX * WSPEED;
	x = (int)(cub->player.posX);
	y = (int)(cub->player.posY + cub->player.dirY * WSPEED);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.posY += cub->player.dirY * WSPEED;
}

void	move_back(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->player.posX - cub->player.dirX * WSPEED);
	y = (int)(cub->player.posY);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.posX -= cub->player.dirX * WSPEED;
	x = (int)(cub->player.posX);
	y = (int)(cub->player.posY - cub->player.dirY * WSPEED);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.posY -= cub->player.dirY * WSPEED;
}

void	move_left(t_cub *cub)
{
	int		x;
	int		y;

	x = (int)(cub->player.posX);
	y = (int)(cub->player.posY - cub->player.dirX * SSPEED);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.posY -= cub->player.dirX * SSPEED;
	x = (int)(cub->player.posX + cub->player.dirY * SSPEED);
	y = (int)(cub->player.posY);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.posX += cub->player.dirY * SSPEED;
}

void	move_right(t_cub *cub)
{
	int		x;
	int		y;

	x = (int)(cub->player.posX);
	y = (int)(cub->player.posY + cub->player.dirX * SSPEED);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.posY += cub->player.dirX * SSPEED;
	x = (int)(cub->player.posX - cub->player.dirY * SSPEED);
	y = (int)(cub->player.posY);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.posX -= cub->player.dirY * SSPEED;
}

int	moveing(int key, t_cub *cub)
{
	if (key == 53)
	{
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		//add destroying textures and freeing
		free_cub(cub);
		exit(0);
	}
	if (key == E)
		try_to_open_door(cub);
	else if (key == W)
		move_forward(cub);
	else if (key == S)
		move_back(cub);
	else if (key == D)
		move_left(cub);
	else if (key == A)
		move_right(cub);
	else if (key == LARROW)
		rot_right(cub);
	else if (key == RARROW)
		rot_left(cub);
	return (0);
}
