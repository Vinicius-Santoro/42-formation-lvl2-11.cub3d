/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:31 by ldatilio          #+#    #+#             */
/*   Updated: 2023/01/22 23:25:53 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_color(char *line, int color, t_data *data)
{
	char	**splited_line;
	char	*trimmed_line;
	int		rgb[3];
	int		i;

	i = -1;
	if (color != -1)
		error_message(1, "Duplicated color rgb");
	trimmed_line = ft_strtrim(line + 2, " \n\t\r");
	splited_line = ft_split(trimmed_line, ',');
	free(trimmed_line);
	while (splited_line[++i])
	{
		if (ft_strisdigit(splited_line[i]) == FALSE)
			error_message(1, "Invalud RGB value, is not a digit");
		rgb[i] = ft_atoi(splited_line[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			error_message(1, "Invalid RGB value, is not a 8bits");
	}
	if (i > 3)
		error_message(1, "Invalid RGB value, is not a rgb");
	return (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}

int	is_valid_ext(const char *file, const char *ext)
{
	size_t	file_len;
	size_t	ext_len;

	file_len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	if (file_len < ext_len)
		return (0);
	if (ft_strncmp(file + (file_len - ext_len), ext, ext_len) == 0)
		return (1);
	return (0);
}

char	*get_tex_file(char *line, char *tex, t_data *data)
{
	char	*file_name;

	if (tex != NULL)
		error_message(1, "Duplicated texture position");
	file_name = ft_strtrim(line + 3, " \n");
	if (is_valid_ext(file_name, ".xpm") == FALSE)
		error_message(1, "The file extension is not '.xpm'");
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

void	init_map(t_data *data)
{
	data->map.count_line = 0;
	data->map.line = ft_strdup("");
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
		error_message(1, "File is not exist");
	if (is_valid_ext(file_name, ".cub") == FALSE)
		error_message(1, "The file extension is not '.cub'");
	read_map(fd, data);
	close(fd);
	return (0);
}
