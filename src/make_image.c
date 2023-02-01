/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:56:12 by ldatilio          #+#    #+#             */
/*   Updated: 2023/01/31 22:52:41 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// t_img_data	*init_texture(char *file, t_data *data)
// {
// 	// int		trash;
// 	t_img_data	*img;

// 	img = malloc (sizeof(t_img_data));
// 	img->new_img = mlx_xpm_file_to_image(data->mlx, file, NULL, NULL);
// 	img->address = mlx_get_data_addr(
// 		img->new_img, &img->bits_per_pixel, &img->line_length, &img->endian
// 		);
// 	return (img);
// }

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
}

void	make_image(t_data *data)
{
	init_game(data);
	data->game_img = malloc(sizeof(t_img));
	printf("aqui???\n");
	data->game_img->img_addr = mlx_get_data_addr( \
		data->game_img->img, &data->game_img->img_bits_per_pixel, \
		&data->game_img->img_line_length, &data->game_img->img_endian \
		);
	printf("aqui????\n");
	mlx_put_image_to_window(data->mlx, data->win, data->game_img->img, 0, 0);
	printf("aqui?????\n");
	// mlx_destroy_image(data->mlx, data->game_img->img);
	printf("aqui6?\n");
	free(data->game_img);
	// mlx_loop(data->mlx);
	// mlx_destroy_window(data->mlx, data->win);
}
