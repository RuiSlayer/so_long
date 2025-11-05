/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 08:57:01 by slayer            #+#    #+#             */
/*   Updated: 2025/11/05 15:05:55 by slayer           ###   ########.fr       */
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
	while ((line = get_next_line(fd)) != NULL)
	{
		i++;
		free(line);
	}
	close (fd);
	return (i);
}

char	**read_file(char const *argv)
{
	int		fd;
	int		i;
	char	**map;
	char	*line;

	i = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file\n"), NULL);
	i = count_lines(argv);
	if (i == -1)
		return (NULL);
	map = malloc((i + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
		map[i++] = line;
	map[i] = NULL;
	close(fd);
	return (map);
}

int	main(int argc, char const *argv[])
{
	char	**map;

	if (argc != 2)
		return (1);
	if (check_file_name(argv[1]))
		return (1);
	map = read_file(argv[1]);
	if (check_map_validity(map))
		return (free_map(map), 1);

	free_map(map);
	return (0);
}
