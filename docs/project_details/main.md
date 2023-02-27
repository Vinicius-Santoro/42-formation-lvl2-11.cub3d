### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>


- Funções deste arquivo:
```c
int					main(int argc, char **argv);
static int			validate_map(char *file_name, t_data *data);
static void			init_game(t_data *data);
static t_img_data	*init_texture(char *file, t_data *data);
```

<h1></h1>

- Descrição: iniciliza o jogo.
- Parâmetro: `int argc` - quantidade de argumentos passados na linha de comando.
- Parâmetro: `char **argv` - argumentos passados na linah de comando.
```c
int	main(int argc, char **argv)
{
	t_data	*data;

	/* Verifica se o número de argumentos passados é inválido */
	if (argc > 2)
		error_message(1, "Invalid arguments: too many", data);
	if (argc < 2)
		error_message(2, "Invalid arguments: not enough", data);

	/* Aloca espaço na memória para o struct de dados */
	data = malloc(sizeof(t_data));

	/* Verifica se o arquivo do mapa é válido */
	if (validate_map(argv[1], data) == TRUE)
		return (1);
	/* Inicializa o jogo */
	init_game(data);

	/* Cria a imagem */
	make_image(data);
	
	/* Configura a rotina que será executada a cada atualização de tela
	- mlx: ponteiro para o contexto da biblioteca MLX.
	- ft_run: função callback que será chamada sempre que o evento de loop ocorrer
	- data: elementos da struct data que serão passados para a função callback
	ft_run sempre que ela for chamada.
	*/
	mlx_loop_hook(data->mlx, ft_run, data);
	
	/* Função chamada quando uma tecla é pressionada
	- data->win: é um ponteiro para a janela MLX que registra o evento.
	- KEYPRESS: é um identificador de pressionar a tecla.
	- KEYPRESSMASK: é um edentificador para caputurar as teclas pressionadas.
	- arrows_down: função calback de quando a tecla é pressioanda.
	- data:   é um ponteiro para os dados que serão passados para a função de
	callback arrows_down.
	*/
	mlx_hook(data->win, KEYPRESS, KEYPRESSMASK, arrows_down, data);
	
	/* Função chamada quando uma tecla é solta
	- data->win: é um ponteiro para a janela MLX que registra o evento.
	- KEYRELEASE: tipo de evento que será capturado. Neste caso, é o evento de
	liberação de uma tecla.
	- KEYRELEASEMASK: é uma máscara que especifica o tipo de evento que será
	capturado.
	- arrows_up: é a função de callback que será chamada quando o evento de
	liberação de tecla for detectado.
	- data: é um ponteiro para os dados que serão passados para a função de
	callback arrows_up.
	*/
	mlx_hook(data->win, KEYRELEASE, KEYRELEASEMASK, arrows_up, data);
	
	/* Função chamada ao fechar a janela
	- data->win: é um ponteiro para a janela MLX que registra o evento.
	- DESTROYNOTIFY: especifica o tipo de evento que o hook deve interceptar.
	DESTROYNOTIFY é um valor inteiro definido na biblioteca X11 que representa 
	o evento de destruição da janela. Quando essa janela é fechada, o hook será
	ativado.
	- NOEVENTMASK: especifica a máscara de eventos que deve ser usada para
	registrar o hook. NOEVENTMASK é um valor inteiro que representa uma máscara
	vazia, o que significa que o hook só será ativado para o evento especificado
	no segundo parâmetro.
	- close_game: Este parâmetro é um ponteiro para uma função que será chamada
	quando o evento especificado ocorrer. Neste caso, a função close_game será
	chamada quando a janela for fechada. Essa função é responsável por
	desalocar todos os recursos utilizados pelo programa antes de encerrá-lo.
	- data: Este parâmetro é um ponteiro para um bloco de dados personalizado
	que é passado para a função close_game. Esse bloco de dados pode conte
	informações sobre o estado atual do jogo ou outras informações relevantes
	este caso, o bloco de dados é passado para a função close_game para
	garantir que todos os recursos sejam liberados corretamente.
	*/
	mlx_hook(data->win, DESTROYNOTIFY, NOEVENTMASK, close_game, data);
	
	/* Função chamada para movimentação pelo mouse
	- data->win: é um ponteiro para a janela MLX que registra o evento.
	- 6: Este parâmetro especifica o tipo de evento que o hook deve interceptar.
	 O valor 6 representa o evento de movimento do mouse (MotionNotify)
	 na biblioteca gráfica X11.
	- 64: Este parâmetro especifica a máscara de eventos que deve ser usada para
	 registrar o hook. O valor 64 representa a máscara de evento
	 PointerMotionMask na biblioteca gráfica X11. Essa máscara especifica que o
	 hook deve ser ativado somente quando ocorrer um evento de movimento do
	 mouse.
	- mouse_move: Este parâmetro é um ponteiro para uma função que será chamada
	quando o evento especificado ocorrer. Neste caso, a função mouse_move será
	chamada quando o evento de movimento do mouse ocorrer. Essa função é
	responsável por atualizar a posição do cursor do mouse na janela gráfica ou
	executar outras ações relevantes.
	- data: Este parâmetro é um ponteiro para um bloco de dados personalizado
	que é passado para a função mouse_move. Esse bloco de dados pode conter
	informações sobre o estado atual do jogo ou outras informações relevantes.
	Neste caso, o bloco de dados é passado para a função mouse_move para que
	ela possa atualizar a posição do cursor do mouse na janela gráfica com base
	nesses dados.
	*/
	mlx_hook(data->win, 6, 64, mouse_move, data);

	/* Loop principal da biblioteca mlx */
	mlx_loop(data->mlx);
	return (0);
}
```

