/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:50:32 by slayer            #+#    #+#             */
/*   Updated: 2025/11/06 18:24:57 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_file_name(char const *argv)
{
	int		i;
	int		j;
	char	*extencion;

	i = ft_strlen(argv) - 1;
	j = 3;
	extencion = ".ber";
	while (j >= 0)
	{
		if (argv[i] != extencion[j])
			return (1);
		i--;
		j--;
	}
	return (0);
}

char	caracter_test(int i, int j, t_Level *level)
{
	if (level->map[i][j] == '0' || level->map[i][j] == '1')
		return (level->map[i][j]);
	if (level->map[i][j] == 'E' && level->exit_init_pos->x == -1)
	{
		level->exit_init_pos->y = i;
		level->exit_init_pos->x = j;
		return (level->map[i][j]);
	}
	if (level->map[i][j] == 'E' && level->exit_init_pos->x != -1)
		return (perror("Error\nThe map must have only one exit\n"), 'N');
	if (level->map[i][j] == 'P' && level->player_ini_pos->x == -1)
	{
		level->player_ini_pos->y = i;
		level->player_ini_pos->x = j;
		return (level->map[i][j]);
	}
	if (level->map[i][j] == 'P' && level->player_ini_pos->x != -1)
		return (perror("Error\nthe map must have only one player\n"), 'N');
	if (level->map[i][j] == 'C')
	{
		level->has_colectable = 1;
		return (level->map[i][j]);
	}
	return (perror("Error\nInvalid Caracter in map\n"), 'N');
}

int	check_map_syntax(t_Level *level)
{
	int		i;
	int		j;
	int		last;

	i = 0;
	while (level->map[i])
	{
		j = 0;
		while (level->map[i][j] != '\n' && level->map[i][j])
		{
			if (caracter_test(i, j, level) == 'N')
				return (1);
			j++;
		}
		if (i > 0 && j != last)
			return (perror("Error\nThe lines must have the same legth\n"), 1);
		last = j;
		i++;
	}
	if (level->has_colectable == 0)
		return (perror("Error\nThe map must have at least one colectable\n"), 1);
	if (j == i)
		return (perror("Error\nThe map must be a rectangle\n"), 1);
	level->limit->x = j - 1;
	return (0);
}

int	check_walls_top_bootom(t_Level *level)
{
	int	j;

	j = 0;
	while (j <= level->limit->x)
	{
		if (level->map[0][j] != '1' || level->map[level->limit->y][j] != '1')
			return (perror("Error\nThe map must be covered by walls\n"), 1);
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
			return (perror("Error\nThe map must be covered by walls\n"), 1);
		j = 0;
		while (level->map[i][j])
		{
			j++;
		}
		i++;
	}
	return (0);
}
