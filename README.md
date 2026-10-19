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
### Requirements
- CMake 3.16 or later
- A compatible C++ compiler
- GitHub CLI (gh) or Git
### Compatibility
Currently, LarpOS is only officially supported on Linux. Windows and other platforms are not officially supported, but users are free to try building from source.
### Linux
Run these commands:
```gh repo clone cheezedbread/larp-shell
cd larp-shell
cmake -S . -B build
cmake --build build
./build/LarpOS
```
### Windows users
Windows support is not currently provided. If you'd like to run LarpOS on Windows, you'll need to build it yourself and handle any platform-specific issues.

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
