/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_identifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:53:47 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/05 20:29:35 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_type_struct(t_type *types)
{
	types->NO = NULL;
	types->SO = NULL;
	types->WE = NULL;
	types->EA = NULL;
	types->F = NULL;
	types->C = NULL;
}

int	type_name(char *to_check, char *with, char *file)
{
	int	file_len;

	if (ft_strcmp(to_check, with))
		return (0);
	if (!ft_strcmp(with, "F") || !ft_strcmp(with, "C"))
		return (1);
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
	printf("%s\n", split[0]);
	if (type_name(split[0], "NO", split[1]) && !types->NO)
		types->NO = split[1];
	else if (type_name(split[0], "SO", split[1]) && !types->SO)
		types->SO = split[1];
	else if (type_name(split[0], "WE", split[1]) && !types->WE)
		types->WE = split[1];
	else if (type_name(split[0], "EA", split[1]) && !types->EA)
		types->EA = split[1];
	else if (type_name(split[0], "F", split[1]) && !types->F)
		types->F = split[1];
	else if (type_name(split[0], "C", split[1]) && !types->C)
		types->C = split[1];
	else
	{
		free_types(types);
		free(split[0]);
		free(split);
		free_map_struct(map);
		err("Type identifier error\n");
	}
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
