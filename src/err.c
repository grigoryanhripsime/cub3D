/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:28:17 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/05 19:47:52 by hrigrigo         ###   ########.fr       */
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

void	err(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

void	free_types(t_type *types)
{
	if (!types)
		return ;
	if (types->NO)
		free(types->NO);
	if (types->SO)
		free(types->SO);
	if (types->WE)
		free(types->WE);
	if (types->EA)
		free(types->EA);
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
}
