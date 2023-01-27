/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:58:54 by vnazioze          #+#    #+#             */
/*   Updated: 2023/01/27 00:18:19 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	validate_map_boundaries(char **map, int line, int column)
{
	if (ft_strchr("0NSWE", map[line][column]) && (
		map[line][column + 1] == '\0' || \
		map[line][column - 1] == '\0' || \
		map[line + 1][column] == '\0' || \
		map[line - 1][column] == '\0'))
		return (0);
	return (1);
}

void	get_map(t_data *data)
{
	int	line;
	int	column;

	line = 0;
	if (data->map.start_line == 0)
		error_message(18, "Invalid map: missing map", data);
	data->map.map = &(data->map.lines[data->map.start_line - 1]);
	while (data->map.map[line] != NULL)
	{
		column = 0;
		while (data->map.map[line][column] != '\0')
		{
			if (validate_map_boundaries(data->map.map, line, column) == FALSE)
				error_message(19, "Invalid map: not surrounded by walls", data);
			if (ft_strchr("NSWE", data->map.map[line][column]))
			{
				printf("player line (line): %02d\n", line);
				printf("player column (column): %02d\n", column);
			}
			column++;
		}
		line++;
		if(column > data->map.max_column)
			data->map.max_column = column;
	}
	printf("quantity line (line): %02d\n", line);
	printf("quantity column (column): %02d\n", column);
	printf("max column: %02d\n", data->map.max_column);
}
