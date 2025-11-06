/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 08:57:01 by slayer            #+#    #+#             */
/*   Updated: 2025/11/06 18:27:33 by slayer           ###   ########.fr       */
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

void	read_file(t_Level *level, char const *argv)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		perror("Error opening file");
	level->limit->y = count_lines(argv) - 1;
	if (level->limit->y == -1)
		close(fd);
	level->map = malloc((level->limit->y + 2) * sizeof(char *));
	if (!level->map)
		close(fd);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		level->map[i++] = line;
		line = get_next_line(fd);
	}
	level->map[i] = NULL;
	close(fd);
}

t_Level	*level_init(void)
{
	t_Level *level;
	level = malloc(sizeof(t_Level));
	level->limit = malloc(sizeof(t_Pos));
	level->player_ini_pos = malloc(sizeof(t_Pos));
	level->exit_init_pos = malloc(sizeof(t_Pos));
	if (!level->limit || !level->player_ini_pos || !level->exit_init_pos)
	{
		free(level->limit);
		free(level->player_ini_pos);
		free(level->exit_init_pos);
		free(level);
		return (NULL);
	}
	level->limit->x = -1;
	level->limit->y = -1;
	level->has_colectable = 0;
	level->exit_init_pos->x = -1;
	level->exit_init_pos->y = -1;
	level->player_ini_pos->x = -1;
	level->player_ini_pos->y = -1;
	return (level);
}

int	main(int argc, char const *argv[])
{
	t_Level *level;

	if (argc != 2)
		return (perror("Error\nYou must pass one file as parametre to the program\n"), 1);
	if (check_file_name(argv[1]))
		return (perror("Error\nYour file must be of the type .ber\n"), 1);
	level = level_init();
	read_file(level, argv[1]);
	if(!level)
		return(perror("Error\nMap creation failed\n"), 1);
	if (check_map_syntax(level))
		return (free_level(level), 1);
	if (check_map_semantics(level))
		return (free_level(level), 1);
	free_level(level);
	return (0);
}
