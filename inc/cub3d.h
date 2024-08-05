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

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
} t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_cub
{
	int				fc;
	int				rc;
	int				map_wd;
	int				map_ht;
	int				hide_map;
	char			*npath;
	char			*spath;
	char			*wpath;
	char			*epath;
	char			**char_map;
	char			*fcolor;
	char			*rcolor;
	t_mlx			mlx;
	t_player		player;
	t_img			img;
	t_img			cdoor;
	t_img			odoor;
	t_rt			ray;
	t_color			f_color;
	t_color			r_color;
	t_map			*map;
	t_img			*gun;
	t_img			*wall;
}	t_cub;


//utils.c
int		ft_strlen(char *s);
int		ft_lstsize(t_map *lst);
void	ft_lstadd_back(t_map **lst,char *new);
int		ft_isspace(int ch);
char	*ft_strchr(char *s, int c);

//err.c
void	err(char *str);
void	free_map_struct(t_map *map);
void	free_map(char **map);

//valid_map.c
char	**lst_to_array(t_map *map_stract);
char	*replace_tab_with_spaces(char **map, int i, int j);
void	tabs_to_spaces(char **map);
void	check_borders(char **map);
char	**init_map(char *av);

//struct_map_check.c
int		name_check(char *s);
void	check_valid_chars(t_map *map);
int		there_is_valid_char(char *s);
void	remove_free_lines_start(t_map **map);
void	remove_free_lines_end(t_map **map);
t_map	*check_valid_map_struct(char *map);



#endif