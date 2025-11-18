/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 22:53:34 by slayer            #+#    #+#             */
/*   Updated: 2025/11/18 18:58:08 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_aux(t_Game *game, int x, int y)
{
	mlx_clear_window(game->win_level->mlx, game->win_level->mlx_win);
	game->level->map[game->level->player_ini_pos->y]
	[game->level->player_ini_pos->x] = '0';
	game->level->map[game->level->player_ini_pos->y + y]
	[game->level->player_ini_pos->x + x] = 'P';
	game->level->player_ini_pos->x += x;
	game->level->player_ini_pos->y += y;
	game->level->move_counter++;
	ft_printf("moves: %d\n", game->level->move_counter);
}

void	move(t_Game *game, int x, int y)
{
	if (game->level->map[game->level->player_ini_pos->y + y]
		[game->level->player_ini_pos->x + x] == 'C')
	{
		game->level->colectables--;
		move_aux(game, x, y);
		if (game->level->colectables == 0)
			game->level->is_finished = 1;
		load_map_img(game->win_level, game->level);
	}
	if (game->level->map[game->level->player_ini_pos->y + y]
		[game->level->player_ini_pos->x + x] == '0')
	{
		move_aux(game, x, y);
		load_map_img(game->win_level, game->level);
	}
	if (game->level->map[game->level->player_ini_pos->y + y]
		[game->level->player_ini_pos->x + x] == 'E' && game->level->is_finished)
	{
		move_aux(game, x, y);
		load_map_img(game->win_level, game->level);
		free_win_level(game->win_level);
		free_level(game->level);
		exit(0);
	}
}
