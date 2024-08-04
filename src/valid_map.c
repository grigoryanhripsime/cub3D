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
	return (map);
}

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

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '\t')
			{
				new = replace_tab_with_spaces(map, i, j);
				free(map[i]);
				map[i] = new;
			}
			j++;
		}
		i++;
	}
}

void check_borders(char **map)
{
	int i;
	int j;
	int flag;

	i = -1;
	while (map[++i])
	{
		j = -1;
		flag = 1;
		while (map[i][++j])
		{
			if (map[i][j] == '1')
				flag = 1;
			else if (map[i][j] == '0' || map[i][j] == 'N'
					|| map[i][j] == 'S' || map[i][j] == 'E'
					|| map[i][j] == 'W')
			{
				flag = 0;
				if (map[i][j - 1] && ft_isspace(map[i][j - 1]))
					break ;
			}
			else if (flag == 0)
				break ;
		}
		if (!flag)
		{
			printf("line: %s\n", map[i]);
			free_map(map);
			err("Invalid map(no closing 1 on line)\n");
		}
	}
}

char **init_map(char *av)
{
	char **map;
	
	map = lst_to_array(check_valid_map_struct(av));
	tabs_to_spaces(map);
	check_borders(map);
	// check_top_bottom(map);
	return (map);
}
