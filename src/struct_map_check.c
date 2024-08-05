/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_map_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:48:55 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/05 20:16:04 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/get_next_line.h"

void	check_valid_chars(t_lst *map, t_type *types)
{
	int		i;
	t_lst	*tmp;

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

int	there_is_valid_char(char *s)
{
	if (ft_strchr(s, '1') || ft_strchr(s, '0')
		|| ft_strchr(s, 'N') || ft_strchr(s, 'S')
		|| ft_strchr(s, 'W') || ft_strchr(s, 'E'))
		return (1);
	return (0);
}

void	remove_free_lines_start(t_lst **map)
{
	t_lst	*tmp;

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

void	remove_free_lines_end(t_lst **map, t_type *types)
{
	t_lst	*tmp;
	t_lst	*tmp2;

	tmp = *map;
	while (tmp && tmp->next)
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

t_lst	*read_map(char *av)
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
	if (!map)
		err("Invalid map\n");
	return (map);
}
