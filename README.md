# Linux-Programming
There are implementations of some commands, a few linux games and homework in "Understanding Unix/Linux Programming"

---

## mysnake
Simple console version of the game "snake" for Linux ONLY, with scoreboard.
### Gameplay
Use *w, a, s, d* to change to direction of the snake, it will move automatically. 

By eating food, your snake will grow, and you will score ten points.

When your snake hit the wall or its body. the game is over.

Try different user names, you can see your real-time ranking on the scoreboard.

Help your snake grow longer and longer, your score will be recorded in *scoreboard.txt*.

### Requirements
* C/C++ compiler
* ncurses library
* cmake
* make
### Installation
``` bash
git clone https://github.com/jkilopu/Linux-Programming.git
cd ./Linux-Programming/mysnake
mkdir build
cd build
cmake .. # You may need to specify a build system generator with "-G" option
make
cd ..
./build/bin/mysnake
```

---

## mymine

Imitaion of classic game "Mines" using SDL2 library, with timer and flag.

### Gameplay

In the menu, you can determine the map width, height and the number of mines.

Once the game starts, you can use the mouse to click on blocks. The left click will open the block, the right click will set a flag on the block.

If you left-click on a digit, and the number of flags around it equals its value, then non-flagged blocks around it will be opened. 

On the right side of the game window, the time spent will be shown.

Sweep all the mines(open all the blocks which can be opened) to win!

### Requirements

* C/C++ compiler
* SDL2 library
* cmake
* make

### Installation

``` bash
git clone https://github.com/jkilopu/Linux-Programming.git
cd ./Linux-Programming/mymine
mkdir build
cd build
cmake .. # You may need to specify a build system generator with "-G" option
make
cd ..
./build/bin/mymine
```

---

## my_shell
A simple shell can only run commands with some arguments in PATH, version 0.2.
### Describtion
Accept a command, find a program in the path, and repeat the above work before receiving the exit command (and ignore the interrupt signal from the keyboard)
### Installation
``` bash
git clone https://github.com/jkilopu/Linux-Programming.git
cd ./Linux-Programming/process
gcc my_shell.c -o my_shell
./my_shell
```
try command like "ls -l" or "bc" etc.
### shortage
1. Do not support redirect.
2. Do not support pipe.
3. Do not support anything complex.
