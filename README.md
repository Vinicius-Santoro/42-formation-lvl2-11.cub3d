# 42-formation-lvl2-11.cub3d

Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo.

- This project is inspired by the world-famous Wolfenstein 3D game. Our goal is to create a raycaster.

#### This project was like this:
![philo](https://user-images.githubusercontent.com/83036509/195736506-28f72fd7-3b88-48f3-8b93-01e2c5648938.gif)

#### How to run

- Clone the repository
````
git clone git@github.com:Vinicius-Santoro/42-formation-lvl2-11.cub3d.git
````
- Run `make` to compile _common part_.
- To clean objects files execute: `make clean`
- To clean executable file and objects: `make fclean`
- Recompile: `make re`
- Run `./cub3D` or followed by map path e.g. `./assets/maps/map.cub`

#### File configuration

To run the game, you must pass as first argument a scene description file with the .cub
extension.

#### Identifiers

The file must have 6 element identifiers:

| Identifier      |      Description    |
|:----------:|-------------|
|NO| Represents the texture of the wall in the north direction|
|SO| Represents the wall texture in the south direction|
|WE| Represents the wall texture in the west direction|
|EA| Represents the wall texture in the east direction|
|C| Represents the RGB color scale of the celling|
|F| Represents the RGB color scale of the floor||

Example in a .cub file:

````
NO ./assets/images/texture_1.xpm
SO ./assets/images/texture_2.xpm
WE ./assets/images/texture_3.xpm
EA ./assets/images/texture_4.xpm

F 220,100,0
C 225,30,0
````

#### Map configuration

The map construction is composed by the following characters:

- Walls: `'1'`
- Empty spaces inside: `'0'`
- Empty spaces outside: `' '`
- Initial player direction: `'N'`, `'S'`, `'W'` or `'E'`

#### Map Rules

- It must be completely surrounded by walls
- It must have a player

Map example:

````
111111111111111111111
100001000000000000001
101000000000000000001
100S00100100100100101
100000000000000000001
100000100000000000001
111111111111111111111
````

#### How to play

- The `'→'` and `'←'`  keys of the keyboard allow you to look left and
right in the maze.
- The `'W'`, `'A'`, `'S'` and `'D'` keys allow you to move the point of view through
the maze.
- You can run holding `'Shift'` key.
- `'Esc'` key exits the game.

#### Details of the entire project

- [O que é RayCasting?](docs/necessary_concepts/raycasting.md)
- [Interface gráfica utilizando a Linguagem C com MiniLibX](docs/necessary_concepts/interface.md)
- [RayCasting usando a Linguagem C](docs/necessary_concepts/raycasting-c.md)

#### Details of the entire project

- [makefile](docs/project_details/makefile.md)
- [main.c](docs/main.md)
- [utils.c](docs/utils.md)
- [init_list.c](docs/init_list.md)
- [thread.c](docs/thread.md)
- [philo_actions.c](docs/philo_actions.md)
- [mutex_check.c](docs/thread.md)
- [death_check.c](docs/death_check.md)
- [free.c](docs/free.md)
