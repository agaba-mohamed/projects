# Dante's Star - Maze Generation and Solver

## Project Overview

This project, titled "Dante's Star," is an implementation of maze generation and solving inspired by Dante Alighieri's "The Divine Comedy." The goal is to navigate through nine circles of Hell, representing different challenges in maze solving.

## Project Structure

- **generator**: Contains the source code and binary for maze generation.
- **solver**: Contains the source code and binary for maze solving.
- **generalfiles**: Common source code shared between generator and solver.

## Building the Project

To build the generator and solver binaries, run the following commands:

```bash
make generator
make solver
```

## Maze Generation

To generate a maze, use the following command:

```bash
./generator/generator x y [perfect]
```

- `x` and `y`: Maze dimensions.
- `perfect` (optional): Generate a perfect maze (default is imperfect).

## Maze Solving

To solve a maze, use the following command:

```bash
./solver/solver maze.txt
```

The solved maze will be printed on the standard output. If there's no solution, it will print "no solution found."

## Circles of Hell Representation

The project is structured around the nine circles of Hell from Dante's Divine Comedy, each representing a specific challenge in maze generation and solving.

- **First Circle: Limbo**: Generating the first maze.
- **Second Circle: Lust**: Solving mazes representing the challenge of lust.
- **Third Circle: Gluttony**: Generating imperfect mazes with clusters.
- **Fourth Circle: Greed and Extravagance**: Generating perfect mazes.
- **Fifth Circle: Wrath**: Solving generated mazes.
- **Sixth Circle: Heresy**: Further optimization of maze-solving algorithms.
- **Seventh Circle: Violence**: Maze complexity measurement.
- **Eighth Circle: Fraud**: Heuristic implementation for maze solving.
- **Ninth Circle: Treachery**: Final optimization with heuristic search.

## How to Run

1. Clone the repository.
2. Navigate to the root directory.
3. Build the project using `make`.
4. Run the generator and solver with appropriate commands.

Feel free to explore the generalfiles directory for additional shared features.

Happy coding in Dante's maze of challenges!