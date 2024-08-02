/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:32:47 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/02 20:37:49 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_lstsize(t_map *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst -> next;
	}
	return (count);
}

void	ft_lstadd_back(t_map **lst, char *new)
{
	t_map	*node;
	t_map	*tmp;

	node = malloc(sizeof(t_map));
	if (!node)
	{
		free_map(*lst);
		err("malloc error!\n");
	}
	node -> next = NULL;
	node -> line = new;
	if (!*lst)
		*lst = node;
	else
	{
		tmp = *lst;
		while (tmp -> next)
			tmp = tmp ->next;
		tmp->next = node;
	}
}
