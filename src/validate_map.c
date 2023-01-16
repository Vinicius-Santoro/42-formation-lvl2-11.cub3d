/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:31 by ldatilio          #+#    #+#             */
/*   Updated: 2023/01/14 18:14:57 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_ext_cub(char *file)
{
	while (*file)
	{
		if (*file == '.' && *(file + 4) == '\0' \
		&& *(file + 1) == 'c' && *(file + 2) == 'u' && *(file + 3) == 'b')
			return (1);
		file++;
	}
	return (0);
}

int	validate_map(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (1);
	if (is_ext_cub(file_name) == FALSE)
		printf("\nThe file extension is NOT .cub");
	else
		printf("\nThe file extension is '.cub'");
	close(fd);
	return (0);
}
