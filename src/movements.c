/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:21:11 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/08 14:39:01 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->player.posX + cub->player.dirX * WSPEED);
	y = (int)(cub->player.posY);
	if (cub->map[x][y] == '0')
		cub->player.posX += cub->player.dirX * WSPEED;
	x = (int)(cub->player.posX);
	y = (int)(cub->player.posY + cub->player.dirY * WSPEED);
	if (cub->map[x][y] == '0')
		cub->player.posY += cub->player.dirY * WSPEED;
}

void	move_back(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->player.posX - cub->player.dirX * SSPEED);
	y = (int)(cub->player.posY);
	if (cub->map[x][y] == '0')
		cub->player.posX -= cub->player.dirX * SSPEED;
	x = (int)(cub->player.posX);
	y = (int)(cub->player.posY - cub->player.dirY * SSPEED);
	if (cub->map[x][y] == '0')
		cub->player.posY -= cub->player.dirY * SSPEED;
}

void	move_left(t_cub *cub)
{
	double	tmp;
	int		x;
	int		y;

	tmp = cub->player.dirX;
	cub->player.dirX = cub->player.dirX * cos(-ROTSPEED)
		- cub->player.dirY * sin(-ROTSPEED);
	cub->player.dirY = tmp * sin(-ROTSPEED) + cub->player.dirY * cos(-ROTSPEED);
	tmp = cub->player.planeX;
	cub->player.planeX = cub->player.planeX * cos(-ROTSPEED)
		- cub->player.planeY * sin(-ROTSPEED);
	cub->player.planeY = tmp * sin(-ROTSPEED)
		+ cub->player.planeY * cos(-ROTSPEED);
	x = (int)(cub->player.posX);
	y = (int)(cub->player.posY + cub->player.dirY * ROTSPEED);
	if (cub->map[x][y] == '0')
		cub->player.posY -= cub->player.dirY * ROTSPEED;
	x = (int)(cub->player.posX + cub->player.dirX * ROTSPEED);
	y = (int)(cub->player.posY);
	if (cub->map[x][y] == '0')
		cub->player.posY -= cub->player.dirY * ROTSPEED;
}

void	move_right(t_cub *cub)
{
	double	tmp;
	int		x;
	int		y;

	// printf("posX -> %f | posY -> %f\n", cub->player.posX, cub->player.posY);
	tmp = cub->player.dirX;
	cub->player.dirX = cub->player.dirX * cos(ROTSPEED)
		- cub->player.dirY * sin(ROTSPEED);
	cub->player.dirY = tmp * sin(ROTSPEED) + cub->player.dirY * cos(ROTSPEED);
	tmp = cub->player.planeX;
	cub->player.planeX = cub->player.planeX * cos(ROTSPEED)
		- cub->player.planeY * sin(ROTSPEED);
	cub->player.planeY = tmp * sin(ROTSPEED)
		+ cub->player.planeY * cos(ROTSPEED);
	x = (int)(cub->player.posX);
	y = (int)(cub->player.posY + cub->player.dirY * ROTSPEED);
	if (cub->map[x][y] == '0')
		cub->player.posY -= cub->player.dirY * ROTSPEED;
	x = (int)(cub->player.posX + cub->player.dirX * ROTSPEED);
	y = (int)(cub->player.posY);
	if (cub->map[x][y] == '0')
		cub->player.posY -= cub->player.dirY * ROTSPEED;
}

int	moveing(int key, t_cub *cub)
{
	if (key == W)
		move_forward(cub);
	else if (key == S)
		move_back(cub);
	else if (key == A)
		move_left(cub);
	else if (key == D)
		move_right(cub);
	return (0);
}
