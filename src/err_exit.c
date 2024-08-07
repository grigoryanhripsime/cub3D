/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:28:17 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/07 12:23:46 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	err(char *str)
{
	write(2, str, ft_strlen(str));
	// system("leaks cub3D");
	exit(1);
}

int	ext(void *params)
{
	t_cub		*cub;

	cub = params;
	mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	exit(0);
	return (0);
}
