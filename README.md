# Maze Solver Project

This project is a C++ implementation of a maze solver that uses both Depth-First Search (DFS) and Breadth-First Search (BFS) algorithms to find a path through a maze. The maze is represented as a matrix read from a file, and the project also includes functionality to output the solution path to a file.

## Project Structure

The project consists of the following main components:

- **Main Program (`main.cpp`)**: This file contains the main function that initializes the maze, constructs the graph representation, performs the pathfinding using DFS and BFS, and outputs the results.
- **Data Structures**:
  - `Vector.h`: Implementation of a dynamic array.
  - `Stack.h`: Implementation of a stack data structure.
  - `Queue.h`: Implementation of a queue data structure.
  - `Graph.h`: Implementation of a graph structure with vertices and edges.
- **Maze Components**:
  - `Point`: Represents a point in the maze with x and y coordinates.
  - `Node`: Represents a node in the maze with location, type (wall, path, start, end), and adjacency list.
  - `Maze`: Handles maze creation from a file and initializes node adjacencies.
- **Solvers**:
  - `Solvers`: Contains methods for solving the maze using DFS and BFS algorithms.

## Files

- `main.cpp`: Main driver program.
- `Vector.h`: Custom dynamic array implementation.
- `Stack.h`: Custom stack implementation.
- `Queue.h`: Custom queue implementation.
- `Graph.h`: Custom graph implementation.
- `Labirent.txt`: Input file containing the maze structure.
- `Sonuc.txt`: Output file where the solution path is saved.

## Usage

### Prerequisites

Make sure you have a C++ compiler installed on your system. This project uses C++11 standard.

### Compilation

To compile the project, use the following command:

```sh
g++ main.cpp -o maze_solver
```
## Execution
After compiling, you can run the program with:
```sh
./maze_solver
```
The program will read the maze structure from Labirent.txt, solve it using both DFS and BFS, and save the shortest path to Sonuc.txt.

## Input File Format (Labirent.txt)
The input file should contain a comma-separated matrix representing the maze. Each cell in the matrix can have the following values:

- 0: Wall
- 1: Path
- 2: Start point
- 3: End point

## Example:
```sh
0,0,1,0,0,0,0
0,2,1,1,0,3,0
0,0,0,1,0,1,0
0,0,0,1,1,1,0
0,1,1,1,0,0,0
0,0,0,0,0,0,0

```
## Output File (Sonuc.txt)
The output file will contain the path found from the start to the end of the maze, including the directions taken and the total cost.

## Acknowledgements
This project was developed using C++ and basic data structures and algorithms. Special thanks to the resources and tutorials that guided the development process.

## Contact
If you have any questions or suggestions, feel free to reach out at [osman2001.tekdamar@gmail.com].
