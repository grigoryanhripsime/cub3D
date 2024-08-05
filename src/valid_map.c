/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:30:37 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/05 20:50:37 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	**lst_to_array(t_lst *map_stract, t_type *types)
{
	int		i;
	char	**map;
	t_lst	*tmp;
	int		len;

	map = malloc(sizeof(char *) * (ft_lstsize(map_stract) + 1));
	if (!map)
	{
		free_map_struct(map_stract);
		free_types(types);
		err("Malloc error!\n");
	}
	i = -1;
	len = ft_lstsize(map_stract);
	while (++i < len)
	{
		tmp = map_stract -> next;
		map[i] = map_stract->line;
		free(map_stract);
		map_stract = tmp;
	}
	map[i] = NULL;
	return (map);
}

char	*replace_tab_with_spaces(char **map, int i, int j, t_cub *cub)
{
	char	*new_str;
	int		n;

	new_str = malloc(sizeof(char) * (ft_strlen(map[i]) + 5));
	if (!new_str)
	{
		free_cub(cub);
		err("Malloc error\n");
	}
	n = -1;
	while (++n < j)
		new_str[n] = map[i][n];
	new_str[n++] = ' ';
	new_str[n++] = ' ';
	new_str[n++] = ' ';
	new_str[n] = ' ';
	while (map[i][++j])
		new_str[++n] = map[i][j];
	new_str[++n] = '\0';
	return (new_str);
}

void	tabs_to_spaces(char **map, t_cub *cub)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '\t')
			{
				new = replace_tab_with_spaces(map, i, j, cub);
				free(map[i]);
				map[i] = new;
			}
		}
	}
}

void	check_borders(char **map, t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if ((map[i][j] == '0' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				&& (ft_isspace(map[i - 1][j])
				|| ft_isspace(map[i][j - 1])
				|| ft_isspace(map[i + 1][j])
				|| ft_isspace(map[i][j + 1])))
			{
				free_cub(cub);
				err("Invalid map(invalid borders)\n");
			}
		}
	}
}

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

