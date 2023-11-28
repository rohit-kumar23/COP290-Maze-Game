## COP290 A 2 Player Maze Game

### Task: A 2 player maze game Details
<p align="justify">
Create a maze that matches the IIT Delhi campus as closely as you can. Design a two player game, over that maze. For instance, if you can reach Masala Mix earlier than your opponent, you can occupy a bigger table. If you reach basket-ball court earlier, you will find that empty to play. You can make these kind of things as the final goal. You can also combine a set of tasks, that have to be completed before reaching the final goal. Like collecting the basket ball from the hostel sports room before going to grounds. Some tasks might have a predefined time, like hostel lunch. Missing lunch within that time, can cause a player to drop unconscious after a while, unless he/she eats something from hostel canteen or Amul. Obstacles can include hungry dogs or angry professors, that you might want to avoid on a route. You can increase a player's speed using Yulu between two Yulu stands. Think of a way to give points to the players as the game progresses and a win/loss criteria. Keep the game challenging and unexpected, even after multiple plays. E.g. generate the obstacles at random places on the fly. The above points are just examples, feel free to build something completely different. The only restriction is it has to be set in IITD campus, and should be at least 2 players. You and your team-mate should be able to play the game over Wi-Fi. You will have to learn about sockets for this. You can use arrow keys to move your players. Think about usability at all steps of designing and implementing the game. Appropriate rules shown at game start. Smooth controls. Appropriate messages when network is slow. Sound effects.
</p>


### Installations:
```
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libsdl2-mixer-dev
```

### To run:
```
cd 'Maze Game'
make
make run
```

### Some resources for implementing the above in C++:

(a) Games with SDL for IO control: [sdl1](https://lazyfoo.net/tutorials/SDL/index.php), [sdl2](https://galdin.dev/blog/getting-started-with-sdl/), [sdl3](https://github.com/maciejspychala/sdl-game), [sdl4](http://www.sdltutorials.com/sdl-net-part-1-user-tutorial)

(b) Maze creation and solving: [maze1](https://en.wikipedia.org/wiki/User:Dllu/Maze), [maze2](https://en.wikipedia.org/wiki/Maze_generation_algorithm), [maze3](https://www.makeschool.com/academy/track/standalone/trees-and-mazes/generating-a-maze-with-dfs), [maze4](https://en.wikipedia.org/wiki/Maze-solving_algorithm)

(c) Pacman C++/SDL: [pacman1](https://github.com/schuay/pacman), [pacman2](https://github.com/DarkMuffinJoe/Pacman)
