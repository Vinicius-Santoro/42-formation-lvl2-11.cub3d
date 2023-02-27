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
MAP_NAME		=	./assets/maps/map42.cub

HEADER			=	cub3D.h
INCLUDE			=	-I ./include

CC				=	gcc -g
CFLAGS			=	-Wall -Wextra -Werror
LIB				=	-lbsd -lmlx -lXext -lX11 -lm -lz
VAL_FLAGS		= 	--leak-check=full --show-leak-kinds=all

SRC_PATH		=	./src/
OBJ_PATH		=	./obj/

SRC_FILES		=	main.c			\
					check_line.c	\
					commands.c		\
					end_game.c		\
					make_image.c	\
					parse_map.c		\
					read_map.c		\
					raycast.c		\
					utils.c

SRC            	=	$(addprefix $(SRC_PATH),$(SRC_FILES))
OBJ            	=	$(addprefix $(OBJ_PATH),$(subst .c,.o,$(SRC_FILES)))

all:            $(NAME)
				
LIBFT			=	./libs/libft/libft.a

$(NAME):        $(OBJ) $(LIBFT)
				@ $(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJ) $(LIB) $(LIBFT)
				@ echo "$(CUB)$(RE): was $(GREEN)created$(RE)"
				

$(LIBFT): 
				@ make bonus --no-print-directory -C ./libs/libft

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
				@ mkdir -p $(OBJ_PATH)
				@ $(CC) $(INCLUDE) -c $< -o $@


clean:
				@ $(RM) rm -rf $(OBJ_PATH)
				@ make clean --no-print-directory -C ./libs/libft
				@ echo "$(CUB): object files were $(RED)deleted$(RE)"

fclean:         clean
				@ $(RM) $(NAME) rm -rf  $(LIBFT) $(OBJ_PATH)
				@ echo "$(CUB): was $(RED)deleted$(RE)"

re:				fclean all

play:			re
				@ echo "$(CUB): was $(GREEN)started$(RE)"
				@ ./$(NAME) $(MAP_NAME)

val:			re
				valgrind $(VAL_FLAGS) ./$(NAME) $(MAP_NAME)

.PHONY:			all, clean, fclean, re, play, val
