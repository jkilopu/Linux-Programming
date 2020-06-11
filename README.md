# Linux-Programming
There are implementations of some commands, a few linux games and homework in "Understanding Unix/Linux Programming"

---

## mysnake
Simple console version of the game "snake" for Linux
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
git clone https://github.com/jkilopu/Linux-Programming.git
cd ./Linux-Programming/mysnake
cmake -Bbuild -H.
cd ./build
make
./bin/mysnake
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
