### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>

- Funções deste arquivo:
```c
int			ft_run(t_data *data);
int			arrows_down(int keycode, t_data *data);
int			arrows_up(int keycode, t_data *data);
static void	movement(t_data *data);
static int	check_collision(t_data *data, double ra);
```

<h1></h1>

- Descrição: atualiza a posição do jogador na tela de acordo com as
informações armazenadas em `data`.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
int	ft_run(t_data *data)
{
    /* Responsável pela movimentação do jogador */
	movement(data);

    /* Movimentação para a esquerda e direita */
	if (data->turn_left == 1)
		data->player.angle += PI / 180;
	if (data->turn_right == 1)
		data->player.angle -= PI / 180;

    /* Essas duas validações servem para manter o ângulo dentro do intervalo 
    de 0 a 360 graus.*/
	if (data->player.angle > PI * 2)
		data->player.angle -= PI * 2;
	if (data->player.angle < 0)
		data->player.angle += PI * 2;

    /* Gera a imagem */
	make_image(data);
	return (0);
}
```

<h1></h1>

- Descrição: é chamada quando uma tecla é solta no teclado. 
- Parâmetro: `int keycode` - tecla pressionada.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
int	arrows_down(int keycode, t_data *data)
{
	if (keycode == 97)
		data->move_left = 1;
	if (keycode == 100)
		data->move_right = 1;
	if (keycode == 115)
		data->move_down = 1;
	if (keycode == 119)
		data->move_up = 1;
	if (keycode == 65361)
		data->turn_left = 1;
	if (keycode == 65363)
		data->turn_right = 1;
	if (keycode == 65307)
		close_game(data);
	return (0);
}
```
<h1></h1>

- Descrição: é chamada quando uma tecla é pressionada no teclado. 
- Parâmetro: `int keycode` - tecla pressionada.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
int	arrows_down(int keycode, t_data *data)
{
	if (keycode == 97)
		data->move_left = 1;
	if (keycode == 100)
		data->move_right = 1;
	if (keycode == 115)
		data->move_down = 1;
	if (keycode == 119)
		data->move_up = 1;
	if (keycode == 65361)
		data->turn_left = 1;
	if (keycode == 65363)
		data->turn_right = 1;
	if (keycode == 65307)
		close_game(data);
	return (0);
}
```

<h1></h1>

- Descrição: atualiza a movimentação do jogador dentro do mapa. 
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
static void movement(t_data *data)
{
    /* Se o jogador está movendo para frente e não colide com paredes */
    if (data->move_up == 1 \
	&& check_collision(data, data->player.angle))
    {
        /* Atualiza a posição do jogador na direção escolhida */
        data->player.x += 2 * cos(data->player.angle);
        data->player.y -= 2 * sin(data->player.angle);
    }
    
    /* Se o jogador está movendo para trás e não colide com paredes */
    if (data->move_down == 1 \
	&& check_collision(data, data->player.angle + PI))
    {
        /* Atualiza a posição do jogador na direção escolhida */
        data->player.x -= 2 * cos(data->player.angle);
        data->player.y += 2 * sin(data->player.angle);
    }

    /* Se o jogador está movendo para a direita e não colide com paredes */
    if (data->move_right == 1 \
	&& check_collision(data, data->player.angle - PI / 2))
    {
        /* Atualiza a posição do jogador na direção escolhida */
        data->player.x += 2 * sin(data->player.angle);
        data->player.y += 2 * cos(data->player.angle);
    }

    /* Se o jogador está movendo para a esquerda e não colide com paredes */
    if (data->move_left == 1 \
	&& check_collision(data, data->player.angle + PI / 2))
    {
        /* Atualiza a posição do jogador na direção escolhida */
        data->player.x -= 2 * sin(data->player.angle);
        data->player.y -= 2 * cos(data->player.angle);
    }
}
```

- Descrição: verifica se houve colisão do jogador com uma parede do mapa
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
- Parâmetro: `double ra`- 
```c
static int	check_collision(t_data *data, double ra)
{
	int	map_x;
	int	map_y;

    /* Chama a função para obter a distância até a próxima parede */
	get_distance(data, ra);

    /* Calcula a posição no mapa onde o jogador iria caso se movesse mais 5
    passos
	*/
	map_x = data->player.x + (5 * data->step_x);
	map_y = data->player.y + (5 * data->step_y);

    /* Faz um shift para a direita de 6 bits para dividir por 64 e obter a
    posição no mapa
	*/
	map_x = map_x >> 6;
	map_y = map_y >> 6;

    /* Verifica se a próxima posição do jogador é uma parede no mapa */
    if (data->map.map[map_y][(int)(data->player.x) >> 6] == '1' || \
        data->map.map[(int)(data->player.y) >> 6][map_x] == '1' || \
        data->map.map[map_y][map_x] == '1')
        
        /* Houve colisão */
        return (0);

    /* Não Houve colisão */
    return (1);
}

```