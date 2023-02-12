/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 03:09:58 by vnazioze          #+#    #+#             */
/*   Updated: 2023/02/11 15:42:53 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_sidedist(t_data *data, double ra)
{
	if (ra < PI)
	{
		data->sidedist_y = fabs(((int)(data->player.column) % 64) / sin (ra));
		data->step_y = -1;
	}
	else
	{
		data->sidedist_y = fabs((64 - (int)(data->player.column) % 64) / sin (ra));
		data->step_y = 1;
	}
	if (ra > PI / 2 && ra < 3 * PI / 2)
	{
		data->sidedist_x = fabs(((int)(data->player.line) % 64) / cos (ra));
		data->step_x = -1;
	}
	else
	{
		data->sidedist_x = fabs((64 - (int)(data->player.line) % 64) / cos (ra));
		data->step_x = 1;
	}
}

void	get_deltadist(t_data *data, double ra)
{
	if (cos(ra) == 0)
		data->deltadist_x = 2147483647;
	else
		data->deltadist_x = fabs(64 / cos(ra));
	if (sin(ra) == 0)
		data->deltadist_y = 2147483647;
	else
		data->deltadist_y = fabs(64 / sin(ra));
}

void	collision_loop(t_data *data)
{
	data->map_column = (int)(data->player.column) >> 6;
	data->map_line = (int)(data->player.line) >> 6;
	while (data->map.map[data->map_line][data->map_column] != '1')
	{
		if (data->sidedist_x < data->sidedist_y)
		{
			data->sidedist_x += data->deltadist_x;
			data->map_column += data->step_x;
			data->wall = 0;
		}
		else
		{
			data->sidedist_y += data->deltadist_y;
			data->map_line += data->step_y;
			data->wall = 1;
		}
	}
}

double	get_distance(t_data *data, double ra)
{
		
	get_deltadist(data, ra);
	get_sidedist(data, ra);
	collision_loop(data);
	if (data->wall == 0)
		return (data->sidedist_x - data->deltadist_x);
	else
		return (data->sidedist_y - data->deltadist_y);
}

void	raycast(t_data *data, double ra)
{
	double		ca;
	double		dist;

	if (ra >= 2 * PI)
		ra -= 2 * PI;
	if (ra < 0)
		ra += 2 * PI;
	data->wall = 0;
	dist = get_distance(data, ra);
	ca = data->player.angle - data->ra;
	dist = dist * cos(ca);
	if (data->wall == 0 && (ra <= PI / 2 || ra >= 3 * PI / 2))
		make_vertical_line(data, dist, data->player.column - dist * sin(ra), data->img.ea);
	else if (data->wall == 0)
		make_vertical_line(data, dist, data->player.column - dist * sin(ra), data->img.we);
	else if (data->wall == 1 && ra <= PI)
		make_vertical_line(data, dist, data->player.line + dist * cos(ra), data->img.no);
	else
		make_vertical_line(data, dist, data->player.line + dist * cos(ra), data->img.so);
}
