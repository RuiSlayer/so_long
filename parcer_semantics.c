/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_semantics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:50:32 by slayer            #+#    #+#             */
/*   Updated: 2025/11/06 19:45:17 by slayer           ###   ########.fr       */
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

int	check_map_semantics(t_Level *level)
{
	int		i;
	int		j;

	i = 0;
	if (check_walls_top_bootom(level))
		return (1);
	while (level->map[i])
	{
		if (level->map[i][0] != '1' || level->map[i][level->limit->x] != '1')
			return (ft_printf("Error\nThe map must be covered by walls\n"), 1);
		j = 0;
		while (level->map[i][j])
		{
			j++;
		}
		i++;
	}
	return (0);
}
