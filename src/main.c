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

#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		verify_arguments(argc);
	data = ft_calloc(sizeof(t_data), 1);
	if (validate_map(argv[1], data) == TRUE)
		return (1);
	free(data);
	return (0);
}
