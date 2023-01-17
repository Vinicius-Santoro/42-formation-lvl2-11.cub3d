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
# define INVALID_ARGV GREEN "\
┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━┓\n\
┃" RED "ERROR:" RE " " GREEN "You must specify at least 4 or 5 arguments┃  Rules ┃\n\
┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃━━━━━━━━┃\n\
┃ - [1] number_of_philosophers                    ┃  >  0  ┃\n\
┃ - [2] time_to_die                               ┃  >= 0  ┃\n\
┃ - [3] time_to_eat                               ┃  >= 0  ┃\n\
┃ - [4] time_to_sleep                             ┃  >= 0  ┃\n\
┃ - [5] number_of_times_each_philosopher_must_eat ┃  >= 0  ┃\n\
┃ - Obs: Argument 5 is optional.                  ┃   --   ┃\n\
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━┛\n" RE
int     validate_map(char *file_name);
void    verify_arguments(int argc);

#endif