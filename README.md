# 42-formation-lvl2-11.cub3d

Project 11: Cub3D - Eleventh project for the formation of software engineers at school 42 São Paulo.

- This project is inspired by the world-famous Wolfenstein 3D game. Our goal is to create a raycaster.


#### This project was like this:
![lucas](https://user-images.githubusercontent.com/83036509/219818886-1cb1f06d-862c-473e-a2bd-305c0960e93b.gif)
<p align="left">
	<a href="https://www.linkedin.com/in/viniciusnaziozeno/">
    	<img alt="Linkedin" src="https://img.shields.io/badge/Vinicius Santoro-blue?style=flat&logo=Linkedin&logoColor=white" />
  	</a>
	<a href="https://github.com/Vinicius-Santoro" alt="login intra">
    	<img src="https://img.shields.io/badge/-vnazioze-gray?style=flat&logo=42&logoColor=white" />
	</a>
	<a href="https://www.linkedin.com/in/lucasdatiliocarderelli/">
		<img alt="Linkedin" src="https://img.shields.io/badge/Lucas Datilio-blue?style=flat&logo=Linkedin&logoColor=white" />
	</a>
	<a href="https://github.com/LucasDatilioCarderelli" alt="login intra">
		<img src="https://img.shields.io/badge/-ldatilio-gray?style=flat&logo=42&logoColor=white" />
	</a>
</p>

#### How to run

- Clone the repository
````
git clone git@github.com:Vinicius-Santoro/42-formation-lvl2-11.cub3d.git
````
- Run `make` to compile _common part_.
- To clean objects files execute: `make clean`
- To clean executable file and objects: `make fclean`
- Recompile: `make re`
- Run `./cub3D` or followed by map path e.g. `./assets/maps/map42.cub`

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
NO ./assets/Images/north.xpm
SO ./assets/Images/south.xpm  
WE ./assets/Images/west.xpm
EA ./assets/Images/east.xpm  

F 200,200,200
C 0,0,0
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
1111111111111111111111111111111111111
1000000000000000000000000000000000001
1001111000001111000001111111111111001
1001111000001111000001111111111111001
1001111000001111000001111111111111001
1001111000001111000000000000001111001
1001111111111111000001111111111111001
1001111111111111000001111111111111001
1000000000001111000001111111111111001
1000000000001111000001111000000000001
1000000000001111000001111111111111001
1000000000001111000001111111111111001
100000000000000000N000000000000000001
1111111111111111111111111111111111111
````

#### How to play

- The `'→'` and `'←'`  keys of the keyboard allow you to look left and
right in the maze.
- The `'W'`, `'A'`, `'S'` and `'D'` keys allow you to move the point of view through
the maze.
- `'Esc'` key exits the game.

#### Necessary concepts

- [O que é RayCasting?](docs/necessary_concepts/raycasting.md)
- [Interface gráfica utilizando a Linguagem C com MiniLibX](docs/necessary_concepts/interface.md)
- [RayCasting usando a Linguagem C](docs/necessary_concepts/raycasting-c.md)

#### Details of the entire project

- [makefile](docs/project_details/makefile.md)
- [check_line.c](docs/project_details/check_line.md)
- [commands.c](docs/project_details/commands.md)
- [end_game.c](docs/project_details/end_game.md)
- [main.c](docs/project_details/main.md)
- [make_image.c](docs/project_details/make_image.md)
- [parse_map.c](docs/project_details/parse_map.md)
- [raycast.c](docs/project_details/raycast.md)
- [read_map.c](docs/project_details/read_map.md)
