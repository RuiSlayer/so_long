/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:50:32 by slayer            #+#    #+#             */
/*   Updated: 2025/11/05 15:10:41 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	length(char const *argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	return (count);
}

int	check_file_name(char const *argv)
{
	int		i;
	int		j;
	char	*extencion;

	i = length(argv) - 1;
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

char	caracter_test(char *set_essencial_init, char c)
{
	if (c == '0' || c == '1')
		return (c);
	if (c == 'E' && set_essencial_init[0] == '\0')
	{
		set_essencial_init[0] = 'E';
		return (c);
	}
	if (c == 'E' && set_essencial_init[0] != '\0')
		return (perror("The map must have only one exit\n"), 'N');
	if (c == 'P' && set_essencial_init[1] == '\0')
	{
		set_essencial_init[1] = 'P';
		return (c);
	}
	if (c == 'P' && set_essencial_init[1] != '\0')
		return (perror("the map must have only one player\n"), 'N');
	if (c == 'C')
	{
		set_essencial_init[2] = 'C';
		return (c);
	}
	return (printf("c: %c\n",c), perror("Invalid Caracter in map\n"), 'N');
}

int	check_map_validity(char **map)
{
	int		i;
	int		j;
	int		last;
	char	*set_essencial_init;

	i = 0;
	set_essencial_init = ft_calloc(4 , 1);
	if (!set_essencial_init)
		return (1);
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\n' && map[i][j])
		{
			if (caracter_test(set_essencial_init, map[i][j]) == 'N')
				return (free(set_essencial_init), 1);
			j++;
		}
		if (i > 0 && j != last)
			return (perror("the lines must have the same legth\n"), free(set_essencial_init), 1);
		last = j;
		i++;
	}
	if (set_essencial_init[2] == '\0')
		return (perror("The map must have at least one colectable\n"), free(set_essencial_init), 1);
	if (j == i)
		return (perror("The map must be a rectangle\n"), free(set_essencial_init), 1);
	return (free(set_essencial_init), 0);
}
