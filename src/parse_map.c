/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:58:54 by vnazioze          #+#    #+#             */
/*   Updated: 2023/02/13 00:15:00 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	validate_map_boundaries(int y, int x, t_data *data)
{
	char	**map;

	map = data->map.map;
	if (ft_strchr("0NSWE", map[y][x]) && (
		map[y][x + 1] == '\0' || map[y + 1][x + 1] == '\0' || \
		map[y][x - 1] == '\0' || map[y + 1][x - 1] == '\0' || \
		map[y + 1][x] == '\0' || map[y - 1][x + 1] == '\0' || \
		map[y - 1][x] == '\0' || map[y - 1][x - 1] == '\0' || \
		map[y][x + 1] == ' ' || map[y + 1][x + 1] == ' ' || \
		map[y][x - 1] == ' ' || map[y + 1][x - 1] == ' ' || \
		map[y + 1][x] == ' ' || map[y - 1][x + 1] == ' ' || \
		map[y - 1][x] == ' ' || map[y - 1][x - 1] == ' ' )
		)
		error_message(20, "Invalid map: not surrounded by walls", data);
}

static void	get_player_angle(int y, int x, t_data *data)
{
	if (ft_strchr("NSWE", data->map.map[y][x]))
	{
		data->player.count++;
		data->player.y = y * SPRITE_LEN + SPRITE_LEN / 2;
		data->player.x = x * SPRITE_LEN + SPRITE_LEN / 2;
		if (data->map.map[y][x] == 'E')
			data->player.angle = (PI / 2) * 0;
		if (data->map.map[y][x] == 'N')
			data->player.angle = (PI / 2) * 1;
		if (data->map.map[y][x] == 'W')
			data->player.angle = (PI / 2) * 2;
		if (data->map.map[y][x] == 'S')
			data->player.angle = (PI / 2) * 3;
	}
}

static void	get_map(t_data *data)
{
	if (data->map.start_line == 0)
		error_message(19, "Invalid map: missing map", data);
	data->map.map = &(data->map.lines[data->map.start_line - 1]);
}

void	parse_map(t_data *data)
{
	int	y;
	int	x;

	get_map(data);
	data->player.count = 0;
	y = -1;
	while (data->map.map[++y] != NULL)
	{
		x = -1;
		while (data->map.map[y][++x] != '\0')
		{
			validate_map_boundaries(y, x, data);
			get_player_angle(y, x, data);
		}
	}
	if (data->player.count > 1)
		error_message(21, "Invalid player: too many", data);
	if (data->player.count < 1)
		error_message(22, "Invalid player: not enough", data);
}
