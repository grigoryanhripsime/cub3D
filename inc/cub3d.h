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

typedef struct s_lst
{
	char			*line;
	struct s_lst	*next;
} t_lst;

typedef struct s_type_identifier
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char *F;
	char *C;
} t_type_identifier;

typedef struct s_cub
{
	char **map;
	t_type_identifier *types;
} t_cub;


//utils.c
int		ft_strlen(char *s);
int		ft_lstsize(t_lst *lst);
void	ft_lstadd_back(t_lst **lst,char *new);
int		ft_isspace(int ch);
char	*ft_strchr(char *s, int c);
char	*ft_strstr(char *str, char *to_find);
int		ft_strcmp(const char *s1, const char *s2);

//ft_split.c
int	ft_words_count(char *s);
char	**ft_split(char const *s);

//err.c
void	err(char *str);
void	free_map_struct(t_lst *map);
void	free_array(char **map);

//valid_map.c
char **lst_to_array(t_lst *map_stract, t_type_identifier *types);
char *replace_tab_with_spaces(char **map, int i, int j, t_cub *cub);
void	tabs_to_spaces(char **map, t_cub *cub);
void	check_borders(char **map, t_cub *cub);
t_cub	*init_cub(char *av);
void free_types(t_type_identifier *types);
void free_cub(t_cub *cub);

//struct_map_check.c
int		name_check_file(char *s);
void	check_valid_chars(t_lst *map, t_type_identifier *types);
int		there_is_valid_char(char *s);
void	remove_free_lines_start(t_lst **map);
void	remove_free_lines_end(t_lst **map, t_type_identifier *types);
t_lst	*read_map(char *av);
t_type_identifier	*type_identifiers(t_lst **map);
void init_type_identifier_struct(t_type_identifier *types);


#endif