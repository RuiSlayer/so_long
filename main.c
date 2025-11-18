/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 08:57:01 by slayer            #+#    #+#             */
/*   Updated: 2025/11/18 18:56:32 by rucosta          ###   ########.fr       */
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

int	parsing(int argc, char const *argv[], t_Level **level)
{
	if (argc != 2)
		return (ft_printf
			("Error\nYou must pass one file as parametre to the program\n"), 1);
	if (check_file_name(argv[1]))
		return (1);
	*level = level_init();
	if (!*level)
		return (ft_printf("Error\nLevel creation faild\n"), 1);
	if (read_file(*level, argv[1]))
		return (free_level_soft(*level), 1);
	if (!*level)
		return (ft_printf("Error\nMap creation failed\n"), 1);
	if (check_map_syntax(*level))
		return (free_level(*level), 1);
	if (check_map_semantics(*level))
		return (free_level(*level), 1);
	return (0);
}

int	key_press_event(int key, void *vars)
{
	t_Game	*game;

	game = (t_Game *)vars;
	if (key == 65307)
	{
		free_win_level(game->win_level);
		free_level(game->level);
		exit(0);
	}
	if (key == 119)
		move(game, 0, -1);
	if (key == 97)
		move(game, -1, 0);
	if (key == 115)
		move(game, 0, 1);
	if (key == 100)
		move(game, 1, 0);
	return (0);
}

int	main(int argc, char const **argv)
{
	t_Level		*level;
	t_Win_level	win_level;
	t_Game		game;

	if (parsing(argc, argv, &level))
		return (1);
	win_level.mlx = mlx_init();
	win_level.mlx_win = mlx_new_window(win_level.mlx,
			64 * (level->limit->x + 1), 64 * (level->limit->y + 1), "So_Long");
	if (img_create(&win_level, level))
		return (ft_printf("Error\nImage creation fail\n"), 1);
	load_map_img(&win_level, level);
	game.level = level;
	game.win_level = &win_level;
	ft_printf("moves: %d\n", level->move_counter);
	mlx_hook(win_level.mlx_win, 17, 1L << 0, exit_win, &game);
	mlx_key_hook(win_level.mlx_win, key_press_event, &game);
	mlx_loop(win_level.mlx);
	return (0);
}
