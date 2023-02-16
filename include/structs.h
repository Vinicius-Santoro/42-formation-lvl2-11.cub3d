/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:50:50 by ldatilio          #+#    #+#             */
/*   Updated: 2023/02/16 00:03:27 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3D.h"

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
	int		line_height;
	int		line_offset;
	int		y_max;
	int		y_ceil;
	float	y_tex;
	float	y_tex_step;
	float	y_tex_offset;
	float	x_tex;
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

#endif