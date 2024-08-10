/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:13:20 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/10 16:52:06 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	check_doors(cub->map, cub);
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

void	init_textutes(t_cub *cub)
{
	set_SO_texture(cub);
	set_NO_texture(cub);
	set_WE_texture(cub);
	set_EA_texture(cub);
	set_close_door_texture(cub);
	set_open_door_texture(cub);
	set_gun1(cub);
	set_gun2(cub);
}

void	init_mlx(t_cub *cub)
{
	cub->map_wd = 1080;
	cub->map_ht = 720;
	cub->img.ht = cub->map_ht;
	cub->img.wd = cub->map_wd;
	cub->player.dirX = 0.0;
	cub->player.dirY = 0.0;
	cub->player.planeX = 0.0;
	cub->player.planeY = 0.0;
	get_player_position(cub);
	cub->fc = create_trgb(0, cub->types->F->r,
			cub->types->F->g, cub->types->F->b);
	cub->rc = create_trgb(0, cub->types->C->r,
			cub->types->C->g, cub->types->C->b);
	cub->mlx.mlx = mlx_init();
	cub->mlx.win = mlx_new_window(cub->mlx.mlx,
			cub->map_wd, cub->map_ht, "cub3D");
	init_textutes(cub);
	mlx_hook(cub->mlx.win, 6, 0, &mouse_rot, cub);
	mlx_hook(cub->mlx.win, 2, 0, &moveing, cub);
	mlx_loop_hook(cub->mlx.mlx, &ft_redraw, cub);
	mlx_hook(cub->mlx.win, 17, 0, ext, cub);
	mlx_loop(cub->mlx.mlx);
}
