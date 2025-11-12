/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:50:46 by slayer            #+#    #+#             */
/*   Updated: 2025/11/12 18:23:03 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "ft_printf/ft_printf.h"
# include "42libft/libft.h"
# include "ft_get_next_line/get_next_line.h"
# include "mlx_linux/mlx.h"

typedef struct Pos
{
	int	x;
	int	y;
}	t_Pos;

typedef struct Level
{
	char	**map;
	t_Pos	*limit;
	t_Pos	*player_ini_pos;
	t_Pos	*exit_init_pos;
	int		colectables;
	int		is_finished;
}	t_Level;

typedef struct Win_level
{
	void	*mlx;
	void	*mlx_win;
	void	*wall;
	void	*colectable;
	void	*player;
	void	*exit;
	void	*floor;
}	t_Win_level;

typedef struct Game
{
	t_Level *level;
	t_Win_level *win_level;
}	t_Game;

int		check_file_name(char const *argv);
int		check_map_syntax(t_Level *level);
int		check_map_semantics(t_Level *level);
void	free_level(t_Level *level);
void	free_level_soft(t_Level *level);
void	free_temp_map(char **temp_map, t_Level *level);
void	free_win_level(t_Win_level *win);

#endif