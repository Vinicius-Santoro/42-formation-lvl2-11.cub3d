### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>


- Descrição: Essa função valida se a extensão do arquivo do mapa é `.cub`,
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
	if (is_valid_ext(file_name, ".cub") == FALSE)
		error_message(4, "Invalid file extension: not .cub", data);
	read_map(fd, data);
	parse_map(data);
	close(fd);
	return (0);
}
```

```c
t_img_data	*init_texture( char *file, t_data *data)
{
	int		trash;
	t_img_data	*ret;

	ret = malloc (sizeof(t_img));
	ret->new_img = mlx_xpm_file_to_image(data->mlx, file, &trash, &trash);
	ret->address = mlx_get_data_addr(ret->new_img, &ret->bits_per_pixel,
			&ret->line_length, &ret->endian);
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
