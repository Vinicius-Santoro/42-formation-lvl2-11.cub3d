/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 03:09:58 by vnazioze          #+#    #+#             */
/*   Updated: 2023/02/25 14:33:01 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		raycast(t_data *data, double ra);
double		get_distance(t_data *data, double ra);
static void	get_deltadist(t_data *data, double ra);
static void	get_sidedist(t_data *data, double ra);
static void	collision_loop(t_data *data);

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
		make_vertical_line(\
			data, dist, data->player.y - dist * sin(ra), data->img.ea);
	else if (data->wall == 0)
		make_vertical_line(\
			data, dist, data->player.y - dist * sin(ra), data->img.we);
	else if (data->wall == 1 && ra <= PI)
		make_vertical_line(\
			data, dist, data->player.x + dist * cos(ra), data->img.no);
	else
		make_vertical_line(\
			data, dist, data->player.x + dist * cos(ra), data->img.so);
}

double	get_distance(t_data *data, double ra)
{
	if (ra >= 2 * PI)
		ra -= 2 * PI;
	if (ra < 0)
		ra += 2 * PI;
	get_deltadist(data, ra);
	get_sidedist(data, ra);
	collision_loop(data);
	if (data->wall == 0)
		return (data->sidedist_x - data->deltadist_x);
	else
		return (data->sidedist_y - data->deltadist_y);
}

static void	get_deltadist(t_data *data, double ra)
{
	if (cos(ra) == 0)
		data->deltadist_x = MAX_INT;
	else
		data->deltadist_x = fabs(SPRITE_SIZE / cos(ra));
	if (sin(ra) == 0)
		data->deltadist_y = MAX_INT;
	else
		data->deltadist_y = fabs(SPRITE_SIZE / sin(ra));
}

static void	get_sidedist(t_data *data, double ra)
{
	if (ra < PI)
	{
		data->sidedist_y = fabs(((int)(data->player.y) % SPRITE_SIZE) / sin (ra));
		data->step_y = -1;
	}
	else
	{
		data->sidedist_y = fabs((SPRITE_SIZE - (int)(data->player.y) % SPRITE_SIZE) / sin (ra));
		data->step_y = 1;
	}
	if (ra > PI / 2 && ra < 3 * PI / 2)
	{
		data->sidedist_x = fabs(((int)(data->player.x) % SPRITE_SIZE) / cos (ra));
		data->step_x = -1;
	}
	else
	{
		data->sidedist_x = fabs((SPRITE_SIZE - (int)(data->player.x) % SPRITE_SIZE) / cos (ra));
		data->step_x = 1;
	}
}

static void	collision_loop(t_data *data)
{
	data->map_x = (int)(data->player.x) >> 6;
	data->map_y = (int)(data->player.y) >> 6;
	while (data->map.map[data->map_y][data->map_x] != '1')
	{
		if (data->sidedist_x < data->sidedist_y)
		{
			data->sidedist_x += data->deltadist_x;
			data->map_x += data->step_x;
			data->wall = 0;
		}
		else
		{
			data->sidedist_y += data->deltadist_y;
			data->map_y += data->step_y;
			data->wall = 1;
		}
	}
}
