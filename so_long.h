/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:50:46 by slayer            #+#    #+#             */
/*   Updated: 2025/11/06 16:24:53 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include<stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "ft_printf/ft_printf.h"
# include "42libft/libft.h"
# include "ft_get_next_line/get_next_line.h"

typedef struct Pos
{
	int	x;
	int	y;
}	t_Pos;

typedef struct Level
{
	char	**map;
	t_Pos	limit;
	t_Pos	player_ini;
	t_Pos	exit;
}	t_Level;

int		check_file_name(char const *argv);
int		check_map_syntax(char **map);
int		check_map_semantics(char **map);
void	free_map(char **map);

#endif