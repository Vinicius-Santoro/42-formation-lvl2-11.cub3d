/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 21:17:20 by ldatilio          #+#    #+#             */
/*   Updated: 2023/01/24 21:22:00 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_color(char *line, int color, t_data *data)
{
	char	*trimmed_line;
	int		rgb[3];
	int		i;

	i = -1;
	if (color != -1)
		error_message(7, "Duplicated color rgb", data);
	trimmed_line = ft_strtrim(line + 2, " \n\t\r");
	data->map.splited_line = ft_split(trimmed_line, ',');
	if (trimmed_line != NULL)
		free(trimmed_line);
	while (data->map.splited_line[++i])
	{
		if (ft_strisdigit(data->map.splited_line[i]) == FALSE)
			error_message(8, "Invalud RGB value, is not a digit", data);
		rgb[i] = ft_atoi(data->map.splited_line[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			error_message(9, "Invalid RGB value, is not a 8bits", data);
	}
	free_matrix(data->map.splited_line);
	data->map.splited_line = NULL;
	if (i != 3)
		error_message(10, "Invalid RGB value, is not a rgb", data);
	return ((rgb[0] * BYTE * BYTE) + (rgb[1] * BYTE) + rgb[2]);
}

char	*get_tex_file(char *line, char *tex, t_data *data)
{
	char	*file_name;

	if (tex != NULL)
		error_message(5, "Duplicated texture position", data);
	file_name = ft_strtrim(line + 3, " \n");
	if (is_valid_ext(file_name, ".xpm") == FALSE)
		error_message(6, "The file extension is not '.xpm'", data);
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
}