#include "../inc/cub3d.h"

int	ext(void *params)
{
	t_vars		*vars;
	int			i;

	vars = params;
	mlx_destroy_window(vars->mlx, vars->win);
	//free_map(&vars);
	exit(0);
	return (0);
}

void open_window(t_vars **vars)
{
	(*vars)->mlx = mlx_init();
	(*vars)->win = mlx_new_window((*vars)->mlx,
			1920, 1280, "cub3D");
	mlx_hook((*vars)->win, 17, 0, ext, *vars);
	mlx_loop((*vars)->mlx);
}

int main(int ac, char **av)
{
	t_vars		*vars;

	(void)av;
	ac = 1;
	vars = (t_vars *)malloc(sizeof(t_vars));
	open_window(&vars);
}

