# 42-formation-lvl2-11.cub3d

Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo.

- This project is about creat a RayCaster.

## This project was like this:
![philo](https://user-images.githubusercontent.com/83036509/195736506-28f72fd7-3b88-48f3-8b93-01e2c5648938.gif)

## __How to run__

- Clone the repository
````
git clone git@github.com:Vinicius-Santoro/42-formation-lvl2-11.cub3d.git
````
- Run `make` to compile _common part_.
- To clean objects files execute: `make clean`
- To clean executable file and objects: `make fclean`
- Recompile: `make re`
- Run `./cub3D` or followed by map path e.g. `./maps/map_0.cub`

## __File configuration__

To run the game, you must pass as first argument a scene description file with the .cub
extension.

### __Identifiers__

The file must have 6 element identifiers:

| Identifier      |      Description    |
|:----------:|-------------|
|NO| Represents the texture of the wall in the north direction|
|SO| Represents the wall texture in the south direction|
|EA| Represents the wall texture in the east direction|
|WE| Represents the wall texture in the west direction|
|C| Represents the RGB color scale of the celling|
|F| Represents the RGB color scale of the floor||

Example in a .cub file:

````
NO ./assets/xpm/walls/blue_wall_01.xpm
SO ./assets/xpm/walls/blue_wall_02.xpm
WE ./assets/xpm/walls/blue_wall_02.xpm
EA ./assets/xpm/walls/blue_wall_01.xpm

F 220,100,0
C 225,30,0
````

### __Map configuration__

The map construction is composed by the following characters:

#### _Common Part_

Walls: `'1'`

Empty spaces inside: `'0'`

Empty spaces outside: `' '`

Initial player direction: `'N'`, `'S'`, `'W'` or `'E'`

### __Map Rules__

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

## __How to play__

#### _Common part_

- The `'→'` and `'←'`  keys of the keyboard allow you to look left and
right in the maze.
- The `'W'`, `'A'`, `'S'`, and `'D'` keys allow you to move the point of view through
the maze.
- You can run holding `'Shift'` key.
- `'Esc'` key exits the game.

## __Details of the entire project__
- [main.c](readmes/main.md)
- [utils.c](readmes/utils.md)
- [init_list.c](readmes/init_list.md)
- [thread.c](readmes/thread.md)
- [philo_actions.c](readmes/philo_actions.md)
- [mutex_check.c](readmes/thread.md)
- [death_check.c](readmes/death_check.md)
- [free.c](readmes/free.md)