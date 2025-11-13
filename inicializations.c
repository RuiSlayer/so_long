/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 22:51:52 by slayer            #+#    #+#             */
/*   Updated: 2025/11/13 00:50:23 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_Level	*level_init(void)
{
	t_Level	*level;

	level = malloc(sizeof(t_Level));
	level->limit = malloc(sizeof(t_Pos));
	level->player_ini_pos = malloc(sizeof(t_Pos));
	level->exit_init_pos = malloc(sizeof(t_Pos));
	if (!level->limit || !level->player_ini_pos || !level->exit_init_pos)
	{
		free(level->limit);
		free(level->player_ini_pos);
		free(level->exit_init_pos);
		free(level);
		return (NULL);
	}
	level->limit->x = -1;
	level->limit->y = -1;
	level->colectables = 0;
	level->is_finished = 0;
	level->move_counter = 0;
	level->exit_init_pos->x = -1;
	level->exit_init_pos->y = -1;
	level->player_ini_pos->x = -1;
	level->player_ini_pos->y = -1;
	return (level);
}

int	img_create(t_Win_level *Win_level)
{
	int		img_width;
	int		img_height;

	Win_level->wall = mlx_xpm_file_to_image(Win_level->mlx,
			"./textures/wall.xpm", &img_width, &img_height);
	Win_level->colectable = mlx_xpm_file_to_image(Win_level->mlx,
			"./textures/c7.xpm", &img_width, &img_height);
	Win_level->player = mlx_xpm_file_to_image(Win_level->mlx,
			"./textures/sonic.xpm", &img_width, &img_height);
	Win_level->exit = mlx_xpm_file_to_image(Win_level->mlx,
			"./textures/egg.xpm", &img_width, &img_height);
	Win_level->floor = mlx_xpm_file_to_image(Win_level->mlx,
			"./textures/floor.xpm", &img_width, &img_height);
	return (0);
}

void	load_map_img_aux(t_Win_level *Win_level, t_Level *level, int i, int j)
{
	if (level->map[i][j] == '1')
		mlx_put_image_to_window (Win_level->mlx, Win_level->mlx_win,
			Win_level->wall, j * 64, i * 64);
	if (level->map[i][j] == '0')
		mlx_put_image_to_window (Win_level->mlx, Win_level->mlx_win,
			Win_level->floor, j * 64, i * 64);
	if (level->map[i][j] == 'P')
		mlx_put_image_to_window (Win_level->mlx, Win_level->mlx_win,
			Win_level->player, j * 64, i * 64);
	if (level->map[i][j] == 'C')
		mlx_put_image_to_window (Win_level->mlx, Win_level->mlx_win,
			Win_level->colectable, j * 64, i * 64);
	if (level->map[i][j] == 'E')
		mlx_put_image_to_window (Win_level->mlx, Win_level->mlx_win,
			Win_level->exit, j * 64, i * 64);
}

void	load_map_img(t_Win_level *Win_level, t_Level *level)
{
	int	i;
	int	j;

	i = 0;
	while (i <= level->limit->y)
	{
		j = 0;
		while (j <= level->limit->x)
		{
			load_map_img_aux(Win_level, level, i, j);
			j++;
		}
		i++;
	}
}
