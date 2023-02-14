### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>

- Descrição:
- Parâmetro:
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

- Descrição:
- Parâmetro:
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

- Descrição:
- Parâmetro:
```c
void	exit_game(t_data *data)
{
	free(data->map.tex.no);
	free(data->map.tex.so);
	free(data->map.tex.we);
	free(data->map.tex.ea);
	free_matrix(data->map.splited_line);
	free_matrix(data->map.lines);
}
```

- Descrição:
- Parâmetro:
```c
void	destroy_images(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.no->new_img);
	free(data->img.no);
	mlx_destroy_image(data->mlx, data->img.so->new_img);
	free(data->img.so);
	mlx_destroy_image(data->mlx, data->img.we->new_img);
	free(data->img.we);
	mlx_destroy_image(data->mlx, data->img.ea->new_img);
	free(data->img.ea);
	mlx_clear_window(data->mlx, data->win);
	mlx_loop_end(data->mlx);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
```

- Descrição:
- Parâmetro:
```c
int	close_game(t_data *data)
{
	destroy_images(data);
	exit_game(data);
	free(data->str_fps);
	free(data);
	printf("%scub%s3%sD%s: was %sclosed.%s\n", 
	MAGENTA, BLUE, RED, RE, BLUE, RE);
	exit(0);
}
