/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 08:57:01 by slayer            #+#    #+#             */
/*   Updated: 2025/11/05 11:24:56 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**read_file(char const *argv)
{
	int		fd;
	int		i;
	char	**map;

	i = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
	}
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		map[i] = line;
		free(line);
		i++;
	}
	close(fd);
	return (map);
}

int main(int argc, char const *argv[])
{
	char	**map;
	if (argc != 2)
	{
		return (1);
	}
	check_file_name(argv[1]);
	map = read_file(argv[1]);
	for (size_t i = 0; map[i]; i++)
	{
		ft_printf("mapline: %s\n",map[i]);
	}
	return 0;
}
