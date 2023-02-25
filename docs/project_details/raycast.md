### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https:/*github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>


- Funções deste arquivo:
```c
void		raycast(t_data *data, double ra);
double		get_distance(t_data *data, double ra);
static void	get_deltadist(t_data *data, double ra);
static void	get_sidedist(t_data *data, double ra);
static void	collision_loop(t_data *data);
```

<h1></h1>

- Descrição: verifica o mapa, validando se é válido e recebe o campo de visão
inicial do jogador.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
void raycast(t_data *data, double ra)
{
	/* Variáveis para o ângulo do jogador e distância */
	double ca;
	double dist;

	/* Ajusta o ângulo se estiver fora do intervalo 0 - 2*PI */
	if (ra >= 2 * PI)
		ra -= 2 * PI;
	if (ra < 0)
		ra += 2 * PI;

	/* Zera a parede atual */
	data->wall = 0;

	/* Obtém a distância da parede mais próxima na direção do raio */
	dist = get_distance(data, ra);

	/* Calcula o ângulo de correção */
	ca = data->player.angle - ra;

	/* Aplica a correção para calcular a distância real */
	dist = dist * cos(ca);

	/* Verifica qual parede foi atingida e desenha uma linha vertical correspondente *;

    verifica se a parede está à esquerda ou à direita do jogador e se a parede
    está na metade `superior` da tela. Se a condição for verdadeira, a textura
    usada para desenhar a parede é data->img.ea, que representa a textura da
    parede vista de leste.
    */
	if (data->wall == 0 && (ra <= PI / 2 || ra >= 3 * PI / 2))
		make_vertical_line(data, dist, data->player.y - dist * sin(ra), data->img.ea);

    /* 
    Verifica se a parede está à esquerda ou à direita do jogador e se a parede
    está na metade `inferior` da tela. Se a condição for verdadeira, a textura
    usada para desenhar a parede é data->img.we, que representa a textura d
    parede vista de oeste.
    */
	else if (data->wall == 0)
		make_vertical_line(data, dist, data->player.y - dist * sin(ra), data->img.we);
    
    /*
    Verifica se a parede está acima ou abaixo do jogador e se a parede está na
    metade `direita` da tela. Se a condição for verdadeira, a textura usada para
    desenhar a parede é data->img.no, que representa a textura da parede vista
    de norte.
    */
	else if (data->wall == 1 && ra <= PI)
		make_vertical_line(data, dist, data->player.x + dist * cos(ra), data->img.no);

    /* 
    Caso contrário, a parede está na metade esquerda da tela, então a textura
    usada para desenhar a parede é data->img.so, que representa a textura da
    parede vista de sul.
    */    
	else
		make_vertical_line(data, dist, data->player.x + dist * cos(ra), data->img.so);
}
```

<h1></h1>

- Descrição: calcula a distância do jogador até a parede mais próxima em uma
determinada direção `ra`.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
- Parâmetro: `double ra` - ângulo de visão.
```c
double	get_distance(t_data *data, double ra)
{
	/* Normaliza o ângulo para o intervalo [0, 2*PI). */
	if (ra >= 2 * PI)
		ra -= 2 * PI;
	if (ra < 0)
		ra += 2 * PI;

	/* Calcula a diferença entre as distâncias em x e y dos pontos de
	colisão com as paredes mais próximas na direção do raio. */
	get_deltadist(data, ra);

	/* Calcula as distâncias em x e y do jogador até as paredes mais próximas
	na direção do raio. */
	get_sidedist(data, ra);

	/* Itera até encontrar um ponto de colisão com uma parede, atualizando
	 as distâncias sidedist_x e sidedist_y. */
	collision_loop(data);

	/*   Retorna a distância até o ponto de colisão mais próximo. */
	if (data->wall == 0)
		return (data->sidedist_x - data->deltadist_x);
	else
		return (data->sidedist_y - data->deltadist_y);
}
```

<h1></h1>

- Descrição: calcula a distância do jogador até a parede mais próxima em uma
determinada direção `ra`.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
- Parâmetro: `double ra` - ângulo de visão.
```c
static void get_deltadist(t_data *data, double ra)
{
    /*
    - Fizemos validações quando o valor de cos(ra) é zero, significa que a direção
    do raio é paralela a um eixo vertical (ou seja, perpendicular ao eixo
    horizontal), e, portanto, não há inclinação horizontal do raio. Isso pode
    causar um problema de divisão por zero na equação usada para calcular a
    distância delta em relação ao eixo horizontal.

    - Para evitar isso, quando cos(ra) é zero, é atribuído ao deltadist_x um valor
    grande, em vez de MAX_INT para garantir que ele seja maior que a distância
    máxima que o raio pode percorrer no eixo horizontal, garantindo que o código
    não tente fazer uma divisão por zero.
    
    - Se cos(ra) é igual a 0, a distância em x até a próxima parede é definida
    como o valor máximo possível. 
    Caso contrário, a distância é calculada como a largura do bloco (64)
    dividida por cos(ra). */
    if (cos(ra) == 0)
        data->deltadist_x = MAX_INT;
    else
        data->deltadist_x = fabs(64 / cos(ra));

    /* Se sin(ra) é igual a 0, a distância em y até a próxima parede é definida
    como o valor máximo possível. 
    Caso contrário, a distância é calculada como a largura do bloco (64)
    dividida por sin(ra). */
    if (sin(ra) == 0)
        data->deltadist_y = MAX_INT;
    else
        data->deltadist_y = fabs(64 / sin(ra));
}

