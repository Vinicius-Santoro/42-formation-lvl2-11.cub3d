/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:33:41 by vnazioze          #+#    #+#             */
/*   Updated: 2022/11/21 20:33:41 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libs/libft/libft.h"

# define FALSE 0
# define TRUE 1

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RE "\033[0m"

typedef struct s_map
{
	char	*line;
	char	**lines;
	int		count_line;
}	t_map;

typedef struct s_tex
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_tex;

typedef struct s_color
{
	char	*ceil;
	char	*floor;
}	t_color;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_tex	tex;
	t_color	color;
}	t_data;

int		is_ext_cub(const char *file);
int		validate_map(const char *file_name, t_data *data);
void	verify_arguments(int argc);
void	error_message(int error_code, char *message_error);

char	*ft_strjoin_free(char *s1, char const *s2);

#endif
