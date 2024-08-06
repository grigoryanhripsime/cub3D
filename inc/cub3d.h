/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrkhach <anrkhach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:01:33 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/06 16:10:20 by anrkhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include "../mlx/mlx.h"

# define AROTATE 0.07
# define MROTATE 0.03
# define WSPEED 0.15
# define SSPEED 0.1
# define ADSPEED 0.12

# define MAP_WIDTH 36
# define MAP_HEIGHT 11
# define TILE_SIZE 10

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	int		stepX;
	int		stepY;
	int		mapX;
	int		mapY;
}	t_player;

typedef struct s_rt
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	mapX;
	double	mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltadistX;
	double	deltadistY;
	double	wallDist;
	int		hit;
	int		side;

}	t_rt;

typedef struct s_img
{
	int		wd;
	int		ht;
	int		endian;
	int		line_length;
	int		bits_per_pixel;
	char	*addr;
	void	*img;
}	t_img;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_lst
{
	char			*line;
	struct s_lst	*next;
}	t_lst;

typedef struct s_type_identifier
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
}	t_type;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_textre
{
	int		tex_x;
	int		tex_y;
	int		draw_end;
	int		draw_start;
	int		line_height;
	double	step;
	double	tex_pos;
}	t_texture;

typedef struct s_cub
{
	char	**map;
	t_type	*types;
	int		fc;
	int		rc;
	int		map_wd;
	int		map_ht;
	int		hide_map;
	char	*npath;
	char	*spath;
	char	*wpath;
	char	*epath;
	char	*fcolor;
	char	*rcolor;
	t_mlx	mlx;
	t_player	player;
	t_img		img;
	t_img		cdoor;
	t_img		odoor;
	t_rt		ray;
	t_color		f_color;
	t_color		r_color;
	t_lst		*lst_map;
	t_img		*gun;
	t_img		*wall;
} t_cub;


//utils.c
int		ft_strlen(char *s);
int		ft_lstsize(t_lst *lst);
void	ft_lstadd_back(t_lst **lst, char *new);
int		ft_isspace(int ch);
char	*ft_strchr(char *s, int c);

//utils2.c
char	*ft_strstr(char *str, char *to_find);
int		ft_strcmp(const char *s1, const char *s2);

//ft_split.c
int		ft_words_count(char *s);
char	**ft_split(char const *s);
int		name_check_file(char *s);

//err.c
void	err(char *str);
void	free_map_struct(t_lst *map);
void	free_array(char **map);
void	free_types(t_type *types);
void	free_cub(t_cub *cub);

//valid_map.c
char	**lst_to_array(t_lst *map_stract, t_type *types);
char	*replace_tab_with_spaces(char **map, int i, int j, t_cub *cub);
void	tabs_to_spaces(char **map, t_cub *cub);
void	check_borders(char **map, t_cub *cub);
t_cub	*init_cub(char **map, t_type *types);
t_cub	*init_game(char *av);

//struct_map_check.c
void	check_valid_chars(t_lst *map, t_type *types);
int		there_is_valid_char(char *s);
void	remove_free_lines_start(t_lst **map);
void	remove_free_lines_end(t_lst **map, t_type *types);
t_lst	*read_map(char *av);

//type_identifier.c
void	init_type_struct(t_type *types);
int		type_name(char *to_check, char *with, char *file);
void	init_type(t_type *types, t_lst *map, char **split);
void	check_identifier(t_lst **map, t_type *types);
t_type	*type_identifiers(t_lst **map);

#endif