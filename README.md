# SolarSystemSim

This program uses Kepler's laws of planetary motion to give a simplistic simulation of the solar system.

# How to build
There are a few things that you need to do to build this program.
## -All operating systems
1.You are going to need to install the [SFML](http://www.sfml-dev.org/index.php) library.

2.You are going to have to place the font of your choice inside the same file as the executable

## -Linux
1.When linking the C++ object file to the exe you are going to need to use the following additional args

``` Bash
g++ ~/Path/to/object/file.o -o ~/path/to/exe -lsfml-graphics -lsfml-window -lsfml-system
```



