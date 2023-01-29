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

# define BYTE 256
# define PI 3.14

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RE "\033[0m"

typedef struct s_tex
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}	t_tex;

typedef struct s_color
{
	int			ceil;
	int			floor;
}	t_color;

typedef struct s_map
{
	char		*line;
	char		**lines;
	char		**map;
	char		**splited_line;
	int			count_line;
	int			start_line;
	int			max_column;
	int			max_line;
	t_tex		tex;
	t_color		color;
}	t_map;

typedef struct s_player
{
	int			count;
	int			line;
	int			column;
	int			angle;
}	t_player;

typedef struct s_img
{
	void		*img;
}	t_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_img		img;
}	t_data;

int		validate_map(char *file_name, t_data *data);
void	check_line(char *line, t_data *data);
void	parse_map(t_data *data);
void	make_image(t_data *data);

void	error_message(int error_code, char *message_error, t_data *data);
void	exit_game(t_data *data);
void	free_matrix(char **matrix);

char	*ft_strjoin_free(char *s1, char const *s2);
int		ft_strisdigit(char *str);
int		is_valid_ext(char *file, const char *ext);


#endif
