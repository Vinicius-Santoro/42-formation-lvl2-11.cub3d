### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>

- Descrição: verifica se o cabeçalho do arquivo `.cub` está faltando.
- Parâmetro: `t_data *data` - informações sobre o mapa e as texturas.
```c
static void	check_is_missing_header(t_data *data)
{
	/* Verifica se a textura norte está faltando */
	if (data->map.tex.no == NULL)
		error_message(13, "Invalid texture: missing NO", data);
	
	/* Verifica se a textura sul está faltando */
	if (data->map.tex.so == NULL)
		error_message(14, "Invalid texture: missing SO", data);
	
	/* Verifica se a textura oeste está faltando */
	if (data->map.tex.we == NULL)
		error_message(15, "Invalid texture: missing WE", data);
	
	/* Verifica se a textura leste está faltando */
	if (data->map.tex.ea == NULL)
		error_message(16, "Invalid texture: missing EA", data);
	
	/* Verifica se a cor do piso está faltando */
	if (data->map.color.floor == -1)
		error_message(17, "Invalid RGB: missing floor", data);
	
	/* Verifica se a cor do teto está faltando */
	if (data->map.color.ceil == -1)
		error_message(18, "Invalid RGB: missing ceil", data);
}
```

<h1></h1>

- Descrição: inicializa os valores das variáveis relacionadas ao mapa.
- Parâmetro: `t_data *data` - informações sobre o mapa e as texturas.
```c
static void	init_map(t_data *data)
{
	/* Inicializa a contagem de linhas do mapa com 0 */
	data->map.count_line = 0;
	
	/* Inicializa o vetor de strings que representa a linha do mapa dividida em células como NULL */
	data->map.splited_line = NULL;

	/* Inicializa o vetor de inteiros que representa o mapa como NULL */
	data->map.map = NULL;

	/* Inicializa o caminho da textura para a direção norte como NULL */
	data->map.tex.no = NULL;

	/* Inicializa o caminho da textura para a direção sul como NULL */
	data->map.tex.so = NULL;

	/* Inicializa o caminho da textura para a direção oeste como NULL */
	data->map.tex.we = NULL;

	/* Inicializa o caminho da textura para a direção leste como NULL */
	data->map.tex.ea = NULL;

	/* Inicializa a cor do chão como -1 */
	data->map.color.floor = -1;

	/* Inicializa a cor do teto como -1 */
	data->map.color.ceil = -1;

	/* Inicializa a linha de início do mapa como 0 */
	data->map.start_line = 0;

	/* Inicializa a coluna máxima do mapa como 0 */
	data->map.max_column = 0;
}
```

<h1></h1>

- Descrição: lê o arquivo de mapa e armazena as informações necessárias para o jogo.
- Parâmetro: `int fd` - mapa.
- Parâmetro: `t_data *data` - informações sobre o mapa.
```c
int	read_map(int fd, t_data *data)
{
	char	*temp;
	int		i;

	/* Inicialização das variáveis necessárias */
	init_map(data);

	/* Lê o arquivo linha por linha */
	while (TRUE)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		data->map.line = ft_strjoin_free(data->map.line, temp);
		free(temp);
	}

	/* Divide o arquivo inteiro em linhas */
	data->map.lines = ft_split(data->map.line, '\n');
	free(data->map.line);
	i = -1;

	/* Verifica se as informações estão corretas */
	while (data->map.lines[++i])
		/* texturas no, so, we, ea, F e C. */
		check_line(data->map.lines[i], data);
	check_is_missing_header(data);
}
```
