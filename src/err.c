/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:28:17 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/02 20:29:13 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_map_struct(t_map *map)
{
	t_map	*tmp;

	if (!map)
		return ;
	while (map)
	{
		free(map->line);
		tmp = map->next;
		free(map);
		map = tmp;
	}
	map = NULL;
}

void	free_map(char **map)
{
	int i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	err(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}
