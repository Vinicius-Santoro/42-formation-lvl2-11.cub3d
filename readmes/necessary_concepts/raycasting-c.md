### _Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo._

🏠 [home](https://github.com/Vinicius-Santoro/42-formation-lvl2-10.net_pratice)<br>
⬅ [o que é raycasting?](https://github.com/Vinicius-Santoro/42-formation-lvl2-10.net_pratice/blob/main/readmes/level01.md)

<h1></h1>

- Este código cria uma janela com o título "Simple Raycasting" com o tamanho de 800x600 e um jogador no centro da tela. O jogador tem um ângulo de visão e uma direção inicial de 0 graus.

```c
#include "mlx.h"
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

int main() {
    void *mlx_ptr;
    void *win_ptr;
    int x, y;
    double player_x = WIDTH / 2;
    double player_y = HEIGHT / 2;
    double angle = 0;
    double angle_increment = 0.1;
    int *image;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Simple Raycasting");

    image = mlx_get_data_addr(mlx_new_image(mlx_ptr, WIDTH, HEIGHT),
                              &x, &y, &x);

    while (1) {
        for (int x = 0; x < WIDTH; x++) {
            double ray_angle = angle - (M_PI / 3) / 2 +
                               (x / (double)WIDTH) * (M_PI / 3);
            double distance_to_wall = 0;
            int hit_wall = 0;
            while (!hit_wall) {
                distance_to_wall += 0.1;
                int test_x = player_x + distance_to_wall * cos(ray_angle);
                int test_y = player_y + distance_to_wall * sin(ray_angle);
                if (test_x < 0 || test_x >= WIDTH || test_y < 0 || test_y >= HEIGHT) {
                    hit_wall = 1;
                }
            }
            int wall_height = (HEIGHT / distance_to_wall);
            int wall_start = (HEIGHT - wall_height) / 2;
            for (int y = 0; y < wall_start; y++) {
                image[x + y * WIDTH] = 0x0000ff;
            }
            for (int y = wall_start; y < wall_start + wall_height; y++) {
                image[x + y * WIDTH] = 0xff0000;
            }
            for (int y = wall_start + wall_height; y < HEIGHT; y++) {
                image[x + y * WIDTH] = 0x00ff00;
            }
        }
        angle += angle_increment;
        mlx_put_image_to_window(mlx_ptr, win_ptr,
                                mlx_new_image(mlx_ptr, WIDTH, HEIGHT), 0, 0);
        mlx_loop(mlx_ptr);
    }
    mlx_destroy_window(mlx_ptr, win_ptr);
    return (0);
}
```
