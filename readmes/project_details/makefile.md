### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>

- O makefile é um arquivo de texto que contém instruções para o programa, que automatiza o processo de compilação de um projeto de software escrito em C. Ele especifica quais arquivos de código-fonte devem ser compilados, quais bibliotecas devem ser incluídas e quais opções de compilação devem ser usadas.

```Makefile
# Definindo as cores para utilizar na printagem do terminal.
RED 			=	\033[0;31m
GREEN 			=	\033[0;32m
YELLOW 			=	\033[0;33m
BLUE 			=	\033[0;34m
MAGENTA 		=	\033[0;35m
MAGENTA_2		=	\033[0;95m
CYAN 			=	\033[0;36m
RE 			=	\033[0m

# Nome do arquivo gerado que utilizaremos para a compilação.
NAME			=	cub3D
HEADER			=	cub3D.h

# Especificando o diretório do arquivo header.
INCLUDE			=	-I ./include

# Coleção de compiladores- GNU Compiler Collection
CC			=	gcc

# Flags especificadas pela 42
CFLAGS			=	-Wall -Wextra -Werror

# -lsbd: utilizar a biblioteca "libsbd", que contém funções e estruturas de dados a usadas pelo programa.
# -lmlx: utilizar a biblioteca "libmlx", que é geralmente utilizada no desenvolvimento de programas gráficos com a biblioteca gráfica MinilibX. Ela fornece uma interface simplificada para a biblioteca gráfica X11, permitindo acesso a recursos gráficos como janelas, imagens e eventos de entrada.
# -lXext: utilizar funções adicionais para acessar recursos como janelas transparentes, suporte a multi-tela e suporte ao protocolo X Shape
# -lX11: uma das bibliotecas fundamentais para o desenvolvimento de programas gráficos no ambiente Unix.
# -lm: utilizar a biblioteca "libm", que fornece funções matemáticas. Ela contém funções para realizar operações matemáticas como arredondamento, exponenciação, logaritmos, trigonometria e outras operações matemáticas básicas e avançadas. 
# -lz: utilizar a biblioteca chamada "libz" que fornece funções para compactar e descompactar dados.

LIB			=	-lbsd -lmlx -lXext -lX11 -lm -lz

# Organizando caminhos dos diretórios.
SRC_PATH		=	./src/
OBJ_PATH		=	./obj/

# Organizando arquivos abstratos
SRC_FILES		=	main.c			\
				validate_map.c	\
				validate_error.c\
				utils.c

# Compilando os arquivos abstratos e transformando-os em arquivos objetos.
SRC            		=	$(addprefix $(SRC_PATH),$(SRC_FILES))
OBJ            		=	$(addprefix $(OBJ_PATH),$(subst .c,.o,$(SRC_FILES)))

CUB			=	$(MAGENTA_2)cub$(BLUE)3$(RED)D$(RE)

LIBFT			=	./libs/libft/libft.a

$(LIBFT): 
			@ make bonus --no-print-directory -C ./libs/libft

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
			@ mkdir -p $(OBJ_PATH)
			@ $(CC) $(INCLUDE) -c $< -o $@

# Quando executarmos 'make all', o programa irá criar o executável dos arquivos definidos.
all:            $(NAME)
				

$(NAME):        $(OBJ) $(LIBFT)
		@ $(CC) -o $(NAME) $(OBJ) $(LIBFT)
		@ echo "$(CUB)$(RE): was $(GREEN)created$(RE)"

# Removendo arquivos objetos.
clean:
		@ $(RM) rm -rf $(OBJ_PATH)
		@ make clean --no-print-directory -C ./libs/libft
		@ echo "$(CUB): object files were $(RED)deleted$(RE)"

# Removendo arquivos objetos e o binário criado.
fclean:         clean
		@ $(RM) $(NAME) rm -rf  $(LIBFT) $(OBJ_PATH)
		@ echo "$(CUB): was $(RED)deleted$(RE)"

# Reconpilando o projeto.
re:		fclean all
```
