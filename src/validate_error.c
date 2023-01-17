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

void	verify_arguments(int argc)
{
	if (argc > 2)
	{
		printf(RED"Error: Too many arguments\n"RE);
		exit (1);
	}
	if (argc < 2)
	{
		printf(RED"Error: Not enough arguments\n"RE);
		exit (1);
	}
}