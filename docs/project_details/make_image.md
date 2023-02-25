### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>

- Funções deste arquivo:
```c
void		make_image(t_data *data);
void		make_vertical_line(
				t_data *data, int dist, double ix, t_img_data *img);
static void	put_vertical_line(t_data *data, t_img_data *img);
static void	put_pixel_img(t_img_data *img, int x, int y, int color);
static int	get_pixel_img(t_img_data *img, int x, int y);
```

<h1></h1>

- Descrição: é responsável por renderizar a imagem do jogo na janela gráfica.
- Parâmetro: `t_data *data` - quantidade de argumentos passados na linha de comando.
```c
void	make_image(t_data *data)
{
	mouse_move(0, 0, data);
	data->img.game = malloc(sizeof(t_img));
	data->img.game->new_img = mlx_new_image(\
		data->mlx, WINDOW_SIZE, WINDOW_SIZE \
		);
	data->img.game->address = mlx_get_data_addr(\
		data->img.game->new_img, &data->img.game->bits_per_pixel, \
		&data->img.game->line_length, &data->img.game->endian \
		);
	data->ra = data->player.angle + (PI / 180 * SPRITE_SIZE / 2);
	data->ray_num = 0;
	while (data->ray_num < SPRITE_SIZE)
	{
		raycast(data, data->ra);
		data->ra -= PI / 180;
		data->ray_num++;
	}
	mlx_put_image_to_window(
		data->mlx, data->win, data->img.game->new_img, 0, 0
		);
	mlx_destroy_image(data->mlx, data->img.game->new_img);
	free(data->img.game);
	get_fps(data);
}
```
