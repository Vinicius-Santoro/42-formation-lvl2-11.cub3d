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
	(void) argc;
	if (argc != 2)
		verify_arguments(argc);
	if (validate_map(argv[1]) == TRUE)
		return (1);
	return (0);
}
