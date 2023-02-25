### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>

- Funções deste arquivo:
```c
void		make_image(t_data *data);
void		make_vertical_line(
				t_data *data, int dist, double ix, t_img_data *img);
static void	put_vertical_line(t_data *data, t_img_data *img);
static void	put_pixel_img(t_img_data *img, int x, int y, int color);
static int	get_pixel_img(t_img_data *img, int x, int y);
```

<h1></h1>

- Descrição: é responsável por renderizar a imagem do jogo na janela gráfica.
- Parâmetro: `t_data *data` - quantidade de argumentos passados na linha de
comando.
```c
void	make_image(t_data *data)
{
	/* Função que atualiza a posição do mouse */
	mouse_move(0, 0, data);


	/* Alocando espaço para a imagem do jogo */
	data->img.game = malloc(sizeof(t_img));

	/* Criando uma nova imagem do jogo com a biblioteca mlx
	- data->mlx: apontamento para minilibx.
	- WINDOW_SIZE: largura da janela.
	- WINDOW_SIZE: comprimento da janela.
	*/
	data->img.game->new_img = mlx_new_image(data->mlx, WINDOW_SIZE, WINDOW_SIZE);

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
	data->img.game->address = mlx_get_data_addr(data->img.game->new_img,
	&data->img.game->bits_per_pixel
	&data->img.game->line_length,
	&data->img.game->endian);

	/* Definindo o ângulo do raio a partir da posição do jogador na tela
	- data->player.angle: é o ângulo atual do jogador em radianos.
	*/
	data->ra = data->player.angle + (PI / 180 * SPRITE_SIZE / 2);

	/* Inicializando o número de raycastings traçados */
	data->ray_num = 0;

	/* Laço que traça raios em todas as colunas da tela */
	while (data->ray_num < SPRITE_SIZE)
	{
		/* Chamando a função de raycasting */
		raycast(data, data->ra);

		/* Atualizando o ângulo do raio para a próxima coluna */
		data->ra -= PI / 180;

		/* Incrementando o número de raios traçados */
		data->ray_num++;
	}

	/* Colocando a imagem do jogo na janela 
	- mlx: ponteiro para a conexão mlx retornada pela função mlx_init().
	- win: ponteiro para a janela onde a imagem será desenhada.
	- img: ponteiro para a imagem a ser desenhada.
	- x: coordenada horizontal do canto superior esquerdo da imagem na janela.
	- y: coordenada vertical do canto superior esquerdo da imagem na janela.
	A função está sendo usada para desenhar a imagem data->img.game->new_img na
	janela data->win, posicionando-a no canto superior esquerdo da janela, ou
	seja, na coordenada (0,0).

	*/
	mlx_put_image_to_window(data->mlx, data->win, data->img.game->new_img, 0, 0);

	/* Destruindo a imagem criada com a mlx */
	mlx_destroy_image(data->mlx, data->img.game->new_img);

	/* Liberando a memória alocada para a imagem do jogo */
	free(data->img.game);

	/* Chamando a função que calcula e exibe o FPS na tela */
	get_fps(data);

}
```
