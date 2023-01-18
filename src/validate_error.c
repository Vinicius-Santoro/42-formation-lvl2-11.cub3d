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

#include "../include/cub3D.h"

void	error_message(int error_code, char *message_error)
{
	printf("Error\n");
	printf("%s\n", message_error);
	exit(error_code);
}

void	verify_arguments(int argc)
{
	if (argc > 2)
	{
		printf(RED"Error\nToo many arguments\n"RE);
		exit (1);
	}
	if (argc < 2)
	{
		printf(RED"Error\nNot enough arguments\n"RE);
		exit (1);
	}
}