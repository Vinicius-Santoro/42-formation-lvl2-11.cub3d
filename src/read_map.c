/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:01:31 by ldatilio          #+#    #+#             */
/*   Updated: 2023/02/08 02:06:04 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_is_missing_header(t_data *data)
{
	if (data->map.tex.no == NULL)
		error_message(13, "Invalid texture: missing NO", data);
	if (data->map.tex.so == NULL)
		error_message(14, "Invalid texture: missing SO", data);
	if (data->map.tex.we == NULL)
		error_message(15, "Invalid texture: missing WE", data);
	if (data->map.tex.ea == NULL)
		error_message(16, "Invalid texture: missing EA", data);
	if (data->map.color.floor == -1)
		error_message(17, "Invalid RGB: missing floor", data);
	if (data->map.color.ceil == -1)
		error_message(18, "Invalid RGB: missing ceil", data);
}

static void	init_map(t_data *data)
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
	data->map.max_column = 0;
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
		free(temp);
	}
	data->map.lines = ft_split(data->map.line, '\n');
	free(data->map.line);
	i = -1;
	while (data->map.lines[++i])
		check_line(data->map.lines[i], data);
	check_is_missing_header(data);
}
