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

void	check_borders(t_map *map)
{
	int	i;
	int	flag;

	while (map)
	{
		i = -1;
		flag = 0;
		while (map->line[++i])
		{
			if (map->line[i] == '1')
				flag = 1;
			else if (map->line[i] == '0' || map->line[i] == 'N'
				|| map->line[i] == 'S' || map->line[i] == 'E'
				|| map->line[i] == 'W')
				flag = 0;
			else if (flag == 0)
				break ;
		}
		if (flag == 0)
		{
			free_map(map);
			err("Invalid map(borders)!\n");
		}
		map = map -> next;
	}
}

t_map	*check_valid_map(char *av)
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
	check_borders(map);
	return (map);
}

char **init_map(char **av)
{
	char **map;
	
	map = lst_to_array(check_valid_map(av));
	
}
