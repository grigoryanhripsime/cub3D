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
#include <X11/keysym.h>  // Include for Linux key definitions

void move_forward(t_cub *cub)
{
	double new_x = cub->player.pos_x + cub->player.dir_x * WSPEED;
	double new_y = cub->player.pos_y + cub->player.dir_y * WSPEED;

	if (cub->map[(int)new_x][(int)cub->player.pos_y] != '1')
		cub->player.pos_x = new_x;
	if (cub->map[(int)cub->player.pos_x][(int)new_y] != '1')
		cub->player.pos_y = new_y;
}

void move_back(t_cub *cub)
{
	double new_x = cub->player.pos_x - cub->player.dir_x * WSPEED;
	double new_y = cub->player.pos_y - cub->player.dir_y * WSPEED;

	if (cub->map[(int)new_x][(int)cub->player.pos_y] != '1')
		cub->player.pos_x = new_x;
	if (cub->map[(int)cub->player.pos_x][(int)new_y] != '1')
		cub->player.pos_y = new_y;
}

void move_left(t_cub *cub)
{
	double new_x = cub->player.pos_x - cub->player.dir_y * SSPEED;
	double new_y = cub->player.pos_y + cub->player.dir_x * SSPEED;

	if (cub->map[(int)new_x][(int)cub->player.pos_y] != '1')
		cub->player.pos_x = new_x;
	if (cub->map[(int)cub->player.pos_x][(int)new_y] != '1')
		cub->player.pos_y = new_y;
}

void move_right(t_cub *cub)
{
	double new_x = cub->player.pos_x + cub->player.dir_y * SSPEED;
	double new_y = cub->player.pos_y - cub->player.dir_x * SSPEED;

	if (cub->map[(int)new_x][(int)cub->player.pos_y] != '1')
		cub->player.pos_x = new_x;
	if (cub->map[(int)cub->player.pos_x][(int)new_y] != '1')
		cub->player.pos_y = new_y;
}

int moveing(int key, t_cub *cub)
{
	if (key == XK_Escape)   // Ubuntu equivalent for ESC
		esc(cub);
	if (key == XK_space)
		cub->play = true;
	else if (key == XK_e)
		try_to_open_door(cub);
	else if (key == XK_w)
		move_forward(cub);
	else if (key == XK_s)
		move_back(cub);
	else if (key == XK_d)
		move_right(cub);  // Corrected movement direction
	else if (key == XK_a)
		move_left(cub);   // Corrected movement direction
	else if (key == XK_Left)
		rot_left(cub);
	else if (key == XK_Right)
		rot_right(cub);
	return (0);
}
