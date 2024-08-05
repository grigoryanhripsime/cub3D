/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:32:47 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/05 19:53:08 by hrigrigo         ###   ########.fr       */
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

int	ft_lstsize(t_lst *lst)
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

void	ft_lstadd_back(t_lst **lst, char *new)
{
	t_lst	*node;
	t_lst	*tmp;

	node = malloc(sizeof(t_lst));
	if (!node)
	{
		free_map_struct(*lst);
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

int	ft_isspace(int ch)
{
	if (!ch)
		return (0);
	if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\f'
		|| ch == '\r' || ch == '\v')
		return (1);
	return (0);
}

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	if (c == '\0')
		return ((char *) s);
	return (0);
}
