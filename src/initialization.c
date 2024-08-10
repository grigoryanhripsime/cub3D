/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:13:20 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/10 15:43:53 by anrkhach         ###   ########.fr       */
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

void set_direction(t_cub *cub, char c)
{
	if (c == 'N')
	{
		cub->player.planeY = 0.66;
		cub->player.dirX = -1.0;
	}
	else if (c == 'S')
	{
		cub->player.planeY = -0.66;
		cub->player.dirX = 1.0;
	}
	else if (c == 'W')
	{
		cub->player.planeX = -0.66;
		cub->player.dirY = -1.0;
	}
	else if (c == 'E')
	{
		cub->player.planeX = 0.66;
		cub->player.dirY = 1.0;
	}
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
				set_direction(cub, cub->map[i][j]);
				cub->player.posX = i + 0.5;
				cub->player.posY = j + 0.5;
				cub->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void init_textutes(t_cub *cub)
{
	int	height;
	int	width;
	
	height = 100;
	width = 100;
	
	cub->SO.img = mlx_xpm_file_to_image(cub->mlx.mlx, cub->types->SO, &width, &height);
	if (!cub->SO.img)
	{
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Coudn't open wall textures\n");
	}
	cub->SO.wd = width;
	cub->SO.ht = height;
	cub->SO.addr = mlx_get_data_addr(cub->SO.img, &cub->SO.bits_per_pixel, &cub->SO.line_length, &cub->SO.endian);
	
	cub->NO.img = mlx_xpm_file_to_image(cub->mlx.mlx, cub->types->NO, &width, &height);
	if (!cub->NO.img)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Coudn't open wall textures\n");
	}
	cub->NO.wd = width;
	cub->NO.ht = height;
	cub->NO.addr = mlx_get_data_addr(cub->NO.img, &cub->NO.bits_per_pixel, &cub->NO.line_length, &cub->NO.endian);
	
	cub->WE.img = mlx_xpm_file_to_image(cub->mlx.mlx, cub->types->WE, &width, &height);
	if (!cub->WE.img)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->NO.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Coudn't open wall textures\n");
	}
	cub->WE.wd = width;
	cub->WE.ht = height;
	cub->WE.addr = mlx_get_data_addr(cub->WE.img, &cub->WE.bits_per_pixel, &cub->WE.line_length, &cub->WE.endian);
	
	cub->EA.img = mlx_xpm_file_to_image(cub->mlx.mlx, cub->types->EA, &width, &height);
	if (!cub->EA.img)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->WE.img);
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->NO.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Coudn't open wall textures\n");
	}
	cub->EA.wd = width;
	cub->EA.ht = height;
	cub->EA.addr = mlx_get_data_addr(cub->EA.img, &cub->EA.bits_per_pixel, &cub->EA.line_length, &cub->EA.endian);
	
	cub->closeD.img = mlx_xpm_file_to_image(cub->mlx.mlx, "textures/CloseDoor.xpm", &width, &height);
	if (!cub->closeD.img)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->WE.img);
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->NO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->EA.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Coudn't open door textures\n");
	}
	cub->closeD.wd = width;
	cub->closeD.ht = height;
	cub->closeD.addr = mlx_get_data_addr(cub->closeD.img, &cub->closeD.bits_per_pixel, &cub->closeD.line_length, &cub->closeD.endian);

	cub->openD.img = mlx_xpm_file_to_image(cub->mlx.mlx, "textures/OpenDoor.xpm", &width, &height);
	if (!cub->openD.img)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->WE.img);
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->NO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->EA.img);
		mlx_destroy_image(cub->mlx.mlx, cub->closeD.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Coudn't open door textures\n");
	}
	cub->openD.wd = width;
	cub->openD.ht = height;
	cub->openD.addr = mlx_get_data_addr(cub->openD.img, &cub->openD.bits_per_pixel, &cub->openD.line_length, &cub->openD.endian);



	cub->gun.img = mlx_xpm_file_to_image(cub->mlx.mlx, "textures/00_frame.xpm", &width, &height);
	if (!cub->gun.img)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->WE.img);
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->NO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->EA.img);
		mlx_destroy_image(cub->mlx.mlx, cub->openD.img);
		mlx_destroy_image(cub->mlx.mlx, cub->closeD.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Pistol texture error\n");
	}
	cub->gun.wd = width;
	cub->gun.ht = height;
	cub->gun.addr = mlx_get_data_addr(cub->gun.img, &cub->gun.bits_per_pixel, &cub->gun.line_length, &cub->gun.endian);

	cub->gun_anim.img = mlx_xpm_file_to_image(cub->mlx.mlx, "textures/01_frame.xpm", &width, &height);
	if (!cub->gun_anim.img)
	{
		mlx_destroy_image(cub->mlx.mlx, cub->WE.img);
		mlx_destroy_image(cub->mlx.mlx, cub->SO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->NO.img);
		mlx_destroy_image(cub->mlx.mlx, cub->EA.img);
		mlx_destroy_image(cub->mlx.mlx, cub->openD.img);
		mlx_destroy_image(cub->mlx.mlx, cub->closeD.img);
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
		free_cub(cub);
		err("Pistol texture error\n");
	}
	cub->gun_anim.wd = width;
	cub->gun_anim.ht = height;
	cub->gun_anim.addr = mlx_get_data_addr(cub->gun_anim.img, &cub->gun_anim.bits_per_pixel, &cub->gun_anim.line_length, &cub->gun_anim.endian);
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
