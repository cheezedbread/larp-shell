# larp-shell
LarpOS is a small terminal project that simulates an operating system shell.

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
LarpOS is a hobby/learning project and is still being developed (although very slowly). The code is intentionally ass due to my massive skill issue.

## To-do
- `help` command: shows list of available commands
- `man` command: shows help on specific commands
- Commands that connect the shell to the filesystem
- Fake filesystem with fake root and fake `sudo`
- Scripting
