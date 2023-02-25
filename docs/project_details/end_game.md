### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>

- Funções deste arquivo:
```c
void		error_message(int error_code, char *message_error, t_data *data);
int			close_game(t_data *data);
static void	exit_game(t_data *data);
void		free_matrix(char **matrix);
static void	destroy_images(t_data *data);
```

<h1></h1>

- Descrição: retorna uma mensagem de erro e retorna o código do erro.
- Parâmetro: `int error_code` - código de erro passado como parâmetro.
- Parâmetro: `char *message_error` - mensagem de erro especificada.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
void	error_message(int error_code, char *message_error, t_data *data)
{
	printf("Error\n");
	printf(RED"%s\n"RE, message_error);
	if (error_code > 4)
		exit_game(data);
	free(data);
	exit(error_code);
}
```

<h1></h1>

- Descrição: fecha o jogo, detruindo as imagens e desalocando tudo que foi
alocado.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
int	close_game(t_data *data)
{
	destroy_images(data);
	exit_game(data);
	free(data->fps.str_fps);
	free(data);
	printf("%scub%s3%sD%s: was %sclosed.%s\n", \
	MAGENTA, BLUE, RED, RE, BLUE, RE);
	exit(0);
}
```

<h1></h1>

- Descrição: fecha o jogo, desalocando todas as texturas e matrizes geradas.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.
```c
static void	exit_game(t_data *data)
{
	free(data->map.tex.no);
	free(data->map.tex.so);
	free(data->map.tex.we);
	free(data->map.tex.ea);
	free_matrix(data->map.splited_line);
	free_matrix(data->map.lines);
}
```

<h1></h1>

- Descrição: desaloca uma matriz.
- Parâmetro: `char **matrix` - matriz a ser desalocada.
```c
void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix != NULL)
	{
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}
```

<h1></h1>

- Descrição: destrói todas as imagens geradas.
- Parâmetro: `t_data *data` - um ponteiro para a struct `t_data` que armazena as
informações do jogo.

```c
static void	destroy_images(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.no->new_img);
	mlx_destroy_image(data->mlx, data->img.so->new_img);
	mlx_destroy_image(data->mlx, data->img.we->new_img);
	mlx_destroy_image(data->mlx, data->img.ea->new_img);
	free(data->img.no);
	free(data->img.so);
	free(data->img.we);
	free(data->img.ea);
	mlx_clear_window(data->mlx, data->win);
	mlx_loop_end(data->mlx);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
```
