/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pointers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:24:28 by slayer            #+#    #+#             */
/*   Updated: 2025/11/12 18:39:59 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdlib.h>

void	free_level(t_Level *level)
{
	int	i;

	if (level == NULL)
		return ;
	if (level->map != NULL)
	{
		i = 0;
		while (level->map[i] != NULL)
		{
			free(level->map[i]);
			i++;
		}
		free(level->map);
	}
	free_level_soft(level);
}

void	free_level_soft(t_Level *level)
{
	free(level->limit);
	free(level->player_ini_pos);
	free(level->exit_init_pos);
	free(level);
}

void	free_temp_map(char **temp_map, t_Level *level)
{
	int	i;

	i = 0;
	while (i < level->limit->y)
	{
		free(temp_map[i]);
		i++;
	}
	free(temp_map[i]);
	free(temp_map);
}

void free_win_level(t_Win_level *win)
{
	if (win->mlx_win)
		mlx_destroy_window(win->mlx, win->mlx_win);
	if (win->wall)
		mlx_destroy_image(win->mlx, win->wall);
	if (win->colectable)
		mlx_destroy_image(win->mlx, win->colectable);
	if (win->player)
		mlx_destroy_image(win->mlx, win->player);
	if (win->exit)
		mlx_destroy_image(win->mlx, win->exit);
	if (win->floor)
		mlx_destroy_image(win->mlx, win->floor);
	if (win->mlx)
		mlx_destroy_display(win->mlx);
	free(win->mlx);
}
