/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:13:20 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/11 20:26:20 by anrkhach         ###   ########.fr       */
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
	cub->gun = NULL;
	return (cub);
}

t_cub	*init_game(char *av)
{
	t_lst	*map_struct;
	t_type	*types;
	char	**map;

	map_struct = read_map(av);
	types = type_identifiers(&map_struct);
	if (!types || !types->north || !types->west
		|| !types->east || !types->floor_color || !types->ceiling_color)
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
	set_south_texture(cub);
	set_north_texture(cub);
	set_west_texture(cub);
	set_east_texture(cub);
	set_close_door_texture(cub);
	set_open_door_texture(cub);
	set_guns(cub);
	if (!cub->south.addr || !cub->north.addr || !cub->west.addr
		|| !cub->east.addr || !cub->od.addr || !cub->cd.addr
		|| !cub->gun[0].addr || !cub->gun[1].addr
		|| !cub->gun[2].addr || !cub->gun[3].addr
		|| !cub->gun[4].addr)
	{
		destroy_doors_and_walls(cub);
		destroy_guns(cub);
		free_cub(cub);
		err("Coudn't open texture!\n");
	}
}

void	init_mlx(t_cub *cub)
{
	cub->map_wd = 1080;
	cub->map_ht = 720;
	cub->img.ht = cub->map_ht;
	cub->img.wd = cub->map_wd;
	cub->player.dir_x = 0.0;
	cub->player.dir_y = 0.0;
	cub->player.plane_x = 0.0;
	cub->player.plane_y = 0.0;
	cub->play = false;
	get_player_position(cub);
	cub->fc = create_trgb(0, cub->types->floor_color->r,
			cub->types->floor_color->g, cub->types->floor_color->b);
	cub->rc = create_trgb(0, cub->types->ceiling_color->r,
			cub->types->ceiling_color->g, cub->types->ceiling_color->b);
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
