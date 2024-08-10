/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:10:45 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/10 15:36:31 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	try_to_open_door(t_cub *cub)
{
	printf("x-> %f | y-> %f\n", cub->player.dirX, cub->player.dirY);
	int	x;
	int	y;

	x = (int)cub->player.posX;
	y = (int)cub->player.posY;
	if (cub->player.dirX < -0.05)
		x = (int)cub->player.posX - 1;
	else if (cub->player.dirX > 0.05)
		x = (int)cub->player.posX + 1;
	if (cub->player.dirY < -0.05)
		y = (int)cub->player.posY - 1;
	else if (cub->player.dirY > 0.05)
		y = (int)cub->player.posY + 1;
	if (cub->map[x][y] == 'C')
		cub->map[x][y] = 'O';
	else if (cub->map[x][y] == 'O')
		cub->map[x][y] = 'C';
}

int	mouse_rot(int x, int y, t_cub *cub)
{
	static int	past_view;

	y = 0;
	if (x < past_view)
		rot_right(cub);
	else if (x > past_view)
		rot_left(cub);
	past_view = x;
	return (0);
}
