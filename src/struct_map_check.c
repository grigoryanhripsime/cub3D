#include "../inc/cub3d.h"
#include "../inc/get_next_line.h"

int	name_check_file(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len < 4)
		return (0);
	if (s[len - 4] == '.' && s[len - 3] == 'c'
		&& s[len - 2] == 'u' && s[len - 1] == 'b')
		return (1);
	return (0);
}

void	check_valid_chars(t_lst *map, t_type_identifier *types)
{
	int	i;
	t_lst *tmp;

	tmp = map;
	while (tmp)
	{
		i = -1;
		while (tmp->line[++i])
		{
			if (!(ft_isspace(tmp->line[i])
				|| tmp->line[i] == '1'
				|| tmp->line[i] == '0'
				|| tmp->line[i] == 'E'
				|| tmp->line[i] == 'W'
				|| tmp->line[i] == 'N'
				|| tmp->line[i] == 'S'))
			{
				free_types(types);
				free_map_struct(map);
				err("Invalid map(unacceptable char)!\n");
			}
		}
		tmp = tmp -> next;
	}
}

int there_is_valid_char(char *s)
{
	if (ft_strchr(s, '1') || ft_strchr(s, '0')
		|| ft_strchr(s, 'N') || ft_strchr(s, 'S')
		|| ft_strchr(s, 'W') || ft_strchr(s, 'E'))
		return (1);
	return (0);
}

void remove_free_lines_start(t_lst **map)
{
	t_lst *tmp;

	if (!map)
		return ;
	while (*map && !(there_is_valid_char((*map)->line)
		|| ft_strstr((*map)->line, "NO")
		|| ft_strstr((*map)->line, "SO")
		|| ft_strstr((*map)->line, "WE")
		|| ft_strstr((*map)->line, "EA")
		|| ft_strstr((*map)->line, "F")
		|| ft_strstr((*map)->line, "C")))
	{
			tmp = (*map)->next;
			free((*map)->line);
			free(*map);
			*map = tmp;
	}
}

void remove_free_lines_end(t_lst **map, t_type_identifier *types)
{
	t_lst *tmp;
	t_lst *tmp2;

	tmp = *map;
	while (tmp->next)
	{
		if (!there_is_valid_char(tmp->next->line))
		{
			tmp2 = tmp->next;
			while (tmp2)
			{
				if (there_is_valid_char(tmp2->line))
				{
					free_map_struct(*map);
					free_types(types);
					err("Invalid map(free line in map)\n");
				}
				tmp2 = tmp2->next;
			}
			free_map_struct(tmp->next);
			tmp->next = NULL;
			break ;
		}
		tmp = tmp->next;
	}
}

t_lst *read_map(char *av)
{
	int		fd;
	char	*line;
	t_lst	*map;

	if (!name_check_file(av))
		err("Invalid map!\n");
	map = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		err("Invalid map!\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_lstadd_back(&map, line);
	}
	close(fd);
	return (map);
}

void init_type_identifier_struct(t_type_identifier *types)
{
	types->NO = NULL;
	types->SO = NULL;
	types->WE = NULL;
	types->EA = NULL;
	types->F = NULL;
	types->C = NULL;
}

int name_check_type_identifier(char *to_check, char *with, char *file)
{
	int file_len;

	if (ft_strcmp(to_check, with))
		return (0);
	file_len = ft_strlen(file);
	if (file_len < 4
		|| !(file[file_len - 4] == '.'
		&& file[file_len - 3] == 'x'
		&& file[file_len - 2] == 'p'
		&& file[file_len - 1] == 'm'))
		return (0);
	return (1);
}

void init_type_identifier(t_type_identifier *types, t_lst *map, char **line_split)
{
	printf("%s\n", line_split[0]);
	if (name_check_type_identifier(line_split[0], "NO", line_split[1]) && !types->NO)
		types->NO = line_split[1];
	else if (name_check_type_identifier(line_split[0], "SO", line_split[1]) && !types->SO)
		types->SO = line_split[1];
	else if (name_check_type_identifier(line_split[0], "WE", line_split[1]) && !types->WE)
		types->WE = line_split[1];
	else if (name_check_type_identifier(line_split[0], "EA", line_split[1]) && !types->EA)
		types->EA = line_split[1];
	else if (name_check_type_identifier(line_split[0], "F", line_split[1]) && !types->F)
		types->F = line_split[1];
	else if (name_check_type_identifier(line_split[0], "C", line_split[1]) && !types->C)
		types->C = line_split[1];
	else
	{
		free_types(types);
		free(line_split[0]);
		free(line_split);
		free_map_struct(map);
		err("Type identifier error\n");
	}
	free(line_split[0]);
	free(line_split);
}

void rem_from_map(t_lst **map)
{
	t_lst *tmp;

	tmp = (*map)->next;
	free((*map)->line);
	free((*map));
	*map = tmp;
}

void cut(t_lst **map, t_type_identifier *types)
{
	char **line_split;

	while (*map)
	{
		remove_free_lines_start(map);
		if (ft_strstr((*map)->line, "NO")
			|| ft_strstr((*map)->line, "SO")
			|| ft_strstr((*map)->line, "WE")
			|| ft_strstr((*map)->line, "EA")
			|| ft_strstr((*map)->line, "F")
			|| ft_strstr((*map)->line, "C"))
		{
			if (ft_words_count((*map)->line) != 2)
			{
				free_types(types);
				free_map_struct(*map);
				err("Type identifier error\n");
			}
			line_split = ft_split((*map)->line);
			if (!line_split)
			{
				free_types(types);
				free_map_struct(*map);
				err("Split error\n");
			}
			init_type_identifier(types, *map, line_split);
			rem_from_map(map);
		}
		else
			break ;
	}
}

t_type_identifier	*type_identifiers(t_lst **map)
{
	t_type_identifier *types;

	types = malloc(sizeof(t_type_identifier));
	if (!types)
	{
		free_map_struct(*map);
		err("Malloc error\n");
	}
	init_type_identifier_struct(types);
	cut(map, types);
	return (types);
}
