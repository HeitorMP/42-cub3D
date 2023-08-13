
# Cub3D

My first RayCaster with miniLibX

This project was made in collaboration with [Nuno Moreira](https://github.com/nunotaboada).

It is inspired by the world-famous Wolfenstein 3D game, which
was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to
make a dynamic view inside a maze, in which you’ll have to find your way.

the project consists of creating a “realistic” 3D graphical
representation of the inside of a maze from a
first-person perspective. You have to create this
representation using the Ray-Casting principles.


### Exemple of a configuration file:
it is necessary to pass a configuration file of type .cub as a parameter. You can find some files in the maps folder!

This file needs to have the following information:
- texture for north, south, east and west walls.
- floor color and ceiling color
- a map where 1 represents the walls and 0 the - floor, in addition to the initial position of the player with the letters N, S, E, or W that indicates the direction in which the player will be looking at the beginning of the game.



## Screenshots

![Menu](https://i.imgur.com/wqghhSF.png)
![Game](https://i.imgur.com/DOcJy2U.png)


## what I've learned

 - [Ray-casting](https://en.wikipedia.org/wiki/Ray_casting)


## Usage/Examples

```bash
Make or Make bonus
```

```bash
./cub3D_bonus maps/configurations_file.cub
```

