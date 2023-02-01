/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_img_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 03:19:39 by vnazioze          #+#    #+#             */
/*   Updated: 2023/02/01 03:19:41 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*byte;

	byte = img->img_addr + ((y * img->img_line_length)
			+ (x * img->img_bits_per_pixel / 8));
	*(unsigned int *)byte = color;
}

int	my_img_pixel_get(t_img *img, int x, int y)
{
	char	*byte;

	byte = img->img_addr + ((y * img->img_line_length)
			+ (x * img->img_bits_per_pixel / 8));
	return (*(unsigned int *)byte);
}
