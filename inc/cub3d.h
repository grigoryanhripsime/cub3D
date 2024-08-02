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

typedef struct s_vars
{
	void		*mlx;
	void		*win;
}	t_vars;

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
} t_map;

typedef struct s_cub
{
	char **map;
} t_cub;


//utils.c
int		ft_strlen(char *s);
void	ft_lstadd_back(t_map **lst,char *new);
int	ft_lstsize(t_map *lst);

//err.c
void err(char *str);
void free_map(t_map *map);

//valid_map.c
t_map	*check_valid_map(char *map);


#endif