/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_img_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 03:19:39 by vnazioze          #+#    #+#             */
/*   Updated: 2023/02/12 19:20:43 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * It takes an image, an x and y coordinate, and a color, and it puts the color at the x and y
 * coordinate on the image
 * 
 * @param img the image data structure
 * @param x x coordinate of the pixel
 * @param y the y coordinate of the pixel
 * @param color the color of the pixel
 */
void	my_img_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*byte;

	byte = img->address + ((y * img->line_length)
			+ (x * img->bits_per_pixel / 8));
	*(unsigned int *)byte = color;
}

/**
 * It returns the pixel at the given coordinates
 * 
 * @param img the image data structure
 * @param x x coordinate of the pixel
 * @param y the y coordinate of the pixel
 * 
 * @return The color of the pixel at the given coordinates.
 */
int	my_img_pixel_get(t_img_data *img, int x, int y)
{
	char	*byte;

	byte = img->address + ((y * img->line_length)
			+ (abs(x * img->bits_per_pixel / 8)));
	return (*(unsigned int*)byte);
}
