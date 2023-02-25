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
- Parâmetro: `char *tex` - variávelda textura, por exemplo, `data->map.tex.no`.
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
	fd = open(file_name, O_RDONLY);
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