# Linux-Programming
There are implementations of some commands and homework in "Understanding Unix/Linux Programming" and "CSAPP"

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

---

## mysnake&mymines
They are imitation of the classic games Mine and Snake.

I have moved them to other repos: [mymine](https://github.com/jkilopu/mymines), [mysnake](https://github.com/jkilopu/mysnake).

But their early version branches was left here.