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
# include <sys/time.h>

# define FALSE 0
# define TRUE 1

# define PI 3.1415926535
# define SPRITE_LEN 64

# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK 1
# define KEYRELEASEMASK 10
# define WINDOW_SIZE 512

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
	double		y;
	double		x;
	float		angle;
}	t_player;

typedef struct s_img_data
{
	void		*new_img;
	char		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_img_data;

typedef struct s_img
{
	t_img_data	*game;
	t_img_data	*no;
	t_img_data	*so;
	t_img_data	*we;
	t_img_data	*ea;
}	t_img;

typedef struct s_raycast
{
	int		x;
	int		line_h;
	int		line_o;
	int		y_max;
	int		y_ceil;
	float	ty;
	float	ty_step;
	float	ty_off;
	float	tx;
}	t_raycast;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_img		img;
	float		ra;
	int			ray_num;
	t_raycast	rc;
	double		deltadist_x;
	double		deltadist_y;
	double		sidedist_x;
	double		sidedist_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			wall;
	int			move_up;
	int			move_down;
	int			move_left;
	int			move_right;
	int			turn_left;
	int			turn_right;
	int			count_frame;
	int			last_sec;
	int			last_fps;
	char		*str_fps;
}	t_data;

int		read_map(int fd, t_data *data);
void	check_line(char *line, t_data *data);
void	parse_map(t_data *data);
void	make_image(t_data *data);

int		close_game(t_data *data);
void	error_message(int error_code, char *message_error, t_data *data);
void	exit_game(t_data *data);
void	free_matrix(char **matrix);

char	*ft_strjoin_free(char *s1, char const *s2);
int		ft_strisdigit(char *str);
int		is_valid_ext(char *file, const char *ext);

void	get_sidedist(t_data *data, double ra);
void	get_deltadist(t_data *data, double ra);
void	collision_loop(t_data *data);
double	get_distance(t_data *data, double ra);
void	raycast(t_data *data, double ra);

void	put_vertical_line(t_data *data, t_img_data *img);
void	make_vertical_line(t_data *data, int distance, double ix, t_img_data *img);
void	my_img_pixel_put(t_img_data *img, int x, int y, int color);
int		my_img_pixel_get(t_img_data *img, int x, int y);

int		ft_run(t_data *data);
int		arrows_up(int keycode, t_data *data);
int		arrows_down(int keycode, t_data *data);

#endif
