### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d)

<h1></h1>

- Descrição:
- Parâmetro:
```c
void	put_vertical_line(t_data *data, t_img_data *img)
{
	while (data->rc.y_ceil <= data->rc.line_offset)
	{
		data->rc.x = (data->ray_num * 8);
		while (data->rc.x < (data->ray_num * 8) + 8)
			put_pixel_img(data->img.game, data->rc.x++, data->rc.y_ceil, \
			data->map.color.ceil);
		data->rc.y_ceil++;
	}
	while (data->rc.line_offset <= data->rc.y_max)
	{
		data->rc.x = (data->ray_num * 8);
		while (data->rc.x < (data->ray_num * 8) + 8)
			put_pixel_img(data->img.game, data->rc.x++, data->rc.line_offset, \
			get_pixel_img(img, (int)data->rc.x_tex, (int)data->rc.ty));
		data->rc.line_offset++;
		data->rc.ty += data->rc.y_tex_step;
	}
	while (data->rc.y_max <= WINDOW_SIZE)
	{
		data->rc.x = (data->ray_num * 8);
		while (data->rc.x < (data->ray_num * 8) + 8)
			put_pixel_img(data->img.game, data->rc.x++, data->rc.y_max, \
			data->map.color.floor);
		data->rc.y_max++;
	}
}
```

- Descrição:
- Parâmetro:
```c
void	make_vertical_line(t_data *data, int distance, double ix, t_img_data *img)
{
	data->rc.y_ceil = 0;
	if (distance == 0)
		distance = 1;
	data->rc.line_height = (SPRITE_SIZE * WINDOW_SIZE) / distance;
	data->rc.y_tex_step = SPRITE_SIZE / (float)data->rc.line_height;
	data->rc.y_tex_offset = 0;
	if (data->rc.line_height > WINDOW_SIZE)
	{
		data->rc.y_tex_offset = (data->rc.line_height - WINDOW_SIZE) / 2.0;
		data->rc.line_height = WINDOW_SIZE;
	}
	data->rc.line_offset = 256 - data->rc.line_height / 2;
	data->rc.y_max = data->rc.line_offset + data->rc.line_height;
	data->rc.x_tex = (int)(ix) % 64;
	if (img == data->img.so || img == data->img.we)
		data->rc.x_tex = 63 - data->rc.x_tex;
	data->rc.ty = data->rc.y_tex_offset * data->rc.y_tex_step;
	put_vertical_line(data, img);
}
```

- Descrição:
- Parâmetro:
```c
void	get_fps(t_data *data)
{	
	struct timeval	tv;

	gettimeofday(&tv, 0);
	if (data->last_sec == tv.tv_sec)
		data->count_frame++;
	else
	{
		data->last_fps = data->count_frame;
		data->last_sec = tv.tv_sec;
		data->count_frame=0;
		free(data->str_fps);
		data->str_fps = ft_itoa(data->last_fps);
	}
	mlx_string_put(data->mlx, data->win, \
	WINDOW_SIZE * 0.05, WINDOW_SIZE * 0.05, \
	0x00FF00, data->str_fps);
}
```

- Descrição:
- Parâmetro:
```c
void	make_image(t_data *data)
{
	get_fps(data);
	data->img.game = malloc(sizeof(t_img));
	data->img.game->new_img = mlx_new_image(data->mlx, WINDOW_SIZE, WINDOW_SIZE);
	data->img.game->address = mlx_get_data_addr( \
		data->img.game->new_img, &data->img.game->bits_per_pixel, \
		&data->img.game->line_length, &data->img.game->endian \
		);
	data->ra = data->player.angle + (PI / 180 * 32);
	data->ray_num = 0;
	while (data->ray_num < 64)
	{
		raycast(data, data->ra);
		data->ra -= PI / 180;
		data->ray_num++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.game->new_img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.game->new_img);
	free(data->img.game);
}
```

