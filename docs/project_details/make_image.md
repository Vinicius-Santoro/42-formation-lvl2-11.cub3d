### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https:github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

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

<h1></h1>

- Descrição: desenha uma linha vertical na tela correspondente ao plano 3D. A
altura da linha é determinada pela distância do sprite em relação ao jogador.
- Parâmetro: `t_data *data` - quantidade de argumentos passados na linha de
comando.
- Parâmetro: `int dist` - distância do sprite em relação ao jogador.
- Parâmetro: `double ix`- posição horizontal da coluna na tela em que a sprite
será desenhada.
- Parâmetro: `t_img_data *img` - ponteiro para a estrutura `t_img_data` que
contém informações sobre a textura da sprite.
```c
void	make_vertical_line(t_data *data, int dist, double ix, t_img_data *img)
{
	/* A altura do teto em relação à linha é inicializada com 0 */
	data->rc.y_ceil = 0;

	/* Se a distância entre o jogador e o ponto de intersecção do raio com o
	mapa for 0, ela é definida como 1 para evitar divisão por 0. */
	if (dist == 0)
		dist = 1;

	/* A altura da linha na tela é calculada a partir da distância, tamanho do
	sprite e tamanho da janela. */
	data->rc.line_height = (SPRITE_SIZE * WINDOW_SIZE) / dist;

	/* O tamanho da textura na coordenada y é calculado em função da altura da
	linha e do tamanho do sprite. */
	data->rc.y_tex_step = SPRITE_SIZE / (float)data->rc.line_height;

	/* O deslocamento na coordenada y é definido como 0 */
	data->rc.y_tex_offset = 0;

	/* Se a altura da linha for maior que a altura da janela, é necessário
	definir um deslocamento para que a textura seja centralizada na linha
	vertical. */
	if (data->rc.line_height > WINDOW_SIZE)
	{
		data->rc.y_tex_offset = (data->rc.line_height - WINDOW_SIZE) / 2.0;
		data->rc.line_height = WINDOW_SIZE;
	}

	/* O deslocamento na coordenada y da linha em relação ao topo da janela é
	calculado. */
	data->rc.line_offset = WINDOW_SIZE / 2 - data->rc.line_height / 2;

	/* O valor máximo da coordenada y é definido como o deslocamento mais a
	altura da linha. */
	data->rc.y_max = data->rc.line_offset + data->rc.line_height;

	/* O número da coluna de pixels da textura que será usada para desenhar a
	linha é calculado a partir da posição horizontal do ponto de intersecção.*/
	data->rc.x_tex = (int)(ix) % SPRITE_SIZE;

	/* Se a imagem for uma textura do sul ou do oeste, o valor de x_tex 
	precisa ser ajustado para desenhar a textura corretamente. */
	if (img == data->img.so || img == data->img.we)
		data->rc.x_tex -= SPRITE_SIZE - 1;

	/* O valor da coordenada y da textura é definido como o deslocamento vezes o
	tamanho da textura na coordenada y. */
	data->rc.y_tex = data->rc.y_tex_offset * data->rc.y_tex_step;

	/* Finalmente, a linha vertical é desenhada na imagem. */
	put_vertical_line(data, img);

	/* Resumidamente, a função make_vertical_line cria a linha e a
	put_vertical_line coloca a linha. */
}
```

<h1></h1>

