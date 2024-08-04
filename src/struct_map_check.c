#include "../inc/cub3d.h"
#include "../inc/get_next_line.h"

int	name_check(char *s)
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

void	check_valid_chars(t_map *map)
{
	int	i;
	t_map *tmp;

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

void remove_free_lines_start(t_map **map)
{
	t_map *tmp;

	while (*map && !there_is_valid_char((*map)->line))
	{
			tmp = (*map)->next;
			free((*map)->line);
			free(*map);
			*map = tmp;
	}
}

void remove_free_lines_end(t_map **map)
{
	t_map *tmp;

	tmp = *map;
	while (tmp->next)
	{
		if (!there_is_valid_char(tmp->next->line))
		{
			t_map *tmp2;

			tmp2 = tmp->next;
			while (tmp2)
			{
				if (there_is_valid_char(tmp2->line))
				{
					free_map_struct(*map);
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

t_map	*check_valid_map_struct(char *av)
{
	int		fd;
	char	*line;
	t_map	*map;

	map = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0 || !name_check(av))
		err("Invalid map!\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_lstadd_back(&map, line);
	}
	check_valid_chars(map);
	remove_free_lines_start(&map);
	remove_free_lines_end(&map);
	return (map);
}