<h1></h1>

- Descrição: valida se a extensão do arquivo do mapa é `.cub`,
faz a leitura do mapa e analisa se o conteúdo do mapa é valido ou não.
- Parâmetro: `char *file_name` - arquivo que será analisado.
- Parâmetro: `t_data *data` - ponteiro para o arquivo que será analisado.

```c
static int	validate_map(char *file_name, t_data *data)
{
	/*
	Variável para armazenar o retorno que teremos na tentativa de abertura do
	arquivo.
	*/
	int	fd;

	/*
	Retorno que teremos na tentativa de abertura do arquivo.
	A função open retorna -1 em caso de erro.
	*/
	fd = open(file_name, RDWR);
	if (fd < 0)
		error_message(3, "Invalid file: not exist", data);
		
	/* Verificação da extensão do arquivo. */
	if (is_valid_ext(file_name, ".cub") == FALSE)
		error_message(4, "Invalid file extension: not .cub", data);
		
	/* Função para ler o mapa. */
	read_map(fd, data);
	
	/* Função para analisar o mapa e o conteúdo do arquivo. */
	parse_map(data);
	
	/* Fechamento do file descriptor. */
	close(fd);
	return (0);
}
```

<h1></h1>

- Descrição: inicializa o jogo.
- Parâmetro: `t_data *data` - ponteiro para as variáveis do jogo.
```c
void	init_game(t_data *data)
{
	/* Inicialização da biblioteca MLX */
	data->mlx = mlx_init();
	
	/* Criação da janela com tamanho 512 x 512 e título "Cub3d" */
	data->win = mlx_new_window(data->mlx, WINDOW_SIZE, WINDOW_SIZE, "Cub3d");
	
	/* Inicialização das texturas "no", "so", "we" e "ea" */
	data->img.no = init_texture(data->map.tex.no, data);
	data->img.so = init_texture(data->map.tex.so, data);
	data->img.we = init_texture(data->map.tex.we, data);
	data->img.ea = init_texture(data->map.tex.ea, data);
	
	/* Inicialização das ações do jogador */
	data->move_up = 0;
	data->move_down = 0;
	data->move_left = 0;
	data->move_right = 0;
	
	/* Campo de visão a esquerda e a direita */
	data->turn_left = 0;
	data->turn_right = 0;
	
	/* Inicialização de variáveis para contagem de tempo */
	data->last_sec = 0;
	data->last_fps = 0;
	data->count_frame = 0;
	
	/* Inicialização da string para exibição dos fps */
	data->str_fps = ft_strdup("");
}
```

<h1></h1>

- Descrição: inicializa as texturas a partir do arquivo `xpm`. Ela retorna um
ponteiro para uma estrutura `t_img_data`, que contém informações sobre a imagem,
como o endereço dos dados da imagem, o número de bits por pixel, o comprimento
da linha e o endianess.
- Parâmetro: `char *file` - arquivo que contém as texturas (.xpm).
- Parâmetro: `t_data *data` - utuliza essa variável para comseguir acesso a
minilibx.
```c
t_img_data	*init_texture(char *file, t_data *data)
{
	/*
	Ponteiro para estrutura "t_img_data".
	t_img_data ret;
	*/
	t_img_data	*ret;


	/* Variável "trash" para descartar informações desnecessárias. */
	int trash;

	/* Aloca memória para a estrutura "t_img_data". */
	ret = malloc(sizeof(t_img));

	/*
	Carrega a imagem a partir do arquivo fornecido.
	- mlx: um ponteiro para a estrutura mlx que contém informações gerais sobre
	a janela gráfica.
	- file: uma string que representa o caminho para o arquivo de imagem.
	- trash: width - um ponteiro para um inteiro que será preenchido com a
	largura da imagem.
	- trash: height - um ponteiro para um inteiro que será preenchido com o
	comprimento da imagem.
	*/
	ret->new_img = mlx_xpm_file_to_image(data->mlx, file, &trash, &trash);

	/*
	Obtém o endereço dos dados da imagem.
	- image: um ponteiro para a estrutura mlx_img que representa a imagem.
	- bits_per_pixel: um ponteiro para um inteiro que será preenchido com o
	número de bits por pixel da imagem.
	- line_length: um ponteiro para um inteiro que será preenchido com o
	comprimento da linha da imagem (em bytes).
	- endian: um ponteiro para um inteiro que será preenchido com o endianess
	da imagem (0 para little-endian, 1 para big-endian).
	O endian serve para ler o endereço da imagem.
	*/
	ret->address = mlx_get_data_addr(ret->new_img, &ret->bits_per_pixel, \
	&ret->line_length, &ret->endian);

	/* Retorna o ponteiro para a estrutura "t_img_data" */
	return (ret);
}
```