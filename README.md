# larp-shell
LarpOS is a small hobby project where I experiment with C++ by building a simulated operating system shell.

## Features
- Interactive terminal shell
- Built-in commands
  + `echo`
  + `betterecho`
  + `clear`
  + ...
- ANSI terminal colors and text styles
- Command parsing
- ASCII-art startup screen

## Building
Compile with g++:

`` g++ larp-debug.cpp -o larp ``

Then run:

### Linux / macOS
`` ./larp ``

### Windows
`` larp.exe ``

## Project status
LarpOS is a work-in-progress shell simulation written in C++. It currently supports basic interactive commands, terminal styling, and primitive command parsing.

## To-do
- `help` command: shows list of available commands
- `man` command: shows help on specific commands
- Commands that connect the shell to the filesystem
- Fake filesystem with fake root and fake `sudo`
- Scripting
