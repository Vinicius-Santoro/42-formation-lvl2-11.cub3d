### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>

- Descrição: libera a memória alocada para uma matriz de strings.
- Parâmetro: `char **matrix` - a matriz de strings a ser liberada da memória.
```c
void free_matrix(char **matrix)
{
    int i;

    /* Inicializa o contador 'i' em zero */
    i = 0;

    /* Verifica se a matriz passada como argumento não é nula */
    if (matrix != NULL)
    {
        /* Loop através de todas as strings na matriz */
        while (matrix[i])
        {
            /* Libera a memória alocada para cada string */
            free(matrix[i]);

            /* Incrementa o contador 'i' */
            i++;
        }

        /* Libera a memória alocada para a matriz inteira */
        free(matrix);
    }
}
```

<h1></h1>

- Descrição: exibe uma mensagem de erro e encerra o programa com uma determinada saída de código.
- Parâmetro: `error_code` -  um código de erro inteiro para indicar o tipo de erro ocorrido.
- Parâmetro: `message_error` - uma string com a mensagem de erro que deve ser exibida
- Parâmetro:  `data` - um ponteiro para a estrutura de dados `t_data` que armazena informações do programa.
```c
void error_message(int error_code, char *message_error, t_data *data)
{
    /* Exibir a mensagem "Error" */
    printf("Error\n");

    /* Exibir a mensagem de erro em vermelho */
    printf(RED"%s\n"RE, message_error);

    /* Se o código de erro for maior que 4, sair do jogo
    A validação é com maior que quatro, pois se for maior que quatro, significa que as texturas foram iniciadas
    e precisão ser desalocadas da memória.
    */
    if (error_code > 4)
        exit_game(data);

    /* Liberar a memória alocada para a estrutura de dados */
    free(data);

    /* Encerrar o programa com o código de erro especificado */
    exit(error_code);
}
```

<h1></h1>

- Descrição: encerra o jogo e libera a memória alocada para as informações do jogo armazenadas em `data`.
- Parâmetro: `t_data *data` - ponteiro para a estrutura de dados "t_data", que armazena informações sobre o jogo.
```c
void	exit_game(t_data *data)
{
	/* Libera a memória alocada para a textura norte, sil, leste e oeste. */
	free(data->map.tex.no);
	free(data->map.tex.so);
	free(data->map.tex.we);
	free(data->map.tex.ea);
	
	/* Libera a memória alocada para as linhas splited_line da matriz map */
	free_matrix(data->map.splited_line);
	
	/* Libera a memória alocada para as linhas lines da matriz map */
	free_matrix(data->map.lines);
}
```

<h1></h1>

- Descrição: destrói as imagens que foram criadas anteriormente usando a biblioteca MLX
- Parâmetro: `t_data *data` - ponteiro para a estrutura de dados "t_data", que armazena informações sobre o jogo.
```c
void	destroy_images(t_data *data)
{
	/* destrói as imagens do eixo da rosa dos ventos e desaloca elas.
	mlx_destroy_image(data->mlx, data->img.no->new_img);
	free(data->img.no);
	mlx_destroy_image(data->mlx, data->img.so->new_img);
	free(data->img.so);
	mlx_destroy_image(data->mlx, data->img.we->new_img);
	free(data->img.we);
	mlx_destroy_image(data->mlx, data->img.ea->new_img);
	free(data->img.ea);
	
	/* Limpa a janela "data->win" usando o ponteiro "data->mlx" */
	mlx_clear_window(data->mlx, data->win);
	
	/* Fecha o loop da biblioteca MLX */
	mlx_loop_end(data->mlx);
	
	/* Destrói a janela "data->win" usando o ponteiro "data->mlx" */
	mlx_destroy_window(data->mlx, data->win);

	/* Destrói a exibição da biblioteca MLX */
	mlx_destroy_display(data->mlx);

	/* Libera a memória alocada para o ponteiro "data->mlx" */
	free(data->mlx);
}
```

<h1></h1>

- Descrição: fecha o jogo e libera toda a memória alocada durante sua execução
- Parâmetro: `t_data *data` - ponteiro para a estrutura de dados "t_data", que armazena informações sobre o jogo.
```c
int	close_game(t_data *data)
{
	/* Destruir as imagens carregadas durante o jogo. */
	destroy_images(data);
	
	/* Liberar a memória alocada para o mapa. */
	exit_game(data);
	
	/* Liberar a memória alocada para o buffer de fps. */
	free(data->str_fps);
	
	/* Liberar a memória alocada para a estrutura t_data. */
	free(data);
	
	/* Exibi uma mensagem de saída na tela. */
	printf("%scub%s3%sD%s: was %sclosed.%s\n", 
	MAGENTA, BLUE, RED, RE, BLUE, RE);
	
	/* Finaliza o programa. */
	exit(0);
}
