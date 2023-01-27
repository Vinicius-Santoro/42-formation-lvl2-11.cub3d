/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:31 by ldatilio          #+#    #+#             */
/*   Updated: 2023/01/26 22:29:36 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (data->map.start_line == 0)
		error_message(18, "Invalid map: missing map", data);
	data->map.map = &(data->map.lines[data->map.start_line - 1]);
	while (data->map.map[i] != NULL)
	{
		j = 0;
		printf("i: %02d", i);
		while (data->map.map[i][j] != '\0')
		{
			if (ft_strchr("0NSWE", data->map.map[i][j]) && (
				data->map.map[i][j + 1] == '\0' ||
				data->map.map[i][j - 1] == '\0' ||
				data->map.map[i + 1][j] == '\0' ||
				data->map.map[i - 1][j] == '\0'))
				error_message(19, "Invalid map: not surrounded by walls", data);
			j++;
		}
		printf("j: %02d  ", j);
		printf("line3: %s\n", data->map.map[i]);
		i++;
	}
}

void	check_is_missing_header(t_data *data)
{
	if (data->map.tex.no == NULL)
		error_message(12, "Invalid texture: missing NO", data);
	if (data->map.tex.so == NULL)
		error_message(13, "Invalid texture: missing SO", data);
	if (data->map.tex.we == NULL)
		error_message(14, "Invalid texture: missing WE", data);
	if (data->map.tex.ea == NULL)
		error_message(15, "Invalid texture: missing EA", data);
	if (data->map.color.floor == -1)
		error_message(16, "Invalid RGB: missing floor", data);
	if (data->map.color.ceil == -1)
		error_message(17, "Invalid RGB: missing ceil", data);
}

void	init_map(t_data *data)
{
	data->map.count_line = 0;
	data->map.line = ft_strdup("");
	data->map.splited_line = NULL;
	data->map.map = NULL;
	data->map.tex.no = NULL;
	data->map.tex.so = NULL;
	data->map.tex.we = NULL;
	data->map.tex.ea = NULL;
	data->map.color.floor = -1;
	data->map.color.ceil = -1;
	data->map.start_line = 0;
}

int	read_map(int fd, t_data *data)
{
	char	*temp;
	int		i;

	init_map(data);
	while (TRUE)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		data->map.line = ft_strjoin_free(data->map.line, temp);
		printf("line: %s", temp);
		free(temp);
	}
	data->map.lines = ft_split(data->map.line, '\n');
	free(data->map.line);
	i = -1;
	while (data->map.lines[++i])
		check_line(data->map.lines[i], data);
	check_is_missing_header(data);
}

int	validate_map(char *file_name, t_data *data)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_message(3, "Invalid file: not exist", data);
	if (is_valid_ext(file_name, ".cub") == FALSE)
		error_message(4, "Invalid file extension: not .cub", data);
	read_map(fd, data);
	get_map(data);
	close(fd);
	return (0);
}
