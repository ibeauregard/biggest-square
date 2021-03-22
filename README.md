# my_bsq

## About

`my_bsq` -- finds and prints the biggest square on a map

## How to compile

Compile by running `make` in the project's root directory

## Synopsis

`my_bsq [map.txt]`

## Description

`my_bsq` finds the largest possible square on a board while avoiding obstacles. The board is represented by a file passed as the program’s argument, respecting those constraints:

- Its first line contains the number of lines on the board (and only that), "." (representing a free space) and "o" (representing an obstacle) are the only two allowed characters for the other lines
- All the lines will be the same length (except the first one)
- There will always be at least one line
- Each line is terminated by `\n`.

IMPORTANT NOTE: The program assumes that those constraints are observed, and does no further error checking. 

The program prints the board, with some "." replaced by "x" to represent the largest square found.

## Map generation

To generate a new map, run:

`perl map_generator.pl <num_rows> <num_cols> <obstacle_density_as_percentage> > <output_file.txt>`

## Implementation notes

This project could obviously have been done in a more straightforward fashion. However, I decided I was going to play with a C coding style called "C+", where one emulates object-oriented programming with the C programming language.