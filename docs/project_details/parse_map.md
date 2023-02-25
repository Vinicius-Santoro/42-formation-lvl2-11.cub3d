### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>


- Funções deste arquivo:
```c
void		parse_map(t_data *data);
static void	get_map(t_data *data);
static void	validate_map_boundaries(int y, int x, t_data *data);
static void	get_player_angle(int y, int x, t_data *data);
```

<h1></h1>

- Descrição: verifica o mapa, validando se é válido e recebe o campo de visão
inicial do jogador.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
void	parse_map(t_data *data)
{
	int	y;
	int	x;

    /* Valida se o mapa existe. */
	get_map(data);
	data->player.count = 0;
	y = -1;
	while (data->map.map[++y] != NULL)
	{
		x = -1;
		while (data->map.map[y][++x] != '\0')
		{
            /* Valida se o mapa é cercado por paredes. */
			validate_map_boundaries(y, x, data);

            /* Armazena o campo de visão inicial do player. */
			get_player_angle(y, x, data);
		}
	}

    /* Valida a quantidade de jogadores dentro do mapa. */
	if (data->player.count > 1)
		error_message(21, "Invalid player: too many", data);
	if (data->player.count < 1)
		error_message(22, "Invalid player: not enough", data);
}
```

<h1></h1>

- Descrição: verifica se o mapa existe.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
static void	get_map(t_data *data)
{
    /* Se a linha inicial for igual a zero, não existe o mapa. */
	if (data->map.start_line == 0)
		error_message(19, "Invalid map: missing map", data);
	data->map.map = &(data->map.lines[data->map.start_line - 1]);
}
```

<h1></h1>

- Descrição: verifica se o mapa é cercado por paredes.
- Parâmetro: `int y` - coordenada y.
- Parâmetro: `int x` - coordenada x.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
static void	validate_map_boundaries(int y, int x, t_data *data)
{
    /*Ponteiro para o mapa*/
    char	**map;

    /*Atribui o mapa a variável map*/
    map = data->map.map;
    
    /* Verifica se a posição atual contém um dos caracteres válidos e se os arredores da posição atual são válidos */
    if (ft_strchr("0NSWE", map[y][x]) && (
        map[y][x + 1] == '\0' || map[y + 1][x + 1] == '\0' || \
        map[y][x - 1] == '\0' || map[y + 1][x - 1] == '\0' || \
        map[y + 1][x] == '\0' || map[y - 1][x + 1] == '\0' || \
        map[y - 1][x] == '\0' || map[y - 1][x - 1] == '\0' || \
        map[y][x + 1] == ' ' || map[y + 1][x + 1] == ' ' || \
        map[y][x - 1] == ' ' || map[y + 1][x - 1] == ' ' || \
        map[y + 1][x] == ' ' || map[y - 1][x + 1] == ' ' || \
        map[y - 1][x] == ' ' || map[y - 1][x - 1] == ' ' )
        )
        /*  Se for inválido, exibe a mensagem de erro e termina o programa */
        error_message(20, "Invalid map: not surrounded by walls", data);
}

```

<h1></h1>

- Descrição: armazena a posição inicial do jogador - 0º, 90º, 180º ou 270º.
- Parâmetro: `int y` - coordenada y.
- Parâmetro: `int x` - coordenada x.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
static void	get_player_angle(int y, int x, t_data *data)
{
	/* Verifica se a posição atual contém um dos caracteres que representa o jogador */
	if (ft_strchr("NSWE", data->map.map[y][x]))
	{
		/* Incrementa o contador de jogadores e armazena a posição central do jogador */
		data->player.count++;
		data->player.y = y * SPRITE_SIZE + SPRITE_SIZE / 2;
		data->player.x = x * SPRITE_SIZE + SPRITE_SIZE / 2;
		
		/* Atribui o ângulo inicial do jogador baseado na direção que ele está olhando */
		if (data->map.map[y][x] == 'E')
			data->player.angle = (PI / 2) * 0;
		if (data->map.map[y][x] == 'N')
			data->player.angle = (PI / 2) * 1;
		if (data->map.map[y][x] == 'W')
			data->player.angle = (PI / 2) * 2;
		if (data->map.map[y][x] == 'S')
			data->player.angle = (PI / 2) * 3;
	}
}


```