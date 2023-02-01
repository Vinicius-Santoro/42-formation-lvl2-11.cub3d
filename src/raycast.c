/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 03:09:58 by vnazioze          #+#    #+#             */
/*   Updated: 2023/02/01 03:34:28 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_sidedist(t_data *data, double ra)
{
	if (ra < PI)
	{
		data->sidedist_y = fabs(((int)(data->py) % 64) / sin (ra));
		data->step_y = -1;
	}
	else
	{
		data->sidedist_y = fabs((64 - (int)(data->py) % 64) / sin (ra));
		data->step_y = 1;
	}
	if (ra > PI / 2 && ra < 3 * PI / 2)
	{
		data->sidedist_x = fabs(((int)(data->px) % 64) / cos (ra));
		data->step_x = -1;
	}
	else
	{
		data->sidedist_x = fabs((64 - (int)(data->px) % 64) / cos (ra));
		data->step_x = 1;
	}
}

void	get_deltadist(t_data *data, double ra)
{
	if (cos(ra) == 0)
		data->deltadist_x = 10000000;
	else
		data->deltadist_x = fabs(64 / cos(ra));
	if (sin(ra) == 0)
		data->deltadist_y = 10000000;
	else
		data->deltadist_y = fabs(64 / sin(ra));
}

void	collision_loop(t_data *data)
{
	printf("collision_loop 1\n");
	data->map_x = (int)(data->px) >> 6;
	printf("collision_loop 2\n");
	data->map_y = (int)(data->py) >> 6;
	printf("collision_loop 3\n");
	while (data->map.map[data->map_y][data->map_x] != '1')
	{
		printf("collision_loop 4\n");
		if (data->sidedist_x < data->sidedist_y)
		{
			data->sidedist_x += data->deltadist_x;
			data->map_x += data->step_x;
			data->wall = 0;
		}
		else
		{
			printf("collision_loop 5\n");
			data->sidedist_y += data->deltadist_y;
			printf("collision_loop 6\n");
			data->map_y += data->step_y;
			data->wall = 1;
		}
	}
}

double	get_distance(t_data *data, double ra)
{
	if (ra >= 2 * PI)
		ra -= 2 * PI;
	if (ra < 0)
		ra += 2 * PI;
		
	printf("get_distance 1\n");	
	get_deltadist(data, ra);
	printf("get_distance 2\n");
	get_sidedist(data, ra);
	printf("get_distance 3\n");
	collision_loop(data);
	printf("get_distance 4\n");
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
	printf("raycast 1\n");
	dist = get_distance(data, ra);
	printf("raycast 2\n");
	ca = data->pa - data->ra;
	dist = dist * cos(ca);
	if (data->wall == 0 && (ra <= PI / 2 || ra >= 3 * PI / 2))
		make_vertical_line(data, dist, data->py - dist * sin(ra), data->e_img);
	else if (data->wall == 0)
		make_vertical_line(data, dist, data->py - dist * sin(ra), data->w_img);
	else if (data->wall == 1 && ra <= PI)
		make_vertical_line(data, dist, data->px + dist * cos(ra), data->n_img);
	else
		make_vertical_line(data, dist, data->px + dist * cos(ra), data->s_img);
}