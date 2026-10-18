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
- You will need CMake (v3.16 or later), any C++ compiler, and gh.
- Then, run these commands:
``
gh repo clone cheezedbread/larp-shell
cd LarpOS
cmake -S . -B build
cmake --build build
./build/LarpOS
``

## Project status
LarpOS is a work-in-progress shell simulation written in C++. It currently supports basic interactive commands, terminal styling, and primitive command parsing.

## To-do
- [x] Make a title screen
- [x] Make a command parser
- [x] `echo` command: prints input to output
- [x] `betterecho` command: `echo` but with styling
- [x] `help` command: shows list of available commands
- [x] `man` command: shows help on specific commands
- [ ] Commands that connect the shell to the filesystem
- [ ] Fake filesystem with fake root and fake `sudo`
- [ ] Scripting
