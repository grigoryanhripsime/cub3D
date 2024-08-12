/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_identifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:53:47 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/12 18:02:10 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_type_struct(t_type *types)
{
	types->north = NULL;
	types->south = NULL;
	types->west = NULL;
	types->east = NULL;
	types->floor_color = NULL;
	types->ceiling_color = NULL;
}

int	type_name(char *to_check, char *with, char *file)
{
	int	file_len;

	if (ft_strcmp(to_check, with))
		return (0);
	if (!ft_strcmp(with, "F") || !ft_strcmp(with, "C"))
	{
		if (ft_words_count_color(file, ',') != 3 || ft_strstr(file, ",,"))
			return (0);
		return (1);
	}
	file_len = ft_strlen(file);
	if (file_len < 4
		|| !(file[file_len - 4] == '.'
			&& file[file_len - 3] == 'x'
			&& file[file_len - 2] == 'p'
			&& file[file_len - 1] == 'm'))
		return (0);
	return (1);
}

void	init_type(t_type *types, t_lst *map, char **split)
{
	if (type_name(split[0], "NO", split[1]) && !types->north)
		types->north = split[1];
	else if (type_name(split[0], "SO", split[1]) && !types->south)
		types->south = split[1];
	else if (type_name(split[0], "WE", split[1]) && !types->west)
		types->west = split[1];
	else if (type_name(split[0], "EA", split[1]) && !types->east)
		types->east = split[1];
	else if (type_name(split[0], "F", split[1]) && !types->floor_color)
	{
		types->floor_color = type_set_color(split[1]);
		if (!types->floor_color)
			type_error(types, split, map);
	}
	else if (type_name(split[0], "C", split[1]) && !types->ceiling_color)
	{
		types->ceiling_color = type_set_color(split[1]);
		if (!types->ceiling_color)
			type_error(types, split, map);
	}
	else
		type_error(types, split, map);
	free(split[0]);
	free(split);
}

void	check_identifier(t_lst **map, t_type *types)
{
	char	**split;
	t_lst	*tmp;

	if (ft_words_count((*map)->line) != 2)
	{
		free_types(types);
		free_map_struct(*map);
		err("Type identifier error\n");
	}
	split = ft_split((*map)->line);
	if (!split)
	{
		free_types(types);
		free_map_struct(*map);
		err("Split error\n");
	}
	init_type(types, *map, split);
	tmp = (*map)->next;
	free((*map)->line);
	free((*map));
	*map = tmp;
}

t_type	*type_identifiers(t_lst **map)
{
	t_type	*types;

	types = malloc(sizeof(t_type));
	if (!types)
	{
		free_map_struct(*map);
		err("Malloc error\n");
	}
	init_type_struct(types);
	while (map && *map)
	{
		remove_free_lines_start(map);
		if (map && *map && (ft_strstr((*map)->line, "NO")
				|| ft_strstr((*map)->line, "SO")
				|| ft_strstr((*map)->line, "WE")
				|| ft_strstr((*map)->line, "EA")
				|| ft_strstr((*map)->line, "F")
				|| ft_strstr((*map)->line, "C")))
			check_identifier(map, types);
		else
			break ;
	}
	return (types);
}
