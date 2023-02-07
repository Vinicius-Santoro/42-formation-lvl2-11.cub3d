/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:11:32 by vnazioze          #+#    #+#             */
/*   Updated: 2022/11/21 20:11:32 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define KEYPRESSMASK 1
#define KEYPRESS 2


int	int_make_image(t_data *data)
{
	make_image(data);
	return 0;
}

int	arrows_down(t_data *data)
{
	make_image(data);
	return 0;
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc > 2)
		error_message(1, "Invalid arguments: too many", data);
	if (argc < 2)
		error_message(2, "Invalid arguments: not enough", data);
	data = malloc(sizeof(t_data));
	if (validate_map(argv[1], data) == TRUE)
		return (1);
	make_image(data);
	mlx_loop_hook(data->win, arrows_down, data);
	mlx_loop(data->mlx);
	exit_game(data);
	free(data);
	return (0);
}
