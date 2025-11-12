/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 08:57:01 by slayer            #+#    #+#             */
/*   Updated: 2025/11/12 19:19:23 by slayer           ###   ########.fr       */
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
	level->is_finished = 0;
	level->exit_init_pos->x = -1;
	level->exit_init_pos->y = -1;
	level->player_ini_pos->x = -1;
	level->player_ini_pos->y = -1;
	return (level);
}

int	img_create(t_Win_level *Win_level)
{
	int		img_width;
	int		img_height;

	Win_level->wall = mlx_xpm_file_to_image(Win_level->mlx, "./textures/wall.xpm", 
		&img_width, &img_height);
	Win_level->colectable = mlx_xpm_file_to_image(Win_level->mlx, "./textures/c7.xpm", 
	&img_width, &img_height);
	Win_level->player = mlx_xpm_file_to_image(Win_level->mlx, "./textures/sonic.xpm", 
	&img_width, &img_height);
	Win_level->exit = mlx_xpm_file_to_image(Win_level->mlx, "./textures/egg.xpm", 
		&img_width, &img_height);
	Win_level->floor = mlx_xpm_file_to_image(Win_level->mlx, "./textures/floor.xpm", 
	&img_width, &img_height);
	return 0;
}

void	load_map_img(t_Win_level *Win_level, t_Level *level)
{
	int	i;
	int	j;

	i = 0;
	while (i <= level->limit->y)
	{
		j = 0;
		while (j <= level->limit->x)
		{
			if (level->map[i][j] == '1')
				mlx_put_image_to_window(Win_level->mlx, Win_level->mlx_win, Win_level->wall,j*64,i*64);
			if (level->map[i][j] == '0')
				mlx_put_image_to_window(Win_level->mlx, Win_level->mlx_win, Win_level->floor,j*64,i*64);
			if (level->map[i][j] == 'P')
				mlx_put_image_to_window(Win_level->mlx, Win_level->mlx_win, Win_level->player,j*64,i*64);
			if (level->map[i][j] == 'C')
				mlx_put_image_to_window(Win_level->mlx, Win_level->mlx_win, Win_level->colectable,j*64,i*64);
			if (level->map[i][j] == 'E')
				mlx_put_image_to_window(Win_level->mlx, Win_level->mlx_win, Win_level->exit,j*64,i*64);
			j++;
		}
		i++;
	}

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
	return 0;
}

int	key_press_event(int key, void *vars)
{
	t_Game *game;

	game = (t_Game*)vars;
	if (key == 65307)
	{
		free_win_level(game->win_level);
		free_level(game->level);
		exit(0);
	}
	if (key == 119) //w
	{
		mlx_put_image_to_window(game->win_level->mlx, game->win_level->mlx_win, 
			game->win_level->player,(game->level->player_ini_pos->x - 1) *64,(game->level->player_ini_pos->y - 1)*64);
		mlx_put_image_to_window(game->win_level->mlx, game->win_level->mlx_win, 
			game->win_level->floor,game->level->player_ini_pos->x*64,game->level->player_ini_pos->y*64);
		game->level->player_ini_pos->y--;
	}
	if (key == 97) //a
	{
		
	}
	if (key == 115) //s
	{
		
	}
	if (key == 100) //d
	{
		
	}
	printf("key: %i\n", key);
	return 0;
}

int	exit_win(void *vars)
{
	t_Game *game;

	game = (t_Game*)vars;
	free_win_level(game->win_level);
	free_level(game->level);
	exit(0);
	return 0;
}

int	main(int argc, char const **argv)
{
	t_Level	*level;
	t_Win_level win_level;
	t_Game	game;

	if (parsing(argc, argv, &level))
		return (1);
	win_level.mlx = mlx_init();
	win_level.mlx_win = mlx_new_window(win_level.mlx, 64 * (level->limit->x + 1), 64 * (level->limit->y + 1), "o que tu quiseres!");
	img_create(&win_level);
	load_map_img(&win_level, level);
	game.level = level;
	game.win_level = &win_level;
	mlx_hook(win_level.mlx_win, 17, 1L << 0, exit_win, &game);
	mlx_key_hook(win_level.mlx_win, key_press_event, &game);
	mlx_loop(win_level.mlx);
	return (0);
}
