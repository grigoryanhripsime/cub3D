/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:30:37 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/02 20:46:27 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char **lst_to_array(t_map *map_stract)
{
	int i;
	char **map;
	t_map *tmp;
	int len;
	
	map = malloc(sizeof(char *) * (ft_lstsize(map_stract) + 1));
	if (!map)
	{
		free_map_struct(map_stract);
		err("Malloc error!\n");
	}
	i =-1;
	len = ft_lstsize(map_stract);
	while (++i < len)
	{
		tmp = map_stract -> next;
		map[i] = map_stract->line;
		free(map_stract);
		map_stract = tmp;
	}
	map[i] = NULL;
	map_stract = NULL;
	return (map);
}

char *replace_tab_with_spaces(char **map, int i, int j)
{
	char *new_str;
	int n;

	new_str = malloc(sizeof(char) * (ft_strlen(map[i]) + 5));
	if (!new_str)
	{
		free_map(map);
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

void tabs_to_spaces(char **map)
{
	int i;
	int j;
	char *new;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '\t')
			{
				new = replace_tab_with_spaces(map, i, j);
				free(map[i]);
				map[i] = new;
			}
		}
	}
}

void check_borders(char **map)
{
	int i;
	int j;

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
				printf("char = %d, i = %d, j = %d\n",map[i][j], i, j);
				free_map(map);
				err("Invalid map(invalid borders)\n");
			}
		}
	}
}

char **init_map(char *av)
{
	char **map;
	
	map = lst_to_array(check_valid_map_struct(av));
	tabs_to_spaces(map);
	check_borders(map);
	return (map);
}