```

<h1></h1>

- Descrição: calcula as distâncias percorridas pelos raios até atingirem a
próxima parede nas direções horizontal e vertical. Essas distâncias são
armazenadas nas variáveis sidedist_x e sidedist_y, respectivamente.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
- Parâmetro: `double ra` - ângulo de rotação da câmera em relação ao jogador.
```c
static void    get_sidedist(t_data *data, double ra)
{
    /* Verifica se o ângulo de rotação está apontando para a esquerda */
    if (ra < PI)
    {
        /* Calcula a distância da próxima parede na direção y */
        data->sidedist_y = fabs(((int)(data->player.y) % SPRITE_SIZE) / sin (ra));

        /* Define o sentido do passo como para cima */
        data->step_y = -1;
    }

    /* Caso contrário, o ângulo de rotação está apontando para a direita */
    else
    {
        /* Calcula a distância da próxima parede na direção y */
        data->sidedist_y = fabs((SPRITE_SIZE - (int)(data->player.y) % SPRITE_SIZE) / sin (ra));

        /* Define o sentido do passo como para baixo */
        data->step_y = 1;
    }

    /* Verifica se o ângulo de rotação está apontando para cima ou para baixo */
    if (ra > PI / 2 && ra < 3 * PI / 2)
    {
        /* Calcula a distância da próxima parede na direção x */
        data->sidedist_x = fabs(((int)(data->player.x) % SPRITE_SIZE) / cos (ra));

        /* Define o sentido do passo como para a esquerda */
        data->step_x = -1;
    }
    /* Caso contrário, o ângulo de rotação está apontando para a esquerda ou direita */
    else
    {
        /* Calcula a distância da próxima parede na direção x */
        data->sidedist_x = fabs((SPRITE_SIZE - (int)(data->player.x) % SPRITE_SIZE) / cos (ra));

        /* Define o sentido do passo como para a direita */
        data->step_x = 1;
    }
}
```

<h1></h1>

- Descrição: verifica se o player colidirá com uma parede ou não.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
static void collision_loop(t_data *data)
{
    /* Divide a posição do jogador por 64 para encontrar a posição do jogador no
    mapa. */
    data->map_x = (int)(data->player.x) >> 6;
    data->map_y = (int)(data->player.y) >> 6;
    
    /* Enquanto a posição atual do jogador no mapa não for uma parede
    (representada pelo valor '1'). */
    while (data->map.map[data->map_y][data->map_x] != '1')
    {
        /* Se a distância para a próxima parede na direção x é menor que a
        distância na direção y. */
        if (data->sidedist_x < data->sidedist_y)
        {
            /* Atualiza a distância para a próxima parede na direção x, a
            posição do jogador no mapa na direção x e define que o jogador não
            está mais na parede. */
            data->sidedist_x += data->deltadist_x;
            data->map_x += data->step_x;
            data->wall = 0;
        }
        else
        {
            /* Atualiza a distância para a próxima parede na direção y, a
            posição do jogador no mapa na direção y e define que o jogador está na parede. */
            data->sidedist_y += data->deltadist_y;
            data->map_y += data->step_y;
            data->wall = 1;
        }
    }
}
```
- Exemplo do loop de colisão:
```
Mapa:
11111
10001
10N01
10001
11111

player.y = 3
player.x = 3
sprite 64 
player.y = y * sprite + (sprite/2)
player.y = 3 * 64 + (32)
player.y = 224
data->map_y = 3

player.x = x * sprite + (sprite/2)
player.x = 3 * 64 + (32)
player.x = 224
data->map_x = 3
```