# Radar

## Objectives
Create an air traffic control program to manage an infinite number of airplanes on the screen.

## Prerequisites
- GCC (for compiling a C program)
- CSFML library (graphics library for the C language)
- Python (for generating maps)

## How to Generate a Map
Use the following command to generate a map:
```bash
python gen.py -p [number_of_airplanes] -t [number_of_turns] -pa [path_to_save_file]
```
## How to Use
To compile and run the program, use the following commands:
```bash
make && ./my_radar -h
```
This will display the project's helper along with all the keybinds.
To run the program with a specific map, use:
```bash
make && ./my_radar [a_map]
```
Press "Q" to display the collision algorithm used (QUADTREE)

Enjoy !
