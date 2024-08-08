/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:13:20 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/08 17:26:49 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/get_next_line.h"

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

t_cub	*init_cub(char **map, t_type *types)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
	{
		free_types(types);
		err("Malloc error\n");
	}
	cub->map = map;
	cub->types = types;
	tabs_to_spaces(cub->map, cub);
	check_borders(cub->map, cub);
	return (cub);
}

t_cub	*init_game(char *av)
{
	t_lst	*map_struct;
	t_type	*types;
	char	**map;

	map_struct = read_map(av);
	types = type_identifiers(&map_struct);
	if (!types || !types->NO || !types->WE
		|| !types->EA || !types->F || !types->C)
	{
		free_types(types);
		free_map_struct(map_struct);
		err("Invalid map(missing types)\n");
	}
	check_valid_chars(map_struct, types);
	remove_free_lines_start(&map_struct);
	remove_free_lines_end(&map_struct, types);
	if (!map_struct)
	{
		free_types(types);
		err("Invalid map!\n");
	}
	map = lst_to_array(map_struct, types);
	return (init_cub(map, types));
}

void	get_player_position(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
				|| cub->map[i][j] == 'W' || cub->map[i][j] == 'E')
			{
				cub->player.posX = i;
				cub->player.posY = j;
			}
			j++;
		}
		i++;
	}
}

int mouse_rot(int x, int y, t_cub *cub)
{
	static int	past_view;

	y = 0;
	if (x < past_view)
		rot_right(cub);
	else if (x > past_view)
		rot_left(cub);
	past_view = x;
	return (0);	
}

void	init_mlx(t_cub *cub)
{
	cub->map_wd = 1080;
	cub->map_ht = 720;
	cub->player.dirX = -1.0;
	cub->player.dirY = 0.0;
	cub->player.planeX = 0.0;
	cub->player.planeY = 0.66;
	get_player_position(cub);
	cub->fc = create_trgb(0, cub->types->F->r,
			cub->types->F->g, cub->types->F->b);
	cub->rc = create_trgb(0, cub->types->C->r,
			cub->types->C->g, cub->types->C->b);
	cub->mlx.mlx = mlx_init();
	cub->mlx.win = mlx_new_window(cub->mlx.mlx,
			cub->map_wd, cub->map_ht, "cub3D");
	//ft_redraw(cub);
	mlx_hook(cub->mlx.win, 6, 0, &mouse_rot, cub);
	mlx_hook(cub->mlx.win, 2, 0, &moveing, cub);
	mlx_loop_hook(cub->mlx.mlx, &ft_redraw, cub);
	mlx_hook(cub->mlx.win, 17, 0, ext, cub);
	mlx_loop(cub->mlx.mlx);
}
