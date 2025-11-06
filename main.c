/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 08:57:01 by slayer            #+#    #+#             */
/*   Updated: 2025/11/06 16:28:44 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(char const *argv)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), -1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

char	**read_file(char const *argv)
{
	int		fd;
	int		i;
	char	**map;
	char	*line;
	int		count;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), NULL);
	count = count_lines(argv);
	if (count == -1)
		return (close(fd), NULL);
	map = malloc((count + 1) * sizeof(char *));
	if (!map)
		return (close(fd), NULL);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map[i++] = line;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	main(int argc, char const *argv[])
{
	char	**map;

	if (argc != 2)
		return (perror("Error\nYou must pass one file as parametre to the program\n"), 1);
	if (check_file_name(argv[1]))
		return (perror("Error\nYour file must be of the type .ber\n"), 1);
	map = read_file(argv[1]);
	if (check_map_syntax(map))
		return (free_map(map), 1);
	if (check_map_semantics(map))
		return (free_map(map), 1);
	free_map(map);
	return (0);
}
