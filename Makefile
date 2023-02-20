# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 20:01:04 by vnazioze          #+#    #+#              #
#    Updated: 2023/02/15 08:24:54 by ldatilio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED 			=	\033[0;31m
GREEN 			=	\033[0;32m
YELLOW 			=	\033[0;33m
BLUE 			=	\033[0;34m
MAGENTA 		=	\033[0;35m
MAGENTA_2		=	\033[0;95m
CYAN 			=	\033[0;36m
RE 				=	\033[0m

CUB				=	$(MAGENTA)cub$(BLUE)3$(RED)D$(RE)

NAME			=	cub3D
NAME_BONUS		=	cub3D_bonus
MAP_NAME		=	./assets/maps/map42.cub

HEADER			=	cub3D.h
HEADER_BONUS	=	cub3D_bonus.h
INCLUDE			=	-I ./mandatory/include/
INCLUDE_BONUS	=	-I ./bonus/include/

CFLAGS			=	-Wall -Wextra -Werror
CC				=	gcc -g $(CFLAGS) 
LIB				=	-lbsd -lmlx -lXext -lX11 -lm -lz
VAL_FLAGS		= 	--leak-check=full --show-leak-kinds=all

SRC_PATH		=	./mandatory/src/
OBJ_PATH		=	./mandatory/obj/

SRC_PATH_BONUS	=	./bonus/src/
OBJ_PATH_BONUS	=	./bonus/obj/

SRC_FILES		=	main.c			\
					check_line.c	\
					commands.c		\
					end_game.c		\
					make_image.c	\
					parse_map.c		\
					read_map.c		\
					raycast.c		\
					utils.c

SRC_FILES_BONUS	=	main_bonus.c		\
					check_line_bonus.c	\
					commands_bonus.c	\
					end_game_bonus.c	\
					make_image_bonus.c	\
					parse_map_bonus.c	\
					read_map_bonus.c	\
					raycast_bonus.c		\
					utils_bonus.c

SRC				=	$(addprefix $(SRC_PATH),$(SRC_FILES))
OBJ				=	$(addprefix $(OBJ_PATH),$(subst .c,.o,$(SRC_FILES)))

SRC_BONUS		=	$(addprefix $(SRC_PATH_BONUS),\
					$(SRC_FILES_BONUS))
OBJ_BONUS		=	$(addprefix $(OBJ_PATH_BONUS),\
					$(subst .c,.o,$(SRC_FILES_BONUS)))

LIBFT			=	./libs/libft/libft.a

$(LIBFT): 
				@ make bonus --no-print-directory -C ./libs/libft

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
				@ mkdir -p $(OBJ_PATH)
				@ $(CC) $(INCLUDE) -c $< -o $@

$(OBJ_PATH_BONUS)%.o:	$(SRC_PATH_BONUS)%.c
				@ mkdir -p $(OBJ_PATH_BONUS)
				@ $(CC) $(INCLUDE_BONUS) -c $< -o $@

all:			$(NAME)
				
$(NAME):		$(OBJ) $(LIBFT)
				@ $(CC) $(INCLUDE) -o $(NAME) $(OBJ) $(LIB) $(LIBFT)
				@ echo "$(CUB): was $(GREEN)created$(RE)"

bonus:			$(NAME_BONUS)

$(NAME_BONUS):	$(OBJ_BONUS) $(LIBFT)
				@ $(CC) $(INCLUDE_BONUS) -o $(NAME_BONUS) \
				$(OBJ_BONUS) $(LIB) $(LIBFT)
				@ echo "$(CUB): was $(GREEN)created$(RE)"

clean:
				@ rm -rf $(OBJ_PATH) $(OBJ_PATH_BONUS)
				@ make clean --no-print-directory -C ./libs/libft
				@ echo "$(CUB): object files were $(RED)deleted$(RE)"

fclean:			clean
				@ rm -rf $(NAME) $(NAME_BONUS) $(LIBFT)
				@ echo "$(CUB): was $(RED)deleted$(RE)"

re:				fclean all

rebonus:		fclean bonus

play:			all
				@ echo "$(CUB): was $(GREEN)started$(RE)"
				@ ./$(NAME) $(MAP_NAME)

val:			all
				valgrind $(VAL_FLAGS) ./$(NAME) $(MAP_NAME)

play_bonus:		bonus
				@ echo "$(CUB): was $(GREEN)started$(RE)"
				@ ./$(NAME_BONUS) $(MAP_NAME)

val_bonus:		bonus
				valgrind $(VAL_FLAGS) ./$(NAME_BONUS) $(MAP_NAME)

.PHONY:			all, clean, fclean, re, rebonus, \
				play, val, play_bonus, val_bonus
