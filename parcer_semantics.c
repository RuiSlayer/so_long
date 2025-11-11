/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_semantics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:50:32 by slayer            #+#    #+#             */
/*   Updated: 2025/11/11 02:06:39 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**map_dup(char **map, int size)
{
	char	**copy;
	int		i;

	copy = (char **)malloc(sizeof(char *) * size);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (map[i])
		{
			copy[i] = (char *)malloc(sizeof(char) * strlen(map[i]));
			if (!copy[i])
			{
				while (i > 0)
				{
					free(copy[i - 1]);
					i--;
				}
				free(copy);
				return (NULL);
			}
			ft_strlcpy(copy[i], map[i], strlen(map[i]));
		}
		else
			copy[i] = NULL;
		i++;
	}
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
	if (temp_map[y][x] == '1' || temp_map[y][x] == 'V')
		return (1);
	if (temp_map[y][x] == 'E')
		return (0);
	temp_map[y][x] = 'V';

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
	if (temp_map[y][x] == '1' || temp_map[y][x] == 'V' || temp_map[y][x] == 'E')
		return ;
	if (temp_map[y][x] == 'C')
		(*colectables)++;
	temp_map[y][x] = 'V';

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
	temp_map = map_dup(level->map, level->limit->y + 1);
	if (is_exit_posible(level->player_ini_pos->x, level->player_ini_pos->y, temp_map, level))
		return (free_temp_map(temp_map, level), ft_printf("Error\nThe exit is unreachable\n"), 1);
	free_temp_map(temp_map, level);
	colectables = 0;
	temp_map = map_dup(level->map, level->limit->y + 1);
	can_all_be_colectable(level->player_ini_pos->x, level->player_ini_pos->y, temp_map, level, &colectables);
	if (colectables != level->colectables)
		return (free_temp_map(temp_map, level), ft_printf("Error\nAt least one colectable is unreachable\n"), 1);
	return (free_temp_map(temp_map, level), 0);
}
