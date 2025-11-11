/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pointers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:24:28 by slayer            #+#    #+#             */
/*   Updated: 2025/11/10 00:04:20 by slayer           ###   ########.fr       */
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
