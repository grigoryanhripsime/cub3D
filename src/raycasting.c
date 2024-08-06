#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	calc_draw_ends(t_cub *vars, t_texture *tex)
{
	tex->line_height = (int)(vars->map_ht / vars->ray.wallDist);
	tex->draw_start = -tex->line_height / 2 + vars->map_ht / 2;
	if (tex->draw_start < 0)
		tex->draw_start = 0;
	tex->draw_end = tex->line_height / 2 + vars->map_ht / 2;
	if (tex->draw_end >= vars->map_ht)
		tex->draw_end = vars->map_ht - 1;
	tex->step = 1.0 * 64 / tex->line_height;
	tex->tex_pos = (tex->draw_start - vars->map_ht / 2 + tex->line_height / 2)
		* tex->step;
}

void	draw_texture(t_cub *vars, int x, int tex_x)
{
	t_texture			tex;
	int				y;

	tex_x = 0;
	if (vars->ray.wallDist < 0.000001)
		vars->ray.wallDist = 0.000001;
	calc_draw_ends(vars, &tex);
	y = tex.draw_start - 1;
	while (++y < tex.draw_end)
	{
		tex.tex_y = (int)tex.tex_pos & (63);
		tex.tex_pos += tex.step;
		my_mlx_pixel_put(&vars->img, x, y, 0xFFFFFF);
	}
}

void	ray_pos(t_cub *vars, int w)
{
	vars->ray.cameraX = 2.0 * w / (double)vars->map_wd - 1.0;
	vars->ray.rayDirX = vars->player.dirX
		+ vars->player.planeX * vars->ray.cameraX;
	vars->ray.rayDirY = vars->player.dirY
		+ vars->player.planeY * vars->ray.cameraX;
	vars->player.mapX = (int)vars->player.posX;
	vars->player.mapY = (int)vars->player.posY;
	if (vars->ray.rayDirX == 0)
		vars->ray.deltadistX = 1e30;
	else
		vars->ray.deltadistX = fabs(1 / vars->ray.rayDirX);
	if (vars->ray.rayDirY == 0)
		vars->ray.deltadistY = 1e30;
	else
		vars->ray.deltadistY = fabs(1 / vars->ray.rayDirY);
}

void	step_dir(t_cub *vars)
{
	if (vars->ray.rayDirX < 0)
	{
		vars->player.stepX = -1;
		vars->ray.sideDistX = (vars->player.posX - vars->player.mapX)
			* vars->ray.deltadistX;
	}
	else
	{
		vars->player.stepX = 1;
		vars->ray.sideDistX = (vars->player.mapX + 1.0 - vars->player.posX)
			* vars->ray.deltadistX;
	}
	if (vars->ray.rayDirY < 0)
	{
		vars->player.stepY = -1;
		vars->ray.sideDistY = (vars->player.posY - vars->player.mapY)
			* vars->ray.deltadistY;
	}
	else
	{
		vars->player.stepY = 1;
		vars->ray.sideDistY = (vars->player.mapY + 1.0 - vars->player.posY)
			* vars->ray.deltadistY;
	}
}

void	dda_algorithm(t_cub *vars)
{
	while (vars->ray.hit == 0)
	{
		if (vars->ray.sideDistX < vars->ray.sideDistY)
		{
			vars->ray.sideDistX += vars->ray.deltadistX;
			vars->player.mapX += vars->player.stepX;
			vars->ray.side = 0;
		}
		else
		{
			vars->ray.sideDistY += vars->ray.deltadistY;
			vars->player.mapY += vars->player.stepY;
			vars->ray.side = 1;
		}
		if (vars->map[vars->player.mapX][vars->player.mapY] == '1')
			vars->ray.hit = 1;
		else if (vars->map[vars->player.mapX][vars->player.mapY] == 'D')
			vars->ray.hit = 2;
		else if (vars->map[vars->player.mapX][vars->player.mapY] == 'O')
			vars->ray.hit = 3;
	}
	if (vars->ray.side == 0)
		vars->ray.wallDist = (vars->ray.sideDistX - vars->ray.deltadistX);
	else
		vars->ray.wallDist = (vars->ray.sideDistY - vars->ray.deltadistY);
}

void	raycasting(t_cub *vars)
{
	int		i;

	//draw_floor(vars);
	i = -1;
	while (++i <= vars->map_wd)
	{
		ray_pos(vars, i);
		step_dir(vars);
		vars->ray.hit = 0;
		dda_algorithm(vars);
	}
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win, vars->img.img, 0, 0);
}