/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_identifier2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:55:26 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/06 19:18:58 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_color	*type_set_color(char *str)
{
	t_color	*rgb;
	char	**split;

	rgb = malloc(sizeof(t_color));
	if (!rgb)
		return (0);
	split = ft_split_color(str, ',');
	if (!split)
	{
		free(rgb);
		return (0);
	}
	rgb->r = ft_atoi(split[0]);
	rgb->g = ft_atoi(split[1]);
	rgb->b = ft_atoi(split[2]);
	free_array(split);
	free(str);
	if (rgb->r < 0 || rgb->g < 0 || rgb->b < 0)
	{
		free(rgb);
		return (0);
	}
	return (rgb);
}

void	type_error(t_type *types, char **split, t_lst *map)
{
	free_types(types);
	free(split[0]);
	free(split);
	free_map_struct(map);
	err("Type identifier error\n");
}
