/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:34:30 by slayer            #+#    #+#             */
/*   Updated: 2025/11/13 00:44:35 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_file_name(char const *argv)
{
	int		i;
	int		j;
	char	*extencion;
	int		fd;

	if (argv[0] == '.')
		return (ft_printf("Error\nThe file can't be a hidden file\n"), 1);
	i = ft_strlen(argv) - 1;
	j = 3;
	extencion = ".ber";
	while (j >= 0)
	{
		if (argv[i] != extencion[j])
			return (ft_printf
				("Error\nYour file must be of the type .ber\n"), 1);
		i--;
		j--;
	}
	if (argv[i] == '/')
		return (ft_printf("Error\nThe file can't be a hidden file\n"), 1);
	fd = open(argv, __O_DIRECTORY);
	if (fd >= 0)
		return (close(fd), ft_printf("Error\nThe file can't be a dir\n"), 1);
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
		return (ft_printf("Error\nThe map must have only one exit\n"), 'N');
	if (level->map[i][j] == 'P' && level->player_ini_pos->x == -1)
	{
		level->player_ini_pos->y = i;
		level->player_ini_pos->x = j;
		return (level->map[i][j]);
	}
	if (level->map[i][j] == 'P' && level->player_ini_pos->x != -1)
		return (ft_printf("Error\nthe map must have only one player\n"), 'N');
	if (level->map[i][j] == 'C')
	{
		level->colectables++;
		return (level->map[i][j]);
	}
	return (ft_printf("Error\nInvalid Caracter in map\n"), 'N');
}

int	check_map_syntax_aux(t_Level *level)
{
	if (level->exit_init_pos->x == -1)
		return (ft_printf("Error\nThe map must contain an exit\n"), 1);
	if (level->player_ini_pos->x == -1)
		return (ft_printf("Error\nThe map must contain a player\n"), 1);
	if (level->colectables == 0)
		return (ft_printf("Error\nThe map must have one colectable\n"), 1);
	return (0);
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
			return (ft_printf("Error\nLines don't have same legth\n"), 1);
		last = j;
		i++;
	}
	if (check_map_syntax_aux(level))
		return (1);
	if (j == i)
		return (ft_printf("Error\nThe map must be a rectangle\n"), 1);
	level->limit->x = j - 1;
	return (0);
}
