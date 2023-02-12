/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 08:02:26 by vnazioze          #+#    #+#             */
/*   Updated: 2023/01/17 08:02:26 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix != NULL)
	{
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}

void	error_message(int error_code, char *message_error, t_data *data)
{
	printf("Error\n");
	printf(RED"%s\n"RE, message_error);
	if (error_code > 4)
		exit_game(data);
	free(data);
	exit(error_code);
}

void	exit_game(t_data *data)
{
	free(data->map.tex.no);
	free(data->map.tex.so);
	free(data->map.tex.we);
	free(data->map.tex.ea);
	free_matrix(data->map.splited_line);
	free_matrix(data->map.lines);
}

void	destroy_images(t_data *data)
{
	// mlx_destroy_image(data->mlx, data->img.game->new_img);
	// free(data->img.game);

	// if (data->n_img)
	// {
	mlx_destroy_image(data->mlx, data->img.no->new_img);
	free(data->img.no);
	// }
	// if (data->s_img)
	// {
	mlx_destroy_image(data->mlx, data->img.so->new_img);
	free(data->img.so);
	// }
	// if (data->w_img)
	// {
	mlx_destroy_image(data->mlx, data->img.we->new_img);
	free(data->img.we);
	// }
	// if (data->e_img)
	// {
	mlx_destroy_image(data->mlx, data->img.ea->new_img);
	free(data->img.ea);
	// }
	mlx_clear_window(data->mlx, data->win);
	mlx_loop_end(data->mlx);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	free_img(t_data *data)
{

}

int	close_game(t_data *data)
{
	destroy_images(data);
	exit_game(data);
	free(data);
	printf("%scub%s3%sD%s: was %sclosed.%s\n", MAGENTA, BLUE, RED, RE, BLUE, RE);
	exit(0);
}