/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:31 by ldatilio          #+#    #+#             */
/*   Updated: 2023/01/22 18:36:12 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int is_valid_ext(const char *file, const char *ext)
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
	char set[] = " \t\n\r";
    char *file_name = ft_strtrim(line + 3, set);
	if (is_valid_ext(file_name, ".xpm") == FALSE)
		error_message(1, "The file extension is not '.xpm'");
    return (file_name);
}

void	check_line(char *line, t_data *data)
{
	data->map.count_line++;
	if (ft_strncmp("NO ", line, 3) == 0)
		data->tex.no = get_tex_file(line, data->tex.no, data);
	else if (ft_strncmp("SO ", line, 3) == 0)
		data->tex.so = get_tex_file(line, data->tex.so, data);
	else if (ft_strncmp("WE ", line, 3) == 0)
		data->tex.we = get_tex_file(line, data->tex.we, data);
	else if (ft_strncmp("EA ", line, 3) == 0)
		data->tex.ea = get_tex_file(line, data->tex.ea, data);
}

int	read_map(int fd, t_data *data)
{
	char	*new_line;
	char	*temp;

	data->map.count_line = 0;
	data->map.line = ft_strdup("");
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
