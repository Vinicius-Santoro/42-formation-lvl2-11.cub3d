/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:56:12 by ldatilio          #+#    #+#             */
/*   Updated: 2023/02/25 11:36:53 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		make_image(t_data *data);
void		make_vertical_line(
				t_data *data, int dist, double ix, t_img_data *img);
static void	put_vertical_line(t_data *data, t_img_data *img);
static void	put_pixel_img(t_img_data *img, int x, int y, int color);
static int	get_pixel_img(t_img_data *img, int x, int y);

void	make_image(t_data *data)
{
	mouse_move(0, 0, data);
	data->img.game = malloc(sizeof(t_img));
	data->img.game->new_img = mlx_new_image(\
		data->mlx, WINDOW_SIZE, WINDOW_SIZE \
		);
	data->img.game->address = mlx_get_data_addr(\
		data->img.game->new_img, &data->img.game->bits_per_pixel, \
		&data->img.game->line_length, &data->img.game->endian \
		);
	data->ra = data->player.angle + (PI / 180 * SPRITE_SIZE / 2);
	data->ray_num = 0;
	while (data->ray_num < SPRITE_SIZE)
	{
		raycast(data, data->ra);
		data->ra -= PI / 180;
		data->ray_num++;
	}
	mlx_put_image_to_window(
		data->mlx, data->win, data->img.game->new_img, 0, 0
		);
	mlx_destroy_image(data->mlx, data->img.game->new_img);
	free(data->img.game);
	get_fps(data);
}

void	make_vertical_line(t_data *data, int dist, double ix, t_img_data *img)
{
	data->rc.y_ceil = 0;
	if (dist == 0)
		dist = 1;
	data->rc.line_height = (SPRITE_SIZE * WINDOW_SIZE) / dist;
	data->rc.y_tex_step = SPRITE_SIZE / (float)data->rc.line_height;
	data->rc.y_tex_offset = 0;
	if (data->rc.line_height > WINDOW_SIZE)
	{
		data->rc.y_tex_offset = (data->rc.line_height - WINDOW_SIZE) / 2.0;
		data->rc.line_height = WINDOW_SIZE;
	}
	data->rc.line_offset = WINDOW_SIZE / 2 - data->rc.line_height / 2;
	data->rc.y_max = data->rc.line_offset + data->rc.line_height;
	data->rc.x_tex = (int)(ix) % SPRITE_SIZE;
	if (img == data->img.so || img == data->img.we)
		data->rc.x_tex -= SPRITE_SIZE - 1;
	data->rc.y_tex = data->rc.y_tex_offset * data->rc.y_tex_step;
	put_vertical_line(data, img);
}

static void	put_vertical_line(t_data *data, t_img_data *img)
{
	while (data->rc.y_ceil <= data->rc.line_offset)
	{
		data->rc.x = (data->ray_num * SPRITE_SCALE);
		while (data->rc.x < (data->ray_num * SPRITE_SCALE) + SPRITE_SCALE)
			put_pixel_img(data->img.game, data->rc.x++, data->rc.y_ceil, \
			data->map.color.ceil);
		data->rc.y_ceil++;
	}
	while (data->rc.line_offset <= data->rc.y_max)
	{
		data->rc.x = (data->ray_num * SPRITE_SCALE);
		while (data->rc.x < (data->ray_num * SPRITE_SCALE) + SPRITE_SCALE)
			put_pixel_img(data->img.game, data->rc.x++, data->rc.line_offset,
				get_pixel_img(img, (int)data->rc.x_tex, (int)data->rc.y_tex));
		data->rc.line_offset++;
		data->rc.y_tex += data->rc.y_tex_step;
	}
	while (data->rc.y_max <= WINDOW_SIZE)
	{
		data->rc.x = (data->ray_num * SPRITE_SCALE);
		while (data->rc.x < (data->ray_num * SPRITE_SCALE) + SPRITE_SCALE)
			put_pixel_img(data->img.game, data->rc.x++, data->rc.y_max, \
			data->map.color.floor);
		data->rc.y_max++;
	}
}

static void	put_pixel_img(t_img_data *img, int x, int y, int color)
{
	char	*byte;

	byte = img->address + ((y * img->line_length)
			+ (x * img->bits_per_pixel / SPRITE_SCALE));
	*(unsigned int *)byte = color;
}

static int	get_pixel_img(t_img_data *img, int x, int y)
{
	char	*byte;

	byte = img->address + ((y * img->line_length)
			+ (abs(x * img->bits_per_pixel / SPRITE_SCALE)));
	return (*(unsigned int *)byte);
}
