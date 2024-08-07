/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:29:23 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/07 21:38:53 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 2)
		err("Invalid count of arguments\n");
	cub = init_game(av[1]);
	initing(cub);
	free_cub(cub);
}
