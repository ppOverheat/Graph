# Graph
Graph is a program in C for creating graphs of functions defined by arbitrary expressions. 
The values of expressions are calculated using Dijkstra's algorithm for translating expressions into Polish notation. 

The program is assembled using a Makefile. The name of the build stage is all.

- Conditions

  - The size of the field for displaying graphs is a rectangle of 25 by 80 points.

  - Definition area - [0; 4 Pi].

  - Range of values - [-1; 1].

  - The center of coordinates is middle of the left border (point {0, 13}).

  - Values are rounded according to the rules of mathematics.

- Graphics

The field displayed using "*" symbol for the chart line and "." for the rest of the screen space.

- Modules

  - Expression parsing and creating a list of lexical units.

  - Translation into Polish notation and calculation using this notation.

  - Drawing a graph in the terminal.

  - Library for organizing dynamic data structures (stack, list, etc.).

### <b>Example:</b>
___________________
<b>Input:</b>
```
sin(cos(2*x))
```
<b>Output:</b>

```
................................................................................
................................................................................
................................................................................
................................................................................
**................****................****................***................***
..*...................*..............*...................*...*..................
.................*........................*.............*...................*...
...*...................*............*.........................*.................
................*..........................*...............................*....
....*..................................................*.......*................
........................*..........*............................................
...............*............................*.............................*.....
.....*................................................*.........................
.........................*........*.............................*...............
..............*..........................................................*......
......*......................................*.......*..........................
..........................*......*...............................*..............
.............*................................*.........................*.......
.......*...................*....*...................*.............*.............
........*...*..................................*...*...................*........
.........***................****................***................****.........
................................................................................
................................................................................
................................................................................
```

## Important notes:

- The program was written in C, have a structured style, and run from the terminal;

- The source code has been checked by the static analyzer cppcheck, as well as the style linter cpplint.

> The program was written according to the principles of structured programming E. Dijkstra.