- Descrição: desenha uma linha vertical na tela correspondente ao plano 3D. A
altura da linha é determinada pela distância do sprite em relação ao jogador.
- Parâmetro: `t_data *data` - quantidade de argumentos passados na linha de
comando.
- Parâmetro: `t_img_data *img` - ponteiro para a estrutura `t_img_data` que
contém informações sobre a textura da sprite.
```c
static void	put_vertical_line(t_data *data, t_img_data *img)
{
	/* Desenha a porção de teto acima da linha vertical atual */
	while (data->rc.y_ceil <= data->rc.line_offset)
	{
		 /* Calcula a coordenada x inicial da linha vertical atual */
		data->rc.x = (data->ray_num * SPRITE_SCALE);

		/* Desenha cada pixel da porção de teto acima da linha vertical atual */
		while (data->rc.x < (data->ray_num * SPRITE_SCALE) + SPRITE_SCALE)
		{
			/* Desenha um pixel com a cor do teto na posição atual */
			put_pixel_img(data->img.game, data->rc.x, data->rc.y_ceil, data->map.color.ceil);

			/* Avança para o próximo pixel */
			data->rc.x++;
		}
		/* Avança para a próxima linha vertical */
		data->rc.y_ceil++;
	}
	
	/* Desenha a coluna vertical atual */
	while (data->rc.line_offset <= data->rc.y_max)
	{
		/* Calcula a coordenada x inicial da linha vertical atual */
		data->rc.x = (data->ray_num * SPRITE_SCALE);

		/* Desenha cada pixel da coluna vertical atual */
		while (data->rc.x < (data->ray_num * SPRITE_SCALE) + SPRITE_SCALE)
		{
			/* Calcula as coordenadas de textura do pixel atual na coluna vertical */
			int x_tex = (int)data->rc.x_tex;
			int y_tex = (int)data->rc.y_tex;

			/* Desenha um pixel com a cor da textura na posição atual */
			put_pixel_img(data->img.game, data->rc.x, data->rc.line_offset, get_pixel_img(img, x_tex, y_tex));

			/* Avança para o próximo pixel e para as próximas coordenadas de textura */
			data->rc.x++;
			data->rc.y_tex += data->rc.y_tex_step;
		}
		/* Avança para a próxima linha vertical */
		data->rc.line_offset++;
	}
	
	/* Desenha a porção de chão abaixo da linha vertical atual */
	while (data->rc.y_max <= WINDOW_SIZE)
	{
		/* alcula a coordenada x inicial da linha vertical atual */
		data->rc.x = (data->ray_num * SPRITE_SCALE);
		/* Desenha cada pixel da porção de chão abaixo da linha vertical atual */
		while (data->rc.x < (data->ray_num * SPRITE_SCALE) + SPRITE_SCALE)
		{
			/* Desenha um pixel com a cor do chão na posição atual */
			put_pixel_img(data->img.game, data->rc.x, data->rc.y_max, data->map.color.floor);
			 /* Avança para o próximo pixel */

			data->rc.x++;
		}
		/* Avança para a próxima linha vertical */
		data->rc.y_max++;
	}
}

```

<h1></h1>

- Descrição: coloca um pixel na posição (x, y) da imagem representada por img, com a cor especificada por color.
- Parâmetro: `t_img_data *img` - ponteiro para a estrutura `t_img_data` que
contém informações sobre a textura da sprite.
- Parâmetro: `int x` - cordenada x.
- Parâmetro: `int y` - cordenada x.
- Parâmetro: `int color` - cordenada x.
```c
static void	put_pixel_img(t_img_data *img, int x, int y, int color)
{
	char	*byte;

	/* 
	- address: é o endereço base da imagem
	- line_length: comprimento da linha em bytes.
	- bits_per_pixel: número de bits por pixel.

	- O resultado dessa expressão é adicionado ao endereço base da imagem img->address, obtendo-se o endereço do byte que representa a posição (x, y) da imagem.
	- Finalmente, a função converte o endereço do byte para um ponteiro de inteiro sem sinal, permitindo que o valor da cor color seja gravado na posição (x, y) da imagem.
	*/
	byte = img->address + ((y * img->line_length)
			+ (x * img->bits_per_pixel / SPRITE_SCALE));
	*(unsigned int *)byte = color;
}
```

<h1></h1>

- Descrição: obtém o valor de cor de um pixel em uma determinada posição (x, y).
- Parâmetro: `t_img_data *img` - ponteiro para a estrutura `t_img_data` que
contém informações sobre a textura da sprite.
- Parâmetro: `int x` - cordenada x.
- Parâmetro: `int y` - cordenada x.
```c
static int	get_pixel_img(t_img_data *img, int x, int y)
{
	char	*byte;

	/* 
	- address: é o endereço base da imagem
	- line_length: comprimento da linha em bytes.
	- bits_per_pixel: número de bits por pixel.

	- O resultado dessa expressão é adicionado ao endereço base da imagem img->address, obtendo-se o endereço do byte que representa a posição (x, y) da imagem.
	- Finalmente, a função converte o endereço do byte para um ponteiro de inteiro sem sinal, permitindo que o valor da cor color seja gravado na posição (x, y) da imagem.
	*/
	byte = img->address + ((y * img->line_length)
			+ (abs(x * img->bits_per_pixel / SPRITE_SCALE)));

	/* Retorna o valor inteiro da cor do pixel encontrado. */
	return (*(unsigned int *)byte);
}
```