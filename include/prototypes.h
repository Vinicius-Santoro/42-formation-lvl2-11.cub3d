/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:50:48 by ldatilio          #+#    #+#             */
/*   Updated: 2023/02/19 00:19:32 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "cub3D.h"

int		read_map(int fd, t_data *data);
void	check_line(char *line, t_data *data);
void	parse_map(t_data *data);
void	make_image(t_data *data);
void	make_vertical_line(t_data *data, int dist, double ix, t_img_data *img);
void	raycast(t_data *data, double ra);
double	get_distance(t_data *data, double ra);

int		close_game(t_data *data);
void	error_message(int error_code, char *message_error, t_data *data);
void	free_matrix(char **matrix);

int		ft_run(t_data *data);
int		arrows_up(int keycode, t_data *data);
int		arrows_down(int keycode, t_data *data);

char	*ft_strjoin_free(char *s1, char const *s2);
int		ft_strisdigit(char *str);
int		is_valid_ext(char *file, const char *ext);
void	get_fps(t_data *data);
int     mouse_move(int x, int y, t_data *data);

#endif