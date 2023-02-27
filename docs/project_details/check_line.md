### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>

- Funções deste arquivo:
```c
void		check_line(char *line, t_data *data);
static char	*get_tex_file(char *line, char *tex, t_data *data);
static int	get_color(char *line, int color, t_data *data);
static int	check_map_chars(char *line);
```

<h1></h1>

- Descrição: analisa linha por linha do arquivo `.cub`.
- Parâmetro: `char *line` - string contendo a linha atual do arquivo `.cub` que
será analisada.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
void	check_line(char *line, t_data *data)
{
    /* Incrementa o número de linhas para chegar na linha do mapa */
	data->map.count_line++;

    /* Verifica se há as coordenandas nas linhas do arquivo .cub*/
	if (ft_strncmp("NO ", line, 3) == 0)
		data->map.tex.no = get_tex_file(line, data->map.tex.no, data);
	else if (ft_strncmp("SO ", line, 3) == 0)
		data->map.tex.so = get_tex_file(line, data->map.tex.so, data);
	else if (ft_strncmp("WE ", line, 3) == 0)
		data->map.tex.we = get_tex_file(line, data->map.tex.we, data);
	else if (ft_strncmp("EA ", line, 3) == 0)
		data->map.tex.ea = get_tex_file(line, data->map.tex.ea, data);

     /* Verifica se há as cores RGB no aqrvuico .cub*/
	else if (ft_strncmp("F ", line, 2) == 0)
		data->map.color.floor = get_color(line, data->map.color.floor, data);
	else if (ft_strncmp("C ", line, 2) == 0)
		data->map.color.ceil = get_color(line, data->map.color.ceil, data);

    /* Verifica se no mapa conténas apenas os caracteres ' 01NSWE' */
	else if (check_map_chars(line) == TRUE && data->map.start_line == 0)
		data->map.start_line = data->map.count_line;
	else if (check_map_chars(line) == FALSE)
		error_message(12, "Invalid map: imposible characters", data);
}
```

<h1></h1>

- Descrição: analisa as texturas no, so, we e ea do arquivo  `.cub`.
- Parâmetro: `char *line` - linha atual que será analisada.
- Parâmetro: `char *tex` - variável da textura, por exemplo, `data->map.tex.no`.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
static char	*get_tex_file(char *line, char *tex, t_data *data)
{
	char	*file_name;
	int		fd;

	/* Verifica se a textura não é nula, indicando que já foi especificada antes */
	if (tex != NULL)
		error_message(6, "Invalid texture: duplicated position", data);

	/* Extrai o nome do arquivo de textura a partir da linha */
	file_name = ft_strtrim(line + 3, " \n");

	/* Abre o arquivo de textura */
	fd = open(file_name, RDWR);
	if (fd < 0)
		/* Exibe mensagem de erro caso não seja possível abrir o arquivo */
		error_message(5, "Invalid texture: file not exist", data);

	/* Fecha o arquivo */
	close(fd);

	/* Verifica se a extensão do arquivo é .xpm */
	if (is_valid_ext(file_name, ".xpm") == FALSE)
		/* exibe mensagem de erro caso a extensão seja inválida */
		error_message(7, "Invalid file extension: not .xpm", data);

	/* Retorna o nome do arquivo de textura */
	return (file_name);
}

```

<h1></h1>

- Descrição: recebe a cor para a utilização no formato RGB.`.
- Parâmetro: `char *line` - linha atual que será analisada.
- Parâmetro: `char *tex` - variável da cor, por exemplo, `data->map.color.ceil`.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
static int	get_color(char *line, int color, t_data *data)
{
	char	*trimmed_line;
	int		rgb[3];
	int		i;

    i = -1;

    /* Verifica se a cor já foi definida */
    if (color != -1)
        error_message(7, "Invalid color: duplicated color rgb", data);

    /* Remove espaços e caracteres de quebra de linha da linha recebida */
    trimmed_line = ft_strtrim(line + 2, " \n\t\r");

    /* Divide a linha em 3 partes pelo caractere ',' */
    data->map.splited_line = ft_split(trimmed_line, ',');
    if (trimmed_line != NULL)
        free(trimmed_line);

    /* Para cada parte, verifica se é um valor numérico válido e se está dentro
    do intervalo permitido */
    while (data->map.splited_line[++i])
    {
        if (ft_strisdigit(data->map.splited_line[i]) == FALSE)
            error_message(9, "Invalud RGB value: is not a digit", data);
        rgb[i] = ft_atoi(data->map.splited_line[i]);
        if (rgb[i] < 0 || rgb[i] > 255)
            error_message(10, "Invalid RGB value: is not a 8bits", data);
    }

    /* Libera a memória usada pela matriz de strings com os valores RGB */
    free_matrix(data->map.splited_line);
    data->map.splited_line = NULL;

    /* Se o número de partes da linha não for exatamente 3, a cor é inválida */
    if (i != 3)
        error_message(11, "Invalid RGB value: is not a rgb", data);

    /* Retorna a cor no formato 0xRRGGBB
    - rgb[0] << 16: rgb[0] * 2 elevado a 16.
    - rgb[1] << 8: rgb[1] * 2 elevado a 8.
    - rgb[2] << 0: rgb[2] * 2 elevado a 0.
    */
    return ((rgb[0] << 16) + (rgb[1] << 8) + (rgb[2] << 0));
}
```

<h1></h1>

- Descrição: verifica se no mapa contém apenas os caracteres especificados.
- Parâmetro: `char *line` - linha atual que será analisada.
```c
static int	check_map_chars(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (0);
	while (line[i] != '\0')
	{
		if (!ft_strchr(" 01NSWE\n", line[i]))
			return (0);
		i++;
	}
	return (1);
}
```