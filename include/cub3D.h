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
# include <sys/time.h>

# include "../libs/libft/libft.h"
# include "structs.h"
# include "prototypes.h"

# define FALSE 0
# define TRUE 1
# define MAX_INT 2147483647

# define PI 3.1415926535
# define SPRITE_LEN 64
# define WINDOW_SIZE 512

# define KEYPRESSMASK 1
# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYRELEASEMASK 10
# define DESTROYNOTIFY 17
# define NOEVENTMASK 0L

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RE "\033[0m"

#endif
