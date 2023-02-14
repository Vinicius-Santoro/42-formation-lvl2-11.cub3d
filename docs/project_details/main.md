### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>

- Descrição: valida se a extensão do arquivo do mapa é `.cub`,
faz a leitura do mapa e analisa se o conteúdo do mapa é valido ou não.
- Parâmetro: `char *file_name` - arquivo que será analisado.
- Parâmetro: `t_data *data` - arquivo que será analisado.

```c
int	validate_map(char *file_name, t_data *data)
{
	/*
	Variável para armazenar o retorno que teremos na tentativa de abertura do arquivo.
	*/
	int	fd;

	/*
	Retorno que teremos na tentativa de abertura do arquivo.
	A função open retorna -1 em caso de erro.
	*/
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_message(3, "Invalid file: not exist", data);
		
	/*
	Verificação da extensão do arquivo.
	*/
	if (is_valid_ext(file_name, ".cub") == FALSE)
		error_message(4, "Invalid file extension: not .cub", data);
		
	/*
	Função para ler o mapa.
	*/
	read_map(fd, data);
	
	/*
	Função para analisar o mapa e o conteúdo do arquivo.
	*/
	parse_map(data);
	
	/*
	Fechamento do file descriptorç.
	*/
	close(fd);
	return (0);
}
```

- Descrição: inicializa as texturas a partir do arquivo `xpm`. Ela retorna um ponteiro para uma estrutura "t_img_data", que contém informações sobre a imagem, como o endereço dos dados da imagem, o número de bits por pixel, o comprimento da linha e o endianess.
- Parâmetro: `char *file` - arquivo que contém as texturas (.xpm).
- Parâmetro: `t_data *data` - utuliza essa variável para comseguir acesso a minilibx.
```c
t_img_data	*init_texture(char *file, t_data *data)
{
	/*
	Variável "trash" para descartar informações desnecessárias.
	*/
	int trash;
	
	/*
	Ponteiro para estrutura "t_img_data".
	t_img_data ret;
	*/

	/*
	Aloca memória para a estrutura "t_img_data".
	*/
	ret = malloc(sizeof(t_img));

	/*
	Carrega a imagem a partir do arquivo fornecido.
	"mlx": um ponteiro para a estrutura "mlx" que contém informações gerais sobre a janela gráfica.
	"file": uma string que representa o caminho para o arquivo de imagem.
	"trash": width - um ponteiro para um inteiro que será preenchido com a largura da imagem.
	"trash": height - um ponteiro para um inteiro que será preenchido com o comprimento da imagem.
	*/
	ret->new_img = mlx_xpm_file_to_image(data->mlx, file, &trash, &trash);

	/*
	Obtém o endereço dos dados da imagem.
	"image": um ponteiro para a estrutura "mlx_img" que representa a imagem.
	"bits_per_pixel": um ponteiro para um inteiro que será preenchido com o número de bits por pixel da imagem.
	"line_length": um ponteiro para um inteiro que será preenchido com o comprimento da linha da imagem (em bytes).
	"endian": um ponteiro para um inteiro que será preenchido com o endianess da imagem
	(0 para little-endian, 1 para big-endian).
	O endian serve para ler o endereço da imagem.
	*/
	ret->address = mlx_get_data_addr(ret->new_img, &ret->bits_per_pixel, &ret->line_length, &ret->endian);

	// Retorna o ponteiro para a estrutura "t_img_data"
	return (ret);
}
```

```c
void	init_game(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WINDOW_SIZE, WINDOW_SIZE, "Cub3d");
	data->img.no = init_texture(data->map.tex.no, data);
	data->img.so = init_texture(data->map.tex.so, data);
	data->img.we = init_texture(data->map.tex.we, data);
	data->img.ea = init_texture(data->map.tex.ea, data);
	data->turn_left = 0;
	data->turn_right = 0;
	data->move_up = 0;
	data->move_down = 0;
	data->move_left = 0;
	data->move_right = 0;
	data->last_sec = 0;
	data->last_fps = 0;
	data->count_frame = 0;
	data->str_fps = ft_strdup("");
}
```


```c
int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc > 2)
		error_message(1, "Invalid arguments: too many", data);
	if (argc < 2)
		error_message(2, "Invalid arguments: not enough", data);
	data = malloc(sizeof(t_data));
	if (validate_map(argv[1], data) == TRUE)
		return (1);
	init_game(data);
	make_image(data);
	mlx_loop_hook(data->mlx, ft_run, data);
	mlx_hook(data->win, KEYPRESS, KEYPRESSMASK, arrows_down, data);
	mlx_hook(data->win, KEYRELEASE, KEYRELEASEMASK, arrows_up, data);
	mlx_hook(data->win, 17, 0L, close_game, data);
	mlx_loop(data->mlx);
	return (0);
}
```
