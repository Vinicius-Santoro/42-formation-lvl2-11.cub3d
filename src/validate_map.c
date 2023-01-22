/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:31 by ldatilio          #+#    #+#             */
/*   Updated: 2023/01/22 16:09:22 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*get_tex_file(char *line, char *tex, t_data *data)
{
	char set[] = " \t\n\r";
    char *file_name = ft_strtrim(line + 3, set);
    printf("\nNome do arquivo: %s\n", file_name);
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
	if (is_ext_cub(file_name) == FALSE)
		error_message(1, "The file extension is not '.cub'");
	else
		printf("\nThe file extension is '.cub'");
	read_map(fd, data);
	close(fd);
	return (0);
}
