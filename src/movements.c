/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:21:11 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/08 21:16:08 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->player.posX + cub->player.dirX * WSPEED);
	y = (int)(cub->player.posY);
	if (cub->map[x][y] != '1')
		cub->player.posX += cub->player.dirX * WSPEED;
	x = (int)(cub->player.posX);
	y = (int)(cub->player.posY + cub->player.dirY * WSPEED);
	if (cub->map[x][y] != '1')
		cub->player.posY += cub->player.dirY * WSPEED;
}

void	move_back(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->player.posX - cub->player.dirX * WSPEED);
	y = (int)(cub->player.posY);
	if (cub->map[x][y] != '1')
		cub->player.posX -= cub->player.dirX * WSPEED;
	x = (int)(cub->player.posX);
	y = (int)(cub->player.posY - cub->player.dirY * WSPEED);
	if (cub->map[x][y] != '1')
		cub->player.posY -= cub->player.dirY * WSPEED;
}

void	move_left(t_cub *cub)
{
	int		x;
	int		y;

	x = (int)(cub->player.posX - cub->player.dirX * SSPEED);
	y = (int)(cub->player.posY);
	if (cub->map[x][y] != '1')
		cub->player.posY -= cub->player.dirX * SSPEED;
	x = (int)(cub->player.posX);
	y = (int)(cub->player.posY - cub->player.dirY * SSPEED);
	if (cub->map[x][y] != '1')
		cub->player.posX += cub->player.dirY * SSPEED;
}

void	move_right(t_cub *cub)
{
	int		x;
	int		y;
	
	x = (int)(cub->player.posX - cub->player.dirX * SSPEED);
	y = (int)(cub->player.posY);
	if (cub->map[x][y] != '1')
		cub->player.posY += cub->player.dirX * SSPEED;
	x = (int)(cub->player.posX);
	y = (int)(cub->player.posY - cub->player.dirY * SSPEED);
	if (cub->map[x][y] != '1')
		cub->player.posX -= cub->player.dirY * SSPEED;
}


void	rot_left(t_cub *cub)
{
	double	tmp;

	tmp = cub->player.dirX;
	cub->player.dirX = cub->player.dirX * cos(-ROTSPEED)
		- cub->player.dirY * sin(-ROTSPEED);
	cub->player.dirY = tmp * sin(-ROTSPEED) + cub->player.dirY * cos(-ROTSPEED);
	tmp = cub->player.planeX;
	cub->player.planeX = cub->player.planeX * cos(-ROTSPEED)
		- cub->player.planeY * sin(-ROTSPEED);
	cub->player.planeY = tmp * sin(-ROTSPEED)
		+ cub->player.planeY * cos(-ROTSPEED);
}

void	rot_right(t_cub *cub)
{
	double	tmp;

	tmp = cub->player.dirX;
	cub->player.dirX = cub->player.dirX * cos(ROTSPEED)
		- cub->player.dirY * sin(ROTSPEED);
	cub->player.dirY = tmp * sin(ROTSPEED) + cub->player.dirY * cos(ROTSPEED);
	tmp = cub->player.planeX;
	cub->player.planeX = cub->player.planeX * cos(ROTSPEED)
		- cub->player.planeY * sin(ROTSPEED);
	cub->player.planeY = tmp * sin(ROTSPEED)
		+ cub->player.planeY * cos(ROTSPEED);
}


int	moveing(int key, t_cub *cub)
{
	if (key == W)
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
