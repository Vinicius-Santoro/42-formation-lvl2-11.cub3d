/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 03:09:58 by vnazioze          #+#    #+#             */
/*   Updated: 2023/02/07 00:57:24 by vnazioze         ###   ########.fr       */
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
	printf("collision_loop START\n");
	data->map_x = (int)(data->player.column) >> 6;
	data->map_y = (int)(data->player.line) >> 6;
	printf("data->map_x: %d\n", data->map_x);
	printf("data->map_y: %d\n", data->map_y);
	printf("while: %c\n", data->map.map[data->map_y][data->map_x]);
	printf("collision_loop INIT LOOP\n");
	while (data->map.map[data->map_y][data->map_x] != '1')
	{
		printf("---\n");
		printf("while: %c\n", data->map.map[data->map_y][data->map_x]);
		printf("---\n");
		if (data->sidedist_x < data->sidedist_y)
		{
			data->sidedist_x += data->deltadist_x;
			data->map_x += data->step_x;
			data->wall = 0;
			printf("collision_loop 5\n");
		}
		else
		{
			data->sidedist_y += data->deltadist_y;
			data->map_y += data->step_y;
			data->wall = 1;
			printf("collision_loop 6\n");
		}
	}
	printf("collision_loop END\n");
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

	printf("raycast START\n");
	if (ra >= 2 * PI)
		ra -= 2 * PI;
	if (ra < 0)
		ra += 2 * PI;
	data->wall = 0;
	dist = get_distance(data, ra);
	ca = data->pa - data->ra;
	dist = dist * cos(ca);
	if (data->wall == 0 && (ra <= PI / 2 || ra >= 3 * PI / 2))
		make_vertical_line(data, dist, data->player.column - dist * sin(ra), data->e_img);
	else if (data->wall == 0)
		make_vertical_line(data, dist, data->player.column - dist * sin(ra), data->w_img);
	else if (data->wall == 1 && ra <= PI)
		make_vertical_line(data, dist, data->player.line + dist * cos(ra), data->n_img);
	else
		make_vertical_line(data, dist, data->player.line + dist * cos(ra), data->s_img);
	printf("raycast END\n");
}