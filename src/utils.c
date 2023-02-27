/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:22:28 by ldatilio          #+#    #+#             */
/*   Updated: 2023/02/26 23:21:39 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		is_valid_ext(char *file, const char *ext);
char	*ft_strjoin_free(char *s1, char const *s2);
int		ft_strisdigit(char *str);
void	get_fps(t_data *data);
int		mouse_move(int x, int y, t_data *data);

int	is_valid_ext(char *file, const char *ext)
{
	size_t	file_len;
	size_t	ext_len;

	file_len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	if (file_len > ext_len && \
		ft_strncmp(file + (file_len - ext_len), ext, ext_len) == 0)
		return (1);
	if (!ft_strncmp(ext, ".cub", 5))
		return (0);
	free(file);
	file = NULL;
	return (0);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*nstring;
	size_t	i;
	size_t	a;

	nstring = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	a = 0;
	if (nstring == 0)
		return (0);
	while (s1[i] != '\0')
	{
		nstring[i] = s1[i];
		i++;
	}
	while (s2[a] != '\0')
	{
		nstring[i + a] = s2[a];
		a++;
	}
	nstring[i + a] = '\0';
	free(s1);
	s1 = NULL;
	return (nstring);
}

int	ft_strisdigit(char *str)
{
	while (*str)
		if (ft_isdigit(*str++) == 0)
			return (0);
	return (1);
}

void	get_fps(t_data *data)
{	
	gettimeofday(&data->fps.tv, 0);
	if (data->fps.last_sec == data->fps.tv.tv_sec)
	{
		usleep(3000);
		data->fps.count_frame++;
	}
	else
	{
		data->fps.last_fps = data->fps.count_frame;
		data->fps.last_sec = data->fps.tv.tv_sec;
		data->fps.count_frame = 0;
		free(data->fps.str_fps);
		data->fps.str_fps = ft_itoa(data->fps.last_fps);
	}
	mlx_string_put(data->mlx, data->win, \
	WINDOW_SIZE * 0.05, WINDOW_SIZE * 0.05, \
	0x00FF00, data->fps.str_fps);
}

int	mouse_move(int x, int y, t_data *data)
{
	static int		last_x;

	(void)y;
	if (x > 0)
	{
		data->player.angle -= (x - WINDOW_SIZE / 2) * 0.0001;
		last_x = x;
	}
	else if (last_x > 0)
		data->player.angle -= (last_x - WINDOW_SIZE / 2) * 0.0001;
	return (0);
}
