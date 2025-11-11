/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 08:57:01 by slayer            #+#    #+#             */
/*   Updated: 2025/11/11 15:51:53 by slayer           ###   ########.fr       */
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
		return (ft_printf("Error\n opening file\n"), -1);
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

int	read_file(t_Level *level, char const *argv)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nFile opening fail\n"), 1);
	level->limit->y = count_lines(argv) - 1;
	if (level->limit->y == -1)
		return (ft_printf("Error\nFile is empty\n"), 1);
	if (level->limit->y == -1)
		return (close(fd), 1);
	level->map = malloc((level->limit->y + 2) * sizeof(char *));
	if (!level->map)
		return (close(fd), 1);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		level->map[i++] = line;
		line = get_next_line(fd);
	}
	level->map[i] = NULL;
	close(fd);
	return (0);
}

t_Level	*level_init(void)
{
	t_Level	*level;

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
	level->colectables = 0;
	level->exit_init_pos->x = -1;
	level->exit_init_pos->y = -1;
	level->player_ini_pos->x = -1;
	level->player_ini_pos->y = -1;
	return (level);
}

int	main(int argc, char const *argv[])
{
	t_Level	*level;
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1366, 768, "o que tu quiseres!");
	mlx_loop(mlx);
	if (argc != 2)
		return (ft_printf
			("Error\nYou must pass one file as parametre to the program\n"), 1);
	if (check_file_name(argv[1]))
		return (1);
	level = level_init();
	if (!level)
		return (ft_printf("Error\nLevel creation faild\n"), 1);
	if (read_file(level, argv[1]))
		return (free_level_soft(level), 1);
	if (!level)
		return (ft_printf("Error\nMap creation failed\n"), 1);
	if (check_map_syntax(level))
		return (free_level(level), 1);
	if (check_map_semantics(level))
		return (free_level(level), 1);
	free_level(level);
	return (0);
}
