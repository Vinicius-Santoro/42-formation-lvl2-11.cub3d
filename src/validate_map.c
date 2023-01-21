/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:31 by ldatilio          #+#    #+#             */
/*   Updated: 2023/01/21 20:24:32 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	is_ext_cub(const char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (file[len - 4] != '.' || file[len - 3] != 'c' || \
		file[len - 2] != 'u' || file[len - 1] != 'b')
		return (0);
	return (1);
}

int	read_map(int fd, t_data *data)
{
	char	*new_line;
	char	*temp;

	data->map.line = ft_strdup("");
	while (TRUE)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		data->map.line = ft_strjoin_free(data->map.line, temp);
		free(temp);
	}
	free(data->map.line);
}

int	validate_map(const char *file_name, t_data *data)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_message(1, "File is not exist");
	if (is_ext_cub(file_name) == FALSE)
		error_message(1, "The file extension is not '.cub'");
	else
		printf("\nThe file extension is '.cub'");
	read_map(fd, data);
	close(fd);
	return (0);
}
