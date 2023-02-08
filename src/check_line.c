/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 21:17:20 by ldatilio          #+#    #+#             */
/*   Updated: 2023/02/08 01:55:21 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_map_chars(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (0);
	while (line[i] != '\0')
	{
		if (!ft_strchr(" 01NSWE\n", line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	get_color(char *line, int color, t_data *data)
{
	// linha aparada
	char	*trimmed_line;
	int		rgb[3];
	int		i;

	i = -1;
	if (color != -1)
	{
		// Não pode ter ff, nem cc.
		error_message(7, "Invalid color: duplicated color rgb", data);
	}
	// Remove os espaços e as quebras de linha, pegando apenas o rgb.
	trimmed_line = ft_strtrim(line + 2, " \n\t\r");
	data->map.splited_line = ft_split(trimmed_line, ',');
	if (trimmed_line != NULL)
		free(trimmed_line);
	while (data->map.splited_line[++i])
	{
		if (ft_strisdigit(data->map.splited_line[i]) == FALSE)
			error_message(8, "Invalud RGB value: is not a digit", data);
		rgb[i] = ft_atoi(data->map.splited_line[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			error_message(9, "Invalid RGB value: is not a 8bits", data);
	}
	free_matrix(data->map.splited_line);
	data->map.splited_line = NULL;
	if (i != 3)
		error_message(10, "Invalid RGB value: is not a rgb", data);
	// formula de transformacao para rgb puro
	// return ((rgb[0] * BYTE * BYTE) + (rgb[1] * BYTE) + rgb[2]);
	return ((rgb[0] << 16) + (rgb[1] << 8) + (rgb[2] << 0));
}

static char	*get_tex_file(char *line, char *tex, t_data *data)
{
	char	*file_name;
	int		fd;

	if (fd < 0)
		error_message(5.0, "Invalid texture: file not exist", data);
	close(fd);
	if (tex != NULL)
		error_message(5.1, "Invalid texture: duplicated position", data);
	// Apagando espaço tanto no começo quanto no fim
	file_name = ft_strtrim(line + 3, " \n");
	fd = open(file_name, O_RDONLY);
	if (is_valid_ext(file_name, ".xpm") == FALSE)
		error_message(6, "Invalid file extension: not .xpm", data);
	return (file_name);
}

void	check_line(char *line, t_data *data)
{
	data->map.count_line++;
	if (ft_strncmp("NO ", line, 3) == 0)
		data->map.tex.no = get_tex_file(line, data->map.tex.no, data);
	else if (ft_strncmp("SO ", line, 3) == 0)
		data->map.tex.so = get_tex_file(line, data->map.tex.so, data);
	else if (ft_strncmp("WE ", line, 3) == 0)
		data->map.tex.we = get_tex_file(line, data->map.tex.we, data);
	else if (ft_strncmp("EA ", line, 3) == 0)
		data->map.tex.ea = get_tex_file(line, data->map.tex.ea, data);
	else if (ft_strncmp("F ", line, 2) == 0)
		data->map.color.floor = get_color(line, data->map.color.floor, data);
	else if (ft_strncmp("C ", line, 2) == 0)
		data->map.color.ceil = get_color(line, data->map.color.ceil, data);
	else if (check_map_chars(line) == TRUE && data->map.start_line == 0)
		data->map.start_line = data->map.count_line;
	else if (check_map_chars(line) == FALSE)
		error_message(11, "Invalid map: imposible characters", data);
}
