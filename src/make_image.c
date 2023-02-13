/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:56:12 by ldatilio          #+#    #+#             */
/*   Updated: 2023/02/12 23:38:29 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_vertical_line(t_data *data, t_img_data *img)
{
	while (data->rc.y_ceil <= data->rc.line_o)
	{
		data->rc.x = (data->ray_num * 8);
		while (data->rc.x < (data->ray_num * 8) + 8)
			my_img_pixel_put(data->img.game, data->rc.x++, data->rc.y_ceil, \
			data->map.color.ceil);
		data->rc.y_ceil++;
	}
	while (data->rc.line_o <= data->rc.y_max)
	{
		data->rc.x = (data->ray_num * 8);
		while (data->rc.x < (data->ray_num * 8) + 8)
			my_img_pixel_put(data->img.game, data->rc.x++, data->rc.line_o, \
			my_img_pixel_get(img, (int)data->rc.tx, (int)data->rc.ty));
		data->rc.line_o++;
		data->rc.ty += data->rc.ty_step;
	}
	while (data->rc.y_max <= WINDOW_SIZE)
	{
		data->rc.x = (data->ray_num * 8);
		while (data->rc.x < (data->ray_num * 8) + 8)
			my_img_pixel_put(data->img.game, data->rc.x++, data->rc.y_max, \
			data->map.color.floor);
		data->rc.y_max++;
	}
}

void	make_vertical_line(t_data *data, int distance, double ix, t_img_data *img)
{
	data->rc.y_ceil = 0;
	if (distance == 0)
		distance = 1;
	data->rc.line_h = (SPRITE_LEN * WINDOW_SIZE) / distance;
	data->rc.ty_step = 64.0 / (float)data->rc.line_h;
	data->rc.ty_off = 0;
	if (data->rc.line_h > WINDOW_SIZE)
	{
		data->rc.ty_off = (data->rc.line_h - WINDOW_SIZE) / 2.0;
		data->rc.line_h = WINDOW_SIZE;
	}
	data->rc.line_o = 256 - data->rc.line_h / 2;
	data->rc.y_max = data->rc.line_o + data->rc.line_h;
	data->rc.tx = (int)(ix) % 64;
	if (img == data->img.so || img == data->img.we)
		data->rc.tx = 63 - data->rc.tx;
	data->rc.ty = data->rc.ty_off * data->rc.ty_step;
	put_vertical_line(data, img);
}

void	get_fps(t_data *data)
{	
	struct timeval	tv;

	gettimeofday(&tv, 0);
	if (data->last_sec == tv.tv_sec * 1000)
		data->count_frame++;
	else
	{
		data->last_sec = tv.tv_sec * 1000;
		printf("fps: %d\n", data->count_frame);
		data->count_frame=0;		
	}
}

void	make_image(t_data *data)
{
	get_fps(data);
	data->img.game = malloc(sizeof(t_img));
	data->img.game->new_img = mlx_new_image(data->mlx, WINDOW_SIZE, WINDOW_SIZE);
	data->img.game->address = mlx_get_data_addr( \
		data->img.game->new_img, &data->img.game->bits_per_pixel, \
		&data->img.game->line_length, &data->img.game->endian \
		);
	data->ra = data->player.angle + (PI / 180 * 32);
	data->ray_num = 0;
	while (data->ray_num < 64)
	{
		raycast(data, data->ra);
		data->ra -= PI / 180;
		data->ray_num++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.game->new_img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.game->new_img);
	free(data->img.game);
}
