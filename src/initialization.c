/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:13:20 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/06 16:13:53 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_cub	*init_cub(char **map, t_type *types)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
	{
		free_types(types);
		err("Malloc error\n");
	}
	cub->map = map;
	cub->types = types;
	tabs_to_spaces(cub->map, cub);
	check_borders(cub->map, cub);
	return (cub);
}

t_cub	*init_game(char *av)
{
	t_lst	*map_struct;
	t_type	*types;
	char	**map;

	map_struct = read_map(av);
	types = type_identifiers(&map_struct);
	check_valid_chars(map_struct, types);
	remove_free_lines_start(&map_struct);
	remove_free_lines_end(&map_struct, types);
	if (!map_struct)
	{
		free_types(types);
		err("Invalid map!\n");
	}
	map = lst_to_array(map_struct, types);
	return (init_cub(map, types));
}
