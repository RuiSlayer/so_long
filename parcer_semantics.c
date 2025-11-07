/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_semantics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:50:32 by slayer            #+#    #+#             */
/*   Updated: 2025/11/07 00:49:21 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	is_exit_posible(t_Pos *last_pos, int x, int y, t_Level *level)
{
	char	this_pos_content;
	t_Pos	*this_pos;

	this_pos->x = last_pos->x + x;
	this_pos->y = last_pos->y + y;
	this_pos_content = level->map[this_pos->x][this_pos->y];

	if (this_pos_content == '1')
		return (is_exit_posible(last_pos, x, y, level));
	if (this_pos_content == 'E')
		return (1);
	return (is_exit_posible(this_pos, x, y, level));
}

int	check_map_semantics(t_Level *level)
{
	int		i;

	i = 0;
	if (check_walls_top_bootom(level))
		return (1);
	while (level->map[i])
	{
		if (level->map[i][0] != '1' || level->map[i][level->limit->x] != '1')
			return (ft_printf("Error\nThe map must be covered by walls\n"), 1);
		i++;
	}
	return (0);
}
