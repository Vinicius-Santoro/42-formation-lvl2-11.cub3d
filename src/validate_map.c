/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:31 by ldatilio          #+#    #+#             */
/*   Updated: 2023/01/24 21:17:16 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_map(t_data *data)
{
	data->map.count_line = 0;
	data->map.line = ft_strdup("");
	data->map.splited_line = NULL;
	data->map.tex.no = NULL;
	data->map.tex.so = NULL;
	data->map.tex.we = NULL;
	data->map.tex.ea = NULL;
	data->map.color.floor = -1;
	data->map.color.ceil = -1;
}

int	read_map(int fd, t_data *data)
{
	char	*new_line;
	char	*temp;

	init_map(data);
	while (TRUE)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		check_line(temp, data);
		data->map.line = ft_strjoin_free(data->map.line, temp);
		printf("line: %s", temp);
		free(temp);
	}
	// data->map.lines = ft_split(data->map.line, '\n');
	free(data->map.line);
}

int	validate_map(const char *file_name, t_data *data)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_message(3, "File is not exist", data);
	if (is_valid_ext(file_name, ".cub") == FALSE)
		error_message(4, "The file extension is not '.cub'", data);
	read_map(fd, data);
	close(fd);
	return (0);
}
