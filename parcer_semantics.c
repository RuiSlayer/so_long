/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_semantics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:50:32 by slayer            #+#    #+#             */
/*   Updated: 2025/11/07 11:07:47 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_temp_map(t_Level *level)
{
	char	**copy;
	int		i;

	copy = malloc((level->limit->y + 2) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (level->map[i])
	{
		copy[i] = malloc((level->limit->x) * sizeof(char));
		if (!copy[i])
			return (NULL);
		ft_memcpy(copy[i], level->map[i], (level->limit->x) * sizeof(char));
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	check_walls_top_bootom(t_Level *level)
{
	int	j;

	j = 0;
	while (j <= level->limit->x)
	{
		if (level->map[0][j] != '1' || level->map[level->limit->y][j] != '1')
			return (ft_printf("Error\nThe map must be covered by walls\n"), 1);
		j++;
	}
	return (0);
}

int	is_exit_posible(int x, int y, char **temp_map, t_Level *level)
{
	if (x < 0 || x > level->limit->x || y < 0 || y > level->limit->y)
		return (1);
	if (temp_map[x][y] == '1' || temp_map[x][y] == 'V')
		return (1);
	if (temp_map[x][y] == 'E')
		return (0);
	temp_map[x][y] = 'V';

	if (is_exit_posible(x + 1, y, temp_map, level) == 0)
		return (0);
	if (is_exit_posible(x - 1, y, temp_map, level) == 0)
		return (0);
	if (is_exit_posible(x, y + 1, temp_map, level) == 0)
		return (0);
	if (is_exit_posible(x, y - 1, temp_map, level) == 0)
		return (0);
	return (1);
}

void	can_all_be_colectable(int x, int y, char **temp_map, t_Level *level, int *colectables)
{
	if (x < 0 || x >= level->limit->x || y < 0 || y >= level->limit->y)
		return ;
	if (temp_map[x][y] == '1' || temp_map[x][y] == 'V')
		return ;
	if (temp_map[x][y] == 'C')
		(*colectables)++;
	temp_map[x][y] = 'V';

	can_all_be_colectable(x + 1, y, temp_map, level, colectables);
	can_all_be_colectable(x - 1, y, temp_map, level, colectables);
	can_all_be_colectable(x, y + 1, temp_map, level, colectables);
	can_all_be_colectable(x, y - 1, temp_map, level, colectables);
}

int	check_map_semantics(t_Level *level)
{
	int		i;
	char	**temp_map;
	int		colectables;

	if (check_walls_top_bootom(level))
		return (1);
	i = 0;
	while (level->map[i])
	{
		if (level->map[i][0] != '1' || level->map[i][level->limit->x] != '1')
			return (ft_printf("Error\nThe map must be covered by walls\n"), 1);
		i++;
	}
	temp_map = copy_temp_map(level);
	if (is_exit_posible(level->player_ini_pos->x, level->player_ini_pos->y, temp_map, level))
		return (free_temp_map(temp_map), ft_printf("Error\nThe exit is unreachable\n"), 1);
	can_all_be_colectable(level->player_ini_pos->x, level->player_ini_pos->y, temp_map, level, &colectables);
	if (colectables != level->colectables)
		return (free_temp_map(temp_map), ft_printf("Error\nAt least one colectable is unreachable\n"), 1);
	return (free_temp_map(temp_map), 0);
}
