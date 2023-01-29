/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:56:12 by ldatilio          #+#    #+#             */
/*   Updated: 2023/01/28 23:22:29 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	make_image(t_data *data)
{
	// data->img = malloc(sizeof(t_img));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 800, 600, "cub3D");
	mlx_loop(data->mlx);
	mlx_destroy_window(data->mlx, data->win);
	// data->img.img = mlx_new_image(data->mlx, 512, 512);
	// free(data->img);
}