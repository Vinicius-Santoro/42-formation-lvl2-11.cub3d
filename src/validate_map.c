/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:31 by ldatilio          #+#    #+#             */
/*   Updated: 2023/01/17 23:24:21 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	is_ext_cub(const char *file)
{
	size_t	len;

	len = strlen(file);
	if (file[len - 4] != '.' || file[len - 3] != 'c' || \
		file[len - 2] != 'u' || file[len - 1] != 'b')
		return (0);
	return (1);
}

int	validate_map(const char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (1);
	if (is_ext_cub(file_name) == FALSE)
		error_message();
	else
		printf("\nThe file extension is '.cub'");
	close(fd);
	return (0);
}
