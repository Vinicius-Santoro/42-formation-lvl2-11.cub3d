/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:56:12 by ldatilio          #+#    #+#             */
/*   Updated: 2023/02/01 23:59:01 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_vertical_line(t_data *data, t_img *img)
{
	while (data->rc.y_ceil <= data->rc.line_o)
	{
		data->rc.x = (data->ray_num * 8);
		while (data->rc.x < (data->ray_num * 8) + 8)
			my_img_pixel_put(data->game_img, data->rc.x++, data->rc.y_ceil, \
			data->map.color.ceil);
		data->rc.y_ceil++;
	}
	while (data->rc.line_o <= data->rc.y_max)
	{
		data->rc.x = (data->ray_num * 8);
		while (data->rc.x < (data->ray_num * 8) + 8)
			my_img_pixel_put(data->game_img, data->rc.x++, data->rc.line_o, \
			my_img_pixel_get(img, (int)data->rc.tx, (int)data->rc.ty));
		data->rc.line_o++;
		data->rc.ty += data->rc.ty_step;
	}
	while (data->rc.y_max <= 512)
	{
		data->rc.x = (data->ray_num * 8);
		while (data->rc.x < (data->ray_num * 8) + 8)
			my_img_pixel_put(data->game_img, data->rc.x++, data->rc.y_max, \
			data->map.color.floor);
		data->rc.y_max++;
	}
}

void	make_vertical_line(t_data *data, int distance, double ix, t_img *img)
{
	data->rc.y_ceil = 0;
	if (distance == 0)
		distance = 1;
	data->rc.line_h = (SPRITE_LEN * 512) / distance;
	data->rc.ty_step = 64.0 / (float)data->rc.line_h;
	data->rc.ty_off = 0;
	if (data->rc.line_h > 512)
	{
		data->rc.ty_off = (data->rc.line_h - 512) / 2.0;
		data->rc.line_h = 512;
	}
	data->rc.line_o = 256 - data->rc.line_h / 2;
	data->rc.y_max = data->rc.line_o + data->rc.line_h;
	data->rc.tx = (int)(ix) % 64;
	if (img == data->s_img || img == data->w_img)
		data->rc.tx = 63 - data->rc.tx;
	data->rc.ty = data->rc.ty_off * data->rc.ty_step;
	put_vertical_line(data, img);
}

t_img	*init_texture( char *file, t_data *data)
{
	int		trash;
	t_img	*ret;

	ret = malloc (sizeof(t_img));
	ret->img = mlx_xpm_file_to_image(data->mlx, file, &trash, &trash);
	ret->img_addr = mlx_get_data_addr(ret->img, &ret->img_bits_per_pixel,
			&ret->img_line_length, &ret->img_endian);
	return (ret);
}

void	init_game(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 512, 512, "Cub3d");
	printf("aqui?\n");
	data->n_img = init_texture(data->map.tex.no, data);
	printf("aqui??\n");
	data->n_img = init_texture(data->map.tex.no, data);
	data->s_img = init_texture(data->map.tex.so, data);
	data->w_img = init_texture(data->map.tex.we, data);
	data->e_img = init_texture(data->map.tex.ea, data);
	data->ray_num = 1;
	// data->wall = 0;
}

void	make_image(t_data *data)
{
	init_game(data);
	printf("aqui???\n");
	data->game_img = malloc(sizeof(t_img));
	printf("aqui????\n");
	data->game_img->img = mlx_new_image(data->mlx, 512, 512);
	data->game_img->img_addr = mlx_get_data_addr( \
		data->game_img->img, &data->game_img->img_bits_per_pixel, \
		&data->game_img->img_line_length, &data->game_img->img_endian \
		);
	printf("aqui - 5\n");
	data->ra = data->pa + (PI / 180 * 32);
	printf("aqui - 6\n");
	data->ray_num = 1;
	while (data->ray_num < 64)
	{
		raycast(data, data->ra);
		data->ra -= PI / 180;
		data->ray_num++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->game_img->img, 0, 0);
	printf("aqui?????\n");
	// mlx_destroy_image(data->mlx, data->game_img->img);
	printf("aqui6?\n");
	free(data->game_img);
	// mlx_loop(data->mlx);
	// mlx_destroy_window(data->mlx, data->win);
}
