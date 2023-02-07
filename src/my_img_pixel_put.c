/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_img_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 03:19:39 by vnazioze          #+#    #+#             */
/*   Updated: 2023/02/06 22:51:06 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_img_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*byte;

	byte = img->address + ((y * img->line_length)
			+ (x * img->bits_per_pixel / 8));
	*(unsigned int *)byte = color;
}

int	my_img_pixel_get(t_img_data *img, int x, int y)
{
	char	*byte;

	byte = img->address + ((y * img->line_length)
			+ (x * img->bits_per_pixel / 8));
	return (*(unsigned int *)byte);
}
