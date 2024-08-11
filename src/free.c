/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:08:46 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/11 19:58:18 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_map_struct(t_lst *map)
{
	t_lst	*tmp;

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

void	free_array(char **map)
{
	int	i;

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

void	free_types(t_type *types)
{
	if (!types)
		return ;
	if (types->north)
		free(types->north);
	if (types->south)
		free(types->south);
	if (types->west)
		free(types->west);
	if (types->east)
		free(types->east);
	if (types->F)
		free(types->F);
	if (types->C)
		free(types->C);
	free(types);
}

void	free_cub(t_cub *cub)
{
	free_array(cub->map);
	cub->map = NULL;
	free_types(cub->types);
	cub->types = NULL;
	if (cub->gun)
		free(cub->gun);
	cub->gun = NULL;
}
