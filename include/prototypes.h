/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldatilio <ldatilio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:50:48 by ldatilio          #+#    #+#             */
/*   Updated: 2023/02/13 21:50:49 by ldatilio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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