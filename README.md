# Linux-Programming
There are implementations of some commands, a few linux games and homework in "Understanding Unix/Linux Programming"

## mysnake
Console version of the game "snake" for Linux
### Gameplay
You can change the moving direction of snake in four keys: *w, a, s, d*. The snake will move automatically. 
By eating food, your snake will grow.
When your snake hit the wall or its body. the game is over.
Help your snake grow longer and longer, maybe you will find a bug in the game.
### Requirements
* C compiler
* ncurses library
### Installation
``` bash
git clone git@github.com:jkilopu/Linux-Programming.git
cd ./Linux-Programming/mysnake
cmake -Bbuild -H.
cd ./build
make
./bin/mysnake
```