/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:43:59 by ldatilio          #+#    #+#             */
/*   Updated: 2023/02/13 19:56:57 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	arrows_down(int keycode, t_data *data)
{
	if (keycode == 97)
		data->move_left = 1;
	if (keycode == 100)
		data->move_right = 1;
	if (keycode == 115)
		data->move_down = 1;
	if (keycode == 119)
		data->move_up = 1;
	if (keycode == 65361)
		data->turn_left = 1;
	if (keycode == 65363)
		data->turn_right = 1;
	if (keycode == 65307)
		close_game(data);
	return (0);
}

int	arrows_up(int keycode, t_data *data)
{
	if (keycode == 97)
		data->move_left = 0;
	if (keycode == 100)
		data->move_right = 0;
	if (keycode == 115)
		data->move_down = 0;
	if (keycode == 119)
		data->move_up = 0;
	if (keycode == 65361)
		data->turn_left = 0;
	if (keycode == 65363)
		data->turn_right = 0;
	if (keycode == 65307)
		close_game(data);
	return (0);
}

int	check_collision(t_data *data, double ra)
{
	int	map_x;
	int	map_y;

	get_distance(data, ra);
	map_x = data->player.x + (30 * data->step_x);
	map_y = data->player.y + (30 * data->step_y);
	map_x = map_x >> 6;
	map_y = map_y >> 6;
	if (data->map.map[map_y][(int)(data->player.x) >> 6] == '1' || \
	data->map.map[(int)(data->player.y) >> 6][map_x] == '1' || \
	data->map.map[map_y][map_x] == '1')
		return (0);
	return (1);
}

void	movement(t_data *data)
{
	if (data->move_up == 1 && check_collision(data, data->player.angle))
	{
		data->player.x += 2 * cos(data->player.angle);
		data->player.y -= 2 * sin(data->player.angle);
	}
	if (data->move_down == 1 && check_collision(data, data->player.angle + PI))
	{
		data->player.x -= 2 * cos(data->player.angle);
		data->player.y += 2 * sin(data->player.angle);
	}
	if (data->move_right == 1 && check_collision(data, data->player.angle - PI / 2))
	{
		data->player.x += 2 * sin(data->player.angle);
		data->player.y += 2 * cos(data->player.angle);
	}
	if (data->move_left == 1 && check_collision(data, data->player.angle + PI / 2))
	{
		data->player.x -= 2 * sin(data->player.angle);
		data->player.y -= 2 * cos(data->player.angle);
	}
}

int	ft_run(t_data *data)
{
	movement(data);
	if (data->turn_left == 1)
		data->player.angle += PI / 180;
	if (data->turn_right == 1)
		data->player.angle -= PI / 180;
	if (data->player.angle > PI * 2)
		data->player.angle -= PI * 2;
	if (data->player.angle < 0)
		data->player.angle += PI * 2;
	make_image(data);
	return (0);
}
