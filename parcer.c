/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slayer <slayer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:50:32 by slayer            #+#    #+#             */
/*   Updated: 2025/11/05 11:14:16 by slayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	length(char const *argv)
{
	int	count;

	count = 0;
	while (argv[count])
	{
		count++;
	}
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
		{
			return (1);
		}
		i--;
		j--;
	}
	return (0);
}
