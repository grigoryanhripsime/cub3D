/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:21:11 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/11 20:25:55 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->player.pos_x + cub->player.dir_x * WSPEED);
	y = (int)(cub->player.pos_y);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.pos_x += cub->player.dir_x * WSPEED;
	x = (int)(cub->player.pos_x);
	y = (int)(cub->player.pos_y + cub->player.dir_y * WSPEED);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.pos_y += cub->player.dir_y * WSPEED;
}

void	move_back(t_cub *cub)
{
	int	x;
	int	y;

	x = (int)(cub->player.pos_x - cub->player.dir_x * WSPEED);
	y = (int)(cub->player.pos_y);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.pos_x -= cub->player.dir_x * WSPEED;
	x = (int)(cub->player.pos_x);
	y = (int)(cub->player.pos_y - cub->player.dir_y * WSPEED);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.pos_y -= cub->player.dir_y * WSPEED;
}

void	move_left(t_cub *cub)
{
	int		x;
	int		y;

	x = (int)(cub->player.pos_x);
	y = (int)(cub->player.pos_y - cub->player.dir_x * SSPEED);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.pos_y -= cub->player.dir_x * SSPEED;
	x = (int)(cub->player.pos_x + cub->player.dir_y * SSPEED);
	y = (int)(cub->player.pos_y);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.pos_x += cub->player.dir_y * SSPEED;
}

void	move_right(t_cub *cub)
{
	int		x;
	int		y;

	x = (int)(cub->player.pos_x);
	y = (int)(cub->player.pos_y + cub->player.dir_x * SSPEED);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.pos_y += cub->player.dir_x * SSPEED;
	x = (int)(cub->player.pos_x - cub->player.dir_y * SSPEED);
	y = (int)(cub->player.pos_y);
	if (cub->map[x][y] != '1' && cub->map[x][y] != 'C')
		cub->player.pos_x -= cub->player.dir_y * SSPEED;
}

int	moveing(int key, t_cub *cub)
{
	if (key == 53)
		esc(cub);
	if (key == SPACE)
		cub->play = true;
	else if (key == E)
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
