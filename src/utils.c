/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:22:28 by ldatilio          #+#    #+#             */
/*   Updated: 2023/01/25 19:57:07 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	is_valid_ext(char *file, const char *ext)
{
	size_t	file_len;
	size_t	ext_len;

	file_len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	if (file_len > ext_len && \
		ft_strncmp(file + (file_len - ext_len), ext, ext_len) == 0)
		return (1);
	free(file);
	file = NULL;
	return (0);
}
