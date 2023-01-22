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

void	error_message(int error_code, char *message_error)
{
	printf("Error\n");
	printf(RED"%s\n"RE, message_error);
	exit(error_code);
}

void	verify_arguments(int argc)
{
	if (argc > 2)
		error_message(1, "Too many arguments\n");
	if (argc < 2)
		error_message(1, "Not enough arguments\n");
}
