### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [O Que é RayCasting?](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d/blob/main/readmes/necessary_concepts/raycasting.md) | 
[Criando um Simples Raycasting](https://github.com/Vinicius-Santoro/42-formation-lvl2-11.cub3d/blob/main/readmes/necessary_concepts/raycasting-c.md) ➡

<h1></h1>

#### Como criar uma interface gráfica utilizando a MiniLibX

- Inclua os arquivos de cabeçalho da minilibx:
```c
#include "mlx.h"
```

- Inicialize a biblioteca minilibx usando a função mlx_init():
```c
void *mlx_ptr;
mlx_ptr = mlx_init();
```

- Inclua os arquivos de cabeçalho da minilibx:
```c
#include "mlx.h"
```

- Crie uma janela usando a função mlx_new_window():
```c
void *win_ptr;
win_ptr = mlx_new_window(mlx_ptr, largura, altura, "Título da Janela");
```

- Adicione conteúdo à janela, por exemplo, desenhando formas geométricas usando as funções da minilibx.
```c
mlx_pixel_put(mlx_ptr, win_ptr, x, y, cor);
```

- Inicie o loop de eventos usando a função mlx_loop():
```c
mlx_loop(mlx_ptr);
```

- Finalize o programa usando a função mlx_destroy_window()
```c
mlx_destroy_window(mlx_ptr, win_ptr);

```
