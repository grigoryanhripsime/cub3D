/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_map_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:48:55 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/09 16:47:21 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_char(t_type *types, char c, t_lst *map, int flag)
{
	if (ft_isspace(c) || c == '1' || c == '0' || c == 'O' || c == 'C')
		return (0);
	else if ((c == 'E' || c == 'W' || c == 'N' || c == 'S') && flag == 0)
		return (1);
	else
	{
		free_types(types);
		free_map_struct(map);
		err("Invalid map(unacceptable char)!\n");
	}
	return (0);
}

void	check_valid_chars(t_lst *map, t_type *types)
{
	int		i;
	t_lst	*tmp;
	int		flag;

	tmp = map;
	flag = 0;
	while (tmp)
	{
		i = -1;
		while (tmp->line[++i])
			flag += check_char(types, tmp->line[i], map, flag);
		tmp = tmp -> next;
	}
	if (flag != 1)
	{
		free_types(types);
		free_map_struct(map);
		err("Invalid map(no player)!\n");
	}
}

int	there_is_valid_char(char *s)
{
	if (ft_strchr(s, '1') || ft_strchr(s, '0')
		|| ft_strchr(s, 'N') || ft_strchr(s, 'S')
		|| ft_strchr(s, 'W') || ft_strchr(s, 'E')
		|| ft_strchr(s, 'O') || ft_strchr(s, 'C'))
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
